#include "nivel2.h"
#include "ui_gamewindow.h"

Nivel2::Nivel2(QWidget *parent)
    : Nivel(parent)
    , velocidadBase(VELOCIDAD_INICIAL)
    , efectoDoradaActivo(false)
    , generacionPartida(0)
{

    //Cargamos aquí la img de fondo para el nivel 2
    fondo.load(":/imagenes/nivel2_fondo.png");

    cols=((width()-(2*marginX))/cellsize);
    rows=((height()-marginY-120)/cellsize);
    crearMapa();
    generarMuros();

    // Cambiamos el inicio a una celda vacía fuera de la cruz de muros
    cabeza=new Nodo(2, 2);

    iniciarGeneracionPorTiempo();
    //spawnFood();
    //timer= new QTimer(this);

    //connect(timer, &QTimer::timeout, this, &Nivel2::gameloop);

    timer->start(150);

    //connect(retryButton, &QPushButton::clicked, this, &Nivel2::resetGame);

}

void Nivel2::iniciarGeneracionPorTiempo()
{
    rojasGeneradas=0;
    rojasComidas=0;
    doradasGeneradas=0;
    doradasComidas=0;
    rojaActualComida=false;
    doradaActualComida=false;
    hayComidaDorada=false;

    tiempoLimiteSegundos=obtenerTiempoLimiteNivel();
    tiempoRestanteSegundos=tiempoLimiteSegundos;
    tiempoTerminado=false;
    ganoPremio=false;
    if(timerCronometro==nullptr)
    {
        timerCronometro= new QTimer(this);
        connect(timerCronometro, &QTimer::timeout, this, &Nivel::actualizarCronometro);
    }

    intervaloGeneracionMs=INTERVALO_GENERACION_MS;
    if(timerGeneracion==nullptr)
    {
        timerGeneracion= new QTimer(this);
        connect(timerGeneracion, &QTimer::timeout, this, &Nivel::cicloGeneracion);
    }

    ejecutarCicloGeneracion();
    timerGeneracion->start(intervaloGeneracionMs);
    timerCronometro->start(1000);
}

void Nivel2::finalizarPorTiempo()
{
    timer->stop();
    if(timerGeneracion!=nullptr)
    {
        timerGeneracion->stop();
    }
    if(timerCronometro!=nullptr)
    {
        timerCronometro->stop();
    }
    gameover=true;
    tiempoTerminado=true;
    nivelGanado=(manzanasComidas>=MANZANAS_META);
    ganoPremio=(doradasComidas>=DORADAS_MIN_PREMIO);
    retryButton->show();
    update();
}
void Nivel2::generarMuros()
{
    int centroFila = rows/2;
    int centroColumna = cols/2;
    int grosor = 2;
    int largoBrazo = 8;

    // Línea vertical de la cruz |
    for(int i = centroFila-largoBrazo; i <= centroFila+largoBrazo; i++)
    {
        for(int j = centroColumna-grosor; j <= centroColumna+grosor; j++)
        {
            if(i>=0 && i<rows && j>=0 && j<cols)
            {
                mapa[i][j]=1;
            }
        }
    }
    // Línea horizontal de la cruz -
    for(int i = centroFila-grosor; i <= centroFila+grosor; i++)
    {
        for(int j = centroColumna-largoBrazo; j <= centroColumna+largoBrazo; j++)
        {
            if(i>=0 && i<rows && j>=0 && j<cols)
            {
                mapa[i][j]=1;
            }
        }
    }
}

void Nivel2::aumentarVelocidad()
{
    if(velocidadBase > VELOCIDAD_MINIMA)
    {
        velocidadBase -= 10;
        if(efectoDoradaActivo==false)
        {
            timer->setInterval(velocidadBase);
        }
    }
}

void Nivel2::activarReduccionVelocidad()
{
    efectoDoradaActivo=true;
    timer->setInterval(velocidadBase + 80);

    int generacionActual = generacionPartida;
    QTimer::singleShot(5000, this, [this, generacionActual]()
                       {
                           if(generacionActual == generacionPartida)
                           {
                               restaurarVelocidadNormal();
                           }
                       });
}

/*void Nivel2::moveSnake()
{
    if(cabeza==nullptr)
    {
        return;
    }
    int newX= cabeza->x;
    int newY= cabeza->y;

    switch (direction)
    {
    case Up:
        newY--;
        break;
    case Down:
        newY++;
        break;
    case Right:
        newX++;
        break;
    case Left:
        newX--;
        break;
    }

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;
    bool comioAlgo=false;

    if(hayComidaDorada==true && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += 30;
        hayComidaDorada=false;
        activarReduccionVelocidad();
        crecimientoExtra += 2;
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y())
    {
        comioAlgo=true;
        manzanasComidas++;
        puntuacion += 10;

        hayComidaDorada=false;

        if(manzanasComidas >= MANZANAS_META)
        {
            nivelGanado=true;
            gameover=true;
            timer->stop();
            retryButton->show();
        }
        else
        {
            if(manzanasComidas % 2 == 0)
            {
                aumentarVelocidad();
            }

            spawnFood();
            intentoComidaDorada();
        }
    }

    if(!comioAlgo)
    {
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente !=nullptr)
        {
            Nodo* actual=cabeza;
            while(actual->siguiente->siguiente != nullptr)
            {
                actual=actual->siguiente;
            }
            delete actual->siguiente;
            actual->siguiente=nullptr;
        }
    }
}*/

void Nivel2::moveSnake()
{
    if(cabeza==nullptr)
    {
        return;
    }
    int newX= cabeza->x;
    int newY= cabeza->y;

    switch (direction)
    {
    case Up:
        newY--;
        break;
    case Down:
        newY++;
        break;
    case Right:
        newX++;
        break;
    case Left:
        newX--;
        break;
    }

    // Validar límites ANTES de mover la serpiente para evitar que se pinte afuera en cualquier dirección
    if(newX < 0 || newY < 0 || newX >= cols || newY >= rows)
    {
        gameover=true;
        timer->stop();
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->stop();
        }
        retryButton->show();
        return;
    }

    // Validar colisión con muros antes de avanzar
    if(mapa!=nullptr && mapa[newY][newX]==1)
    {
        gameover=true;
        timer->stop();
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->stop();
        }
        retryButton->show();
        return;
    }

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;
    bool comioAlgo=false;

    if(hayComidaDorada==true && doradaActualComida==false && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += 15;
        doradasComidas++;
        doradaActualComida=true;
        hayComidaDorada=false;
        activarReduccionVelocidad();
        crecimientoExtra += 2;
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y() && rojaActualComida==false)
    {
        comioAlgo=true;
        manzanasComidas++;
        puntuacion += 10;
        rojaActualComida=true;
        /*
        if(manzanasComidas >= MANZANAS_META)
        {
            nivelGanado=true;
            gameover=true;
            timer->stop();
            if(timerGeneracion!=nullptr)
            {
                timerGeneracion->stop();
            }
            retryButton->show();
        }
        else
        {
            if(manzanasComidas % 2 == 0)
            {
                aumentarVelocidad();
            }

            avanzarCicloPorRojaComida();
        }*/
        if(manzanasComidas % 2 == 0)
        {
            aumentarVelocidad();
        }

        avanzarCicloPorRojaComida();
    }

    if(comioAlgo==false)
    {
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente !=nullptr)
        {
            Nodo* actual=cabeza;
            while(actual->siguiente->siguiente != nullptr)
            {
                actual=actual->siguiente;
            }
            delete actual->siguiente;
            actual->siguiente=nullptr;
        }
    }
}

void Nivel2::spawnFood()
{
    int x=0;
    int y=0;
    bool posicionValida;

    do
    {
        x= QRandomGenerator::global()->bounded(cols);
        y= QRandomGenerator::global()->bounded(rows);
        posicionValida=true;

        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }

        if(posicionValida==true)
        {
            Nodo* actual=cabeza;
            while(actual!=nullptr)
            {
                if(actual->x==x && actual->y==y)
                {
                    posicionValida=false;
                    break;
                }
                actual=actual->siguiente;
            }
        }

    } while(posicionValida==false);

    food= QPoint(x,y);
}

void Nivel2::checkCollision()
{
    if(cabeza==nullptr)
    {
        return;
    }
    int cabezaX= cabeza->x;
    int cabezaY= cabeza->y;

    if(cabezaX<0 || cabezaY<0 || cabezaX>=cols || cabezaY>=rows)
    {
        gameover=true;
        timer->stop();
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->stop();
        }
        retryButton->show();
        return;
    }

    if(mapa!=nullptr && mapa[cabezaY][cabezaX]==1)
    {
        gameover=true;
        timer->stop();
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->stop();
        }
        retryButton->show();
        return;
    }

    Nodo* actual = cabeza->siguiente;
    while(actual !=nullptr)
    {
        if(cabezaX==actual->x && cabezaY==actual->y)
        {
            gameover=true;
            timer->stop();
            if(timerGeneracion!=nullptr)
            {
                timerGeneracion->stop();
            }
            retryButton->show();
            return;
        }
        actual=actual->siguiente;
    }
}

void Nivel2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!fondo.isNull())
    {
        painter.drawPixmap(0, 0, width(), height(), fondo);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }

    // Delimitar y dar fondo semitransparente al área jugable
    painter.setBrush(QColor(0, 0, 0, 140)); // Color negro con transparencia (cambia el 140 para más o menos opacidad)
    painter.setPen(QPen(QColor(120, 110, 100), 2)); // Un borde sutil alrededor de la zona de juego
    painter.drawRect(marginX, marginY, cols * cellsize, rows * cellsize);

    // CORREGIDO: Se agregaron marginX y marginY para que los muros coincidan con la cuadrícula visual
    painter.setBrush(QColor(120,110,100));
    painter.setPen(QPen(QColor(60,55,50), 2));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(mapa!=nullptr && mapa[i][j]==1)
            {
                int muroX = marginX + (j * cellsize);
                int muroY = marginY + (i * cellsize);
                painter.drawRect(muroX, muroY, cellsize, cellsize);
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
        int posX=marginX+(actual->x*cellsize);
        int posY=marginY+(actual->y*cellsize);
        painter.drawRoundedRect(posX, posY, cellsize, cellsize, 5,5);
        actual= actual->siguiente;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    int foodX=marginX+(food.x()*cellsize);
    int foodY=marginY+(food.y()*cellsize);
    painter.drawEllipse(foodX, foodY, cellsize, cellsize);

    if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255,215,0));
        int doradaX=marginX+(comidaDorada.x()*cellsize);
        int doradaY=marginY+(comidaDorada.y()*cellsize);
        painter.drawEllipse(doradaX, doradaY, cellsize, cellsize);
    }
    /*
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1/%2").arg(manzanasComidas).arg(MANZANAS_META));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado==true)
        {
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }*/
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    int topY = 24;
    int bottomY = 40;

    QRect rect1Top(185, topY, 140, 18);
    QRect rect1Bottom(185, bottomY, 140, 18);
    painter.drawText(rect1Top, Qt::AlignCenter, QString("Gemas: %1").arg(totalManzanasComidas()));
    painter.drawText(rect1Bottom, Qt::AlignCenter, QString("Puntos: %1").arg(puntuacion));

    QRect rect2Top(335, topY, 140, 18);
    QRect rect2Bottom(335, bottomY, 140, 18);
    painter.drawText(rect2Top, Qt::AlignCenter, QString("Rojas: %1").arg(manzanasComidas));
    painter.drawText(rect2Bottom, Qt::AlignCenter, QString("Doradas: %1").arg(doradasComidas));

    QRect rect3(494, 22, 140, 36);
    painter.drawText(rect3, Qt::AlignCenter, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        painter.drawText(QRect(0, height()/2-30, width(), 50), Qt::AlignHCenter, nivelGanado?"¡NIVEL COMPLETADO!":"GAME OVER");

        painter.setFont(QFont("Trebuchet MS", 14, QFont::Bold));
        painter.drawText(QRect(0, height()/2, width(), 30), Qt::AlignCenter,ganoPremio ? "¡Premio de manzanas doradas obtenido!" : "Premio de doradas no obtenido");

    }
}

void Nivel2::resetGame()
{
    limpiarSerpiente();
    cabeza = new Nodo(2, 2); // Mantener la misma posición inicial segura

    direction=Right;
    gameover=false;

    manzanasComidas=0;
    puntuacion=0;
    nivelGanado=false;
    hayComidaDorada=false;
    crecimientoExtra=0;
    velocidadBase=VELOCIDAD_INICIAL;
    efectoDoradaActivo=false;
    generacionPartida++;

    tiempoTerminado=false;

    iniciarGeneracionPorTiempo();

    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(velocidadBase);
    update();
}

void Nivel2::restaurarVelocidadNormal()
{
    efectoDoradaActivo=false;
    timer->setInterval(velocidadBase);
}
