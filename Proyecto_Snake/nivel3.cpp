#include "nivel3.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <QRandomGenerator>

Nivel3::Nivel3(QWidget *parent) :
    Nivel(parent),
    hayFrutaVelocidad(false),
    frutaVelocidadBlanca(true),
    velocidadBase(VELOCIDAD_INICIAL),
    efectoDoradaActivo(false),
    generacionPartida(0),
    desplazamientoBloques(0),
    direccionBloques(1),
    contadorMovimientoBloques(0)
{

    fondo.load(":/imagenes/nivel3_fondo.jpg");
    cols = (width() - (2 * marginX)) / cellsize;
    rows = (height() - (2 * marginY)) / cellsize;

    // USAR int** mapa (igual que Nivel 2)
    crearMapa();
    inicializarBloquesMovibles();
    cabeza = new Nodo(2, 2);

    spawnFood();
    timer->start(velocidadBase);
}

void Nivel3::inicializarBloquesMovibles() {
    centroFilaBloques = rows / 2;
    centroColumnaBloques = cols / 2;
    grosorBloqueMovil = 2;
    altoBloqueMovil = 8;
    maxDesplazamientoBloques = centroFilaBloques - altoBloqueMovil - 1;
    if (maxDesplazamientoBloques < 0) maxDesplazamientoBloques = 0;

    desplazamientoBloques = 0;
    direccionBloques = 1;
    contadorMovimientoBloques = 0;

    // Dibujar bloques iniciales en mapa[][]
    dibujarBloquesEnMapa();
}

void Nivel3::limpiarMapa() {
    if (mapa != nullptr) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mapa[i][j] = 0;
            }
        }
    }
}

void Nivel3::dibujarBloquesEnMapa() {
    if (mapa == nullptr) return;

    // Barra superior
    for (int dy = 0; dy < altoBloqueMovil; dy++) {
        for (int dx = -grosorBloqueMovil; dx <= grosorBloqueMovil; dx++) {
            int x = centroColumnaBloques + dx;
            int y = centroFilaBloques - 1 - desplazamientoBloques - dy;
            if (x >= 0 && x < cols && y >= 0 && y < rows) {
                mapa[y][x] = 1;
            }
        }
    }

    // Barra inferior
    for (int dy = 0; dy < altoBloqueMovil; dy++) {
        for (int dx = -grosorBloqueMovil; dx <= grosorBloqueMovil; dx++) {
            int x = centroColumnaBloques + dx;
            int y = centroFilaBloques + desplazamientoBloques + dy;
            if (x >= 0 && x < cols && y >= 0 && y < rows) {
                mapa[y][x] = 1;
            }
        }
    }
}

void Nivel3::actualizarBloquesMovibles() {
    contadorMovimientoBloques++;
    if (contadorMovimientoBloques < INTERVALO_MOVIMIENTO_BLOQUES) return;

    contadorMovimientoBloques = 0;

    // Mover bloques
    desplazamientoBloques += direccionBloques;
    if (desplazamientoBloques >= maxDesplazamientoBloques) {
        desplazamientoBloques = maxDesplazamientoBloques;
        direccionBloques = -1;
    } else if (desplazamientoBloques <= 0) {
        desplazamientoBloques = 0;
        direccionBloques = 1;
    }

    //  Limpiar mapa y redibujar bloques en nuevas posiciones
    limpiarMapa();
    dibujarBloquesEnMapa();
}

bool Nivel3::puntoEnBloqueMovil(int x, int y) const {
    if (mapa == nullptr) return false;
    if (x < 0 || x >= cols || y < 0 || y >= rows) return false;
    return mapa[y][x] == 1;
}

void Nivel3::gameloop() {
    if (gameover) return;

    actualizarBloquesMovibles();
    moveSnake();
    checkCollision();
    update();
}

void Nivel3::moveSnake() {
    if (cabeza == nullptr) return;

    int newX = cabeza->x;
    int newY = cabeza->y;

    switch (direction) {
    case Up:
    {
        newY--;
        break;
    }
    case Down:
    {
        newY++;
        break;
    }
    case Right:
    {
        newX++;
        break;
    }
    case Left:
    {
        newX--;
        break;

    }
    }

    // Validar límites
    if (newX < 0 || newY < 0 || newX >= cols || newY >= rows) {
        gameover = true;
        timer->stop();
        retryButton->show();
        return;
    }

    //  Validar colisión con bloques usando mapa[][]
    if (puntoEnBloqueMovil(newX, newY))
    {
        gameover = true;
        timer->stop();
        retryButton->show();
        return;
    }

    Nodo* nuevoNodo = new Nodo(newX, newY);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;

    bool comioAlgo = false;

    if (hayComidaDorada && newX == comidaDorada.x() && newY == comidaDorada.y())
    {
        puntuacion += 30;
        hayComidaDorada = false;
        activarReduccionVelocidad();
        crecimientoExtra += 2;
        comioAlgo = true;
    }

    if (hayFrutaVelocidad && newX == frutaVelocidad.x() && newY == frutaVelocidad.y())
    {
        hayFrutaVelocidad = false;
        if (frutaVelocidadBlanca)
        {
            if (velocidadBase - CAMBIO_VELOCIDAD_FRUTA >= VELOCIDAD_MINIMA)
                velocidadBase -= CAMBIO_VELOCIDAD_FRUTA;
        }
        else
        {
            if (velocidadBase + CAMBIO_VELOCIDAD_FRUTA <= VELOCIDAD_MAXIMA)
                velocidadBase += CAMBIO_VELOCIDAD_FRUTA;
        }
        if (!efectoDoradaActivo) timer->setInterval(velocidadBase);
    }

    if (newX == food.x() && newY == food.y())
    {
        comioAlgo = true;
        manzanasComidas++;
        puntuacion += 10;
        crecimientoExtra += 1;
        hayComidaDorada = false;
        hayFrutaVelocidad = false;

        if (manzanasComidas >= MANZANAS_META)
        {
            nivelGanado = true;
            gameover = true;
            timer->stop();
            retryButton->show();
        }
        else
        {
            if (manzanasComidas % 2 == 0) aumentarVelocidad();
            spawnFood();
            intentoComidaDorada();
            intentoFrutaVelocidad();
        }
    }

    if (!comioAlgo) {
        if (crecimientoExtra > 0) {
            crecimientoExtra--;
        } else if (cabeza->siguiente != nullptr) {
            Nodo* actual = cabeza;
            while (actual->siguiente->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            delete actual->siguiente;
            actual->siguiente = nullptr;
        }
    }
}

void Nivel3::spawnFood() {
    int x = 0, y = 0;
    bool posicionValida;

    do {
        x = QRandomGenerator::global()->bounded(cols);
        y = QRandomGenerator::global()->bounded(rows);
        posicionValida = true;

        //  Validar con mapa[][]
        if (puntoEnBloqueMovil(x, y)) posicionValida = false;

        if (posicionValida) {
            Nodo* actual = cabeza;
            while (actual != nullptr) {
                if (actual->x == x && actual->y == y) {
                    posicionValida = false;
                    break;
                }
                actual = actual->siguiente;
            }
        }
    } while (!posicionValida);

    food = QPoint(x, y);
}

void Nivel3::checkCollision() {
    if (cabeza == nullptr) return;

    int cabezaX = cabeza->x;
    int cabezaY = cabeza->y;

    if (cabezaX < 0 || cabezaY < 0 || cabezaX >= cols || cabezaY >= rows) {
        gameover = true;
        timer->stop();
        retryButton->show();
        return;
    }

    //  Colisión con bloques usando mapa[][]
    if (puntoEnBloqueMovil(cabezaX, cabezaY)) {
        gameover = true;
        timer->stop();
        retryButton->show();
        return;
    }

    // Colisión con su propio cuerpo
    Nodo* actual = cabeza->siguiente;
    while (actual != nullptr) {
        if (cabezaX == actual->x && cabezaY == actual->y) {
            gameover = true;
            timer->stop();
            retryButton->show();
            return;
        }
        actual = actual->siguiente;
    }
}

void Nivel3::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!fondo.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), fondo);
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    // Delimitar y dar fondo semitransparente al área jugable
    painter.setBrush(QColor(0, 0, 0, 140));
    painter.setPen(QPen(QColor(120, 110, 100), 2));
    painter.drawRect(marginX, marginY, cols * cellsize, rows * cellsize);

    painter.setBrush(QColor(120,110,100));
    painter.setPen(QPen(QColor(60,55,50), 2));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(puntoEnBloqueMovil(j,i))
            {
                int bloqueX = marginX + (j * cellsize);
                int bloqueY = marginY + (i * cellsize);
                painter.drawRect(bloqueX, bloqueY, cellsize, cellsize);
            }
        }
    }

    Nodo* actual = cabeza;
    bool esCabeza=true;
    while (actual != nullptr)
    {
        if(esCabeza==true)
        {
            painter.setBrush(QColor(0, 255, 180));
            esCabeza=false;
        }
        else
        {
            painter.setBrush(QColor(0, 180, 0));
        }
        painter.setPen(Qt::NoPen);
        int posX = marginX + (actual->x * cellsize);
        int posY = marginY + (actual->y * cellsize);
        painter.drawRoundedRect(posX, posY, cellsize, cellsize, 5, 5);
        actual= actual->siguiente;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    int foodX = marginX + (food.x() * cellsize);
    int foodY = marginY + (food.y() * cellsize);
    painter.drawEllipse(foodX, foodY, cellsize, cellsize);

    if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255,215,0));
        int doradaX = marginX + (comidaDorada.x() * cellsize);
        int doradaY = marginY + (comidaDorada.y() * cellsize);
        painter.drawEllipse(doradaX, doradaY, cellsize, cellsize);
    }

    if(hayFrutaVelocidad==true)
    {
        painter.setPen(Qt::NoPen);
        int frutax = marginX + (frutaVelocidad.x() * cellsize);
        int frutay = marginY + (frutaVelocidad.y() * cellsize);
        if(frutaVelocidadBlanca==true)
        {
            painter.setBrush(Qt::white);
            painter.drawEllipse(frutax, frutay, cellsize, cellsize);
        }
        else
        {
            painter.setBrush(QColor(150,120,80));
            painter.drawEllipse(frutax, frutay, cellsize, cellsize);
            painter.setBrush(QColor(85,65,40));
            painter.drawEllipse(frutax+3, frutay+3, cellsize, cellsize);
            painter.drawEllipse(frutax+cellsize-9, frutay+cellsize-8, 4, 4);
        }
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Gemas: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1/%2").arg(manzanasComidas).arg(MANZANAS_META));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado)
        {
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }
}


void Nivel3::resetGame() {
    limpiarSerpiente();
    cabeza = new Nodo(2, 2);

    direction = Right;
    gameover = false;
    manzanasComidas = 0;
    puntuacion = 0;
    nivelGanado = false;
    hayComidaDorada = false;
    crecimientoExtra = 0;
    velocidadBase = VELOCIDAD_INICIAL;
    efectoDoradaActivo = false;
    generacionPartida++;
    hayFrutaVelocidad = false;
    frutaVelocidadBlanca = true;
    contadorMovimientoBloques = 0;

    //  Reinicializar bloques
    inicializarBloquesMovibles();

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(velocidadBase);
    update();
}

void Nivel3::aumentarVelocidad() {
    if (velocidadBase > VELOCIDAD_MINIMA) {
        velocidadBase -= 10;
        if (!efectoDoradaActivo) timer->setInterval(velocidadBase);
    }
}

void Nivel3::activarReduccionVelocidad() {
    efectoDoradaActivo = true;
    timer->setInterval(velocidadBase + 80);
    int generacionActual = generacionPartida;
    QTimer::singleShot(5000, this, [this, generacionActual]() {
        if (generacionActual == generacionPartida) restaurarVelocidadNormal();
    });
}

void Nivel3::restaurarVelocidadNormal() {
    efectoDoradaActivo = false;
    timer->setInterval(velocidadBase);
}

void Nivel3::intentoFrutaVelocidad() {
    int probabilidad = QRandomGenerator::global()->bounded(100);
    if (probabilidad >= 30) return;

    int x = 0, y = 0;
    bool posicionValida;
    int intentos = 0;

    do {
        x = QRandomGenerator::global()->bounded(cols);
        y = QRandomGenerator::global()->bounded(rows);
        posicionValida = true;

        if (puntoEnBloqueMovil(x, y)) posicionValida = false;
        if (posicionValida && hayComidaDorada && x == comidaDorada.x() && y == comidaDorada.y())
            posicionValida = false;

        if (posicionValida) {
            Nodo* actual = cabeza;
            while (actual != nullptr) {
                if (actual->x == x && actual->y == y) {
                    posicionValida = false;
                    break;
                }
                actual = actual->siguiente;
            }
        }
        intentos++;
    } while (!posicionValida && intentos < 100);

    if (posicionValida) {
        frutaVelocidad = QPoint(x, y);
        hayFrutaVelocidad = true;
        frutaVelocidadBlanca = (QRandomGenerator::global()->bounded(100) < 50);
    }
}