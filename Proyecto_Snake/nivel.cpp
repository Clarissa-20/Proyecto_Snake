#include "nivel.h"
#include "ui_gamewindow.h"

Nivel::Nivel(QWidget *parent)
    : QWidget(parent)
    , ui(nullptr)
    //integración de nodo prueba #1
    , cabeza(nullptr)
    //integracion de mapa prueba#1
    , mapa(nullptr)
    , timer(nullptr)
    //, cellsize(0)
    , rows(0)
    , cols(0)
    , gameover(false)
    , retryButton(nullptr)
    //nivel1
    , hayComidaDorada(false)
    , crecimientoExtra(0)
    , manzanasComidas(0)
    , puntuacion(0)
    , nivelGanado(false)
    //manzanas por tiempo
    , tiempoLimiteSegundos(0)
    , tiempoRestanteSegundos(0)
    , intervaloGeneracionMs(0)
    , timerCronometro(nullptr)

    , timerGeneracion(nullptr)
    , tiempoTerminado(false)
    , rojasGeneradas(0)
    , rojasComidas(0)

    , rojaActualComida(false)
    , doradasGeneradas(0)
    , doradasComidas(0)
    , doradaActualComida(false)

    , ganoPremio(false)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);

    setFixedSize(800,800);
    setFocusPolicy(Qt::StrongFocus);

    direction=Right;
    gameover=false;

    //spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel::gameloop);

    retryButton= new QPushButton("Retry", this);
    retryButton->setGeometry(350, 440, 100, 40);
    retryButton->setStyleSheet("QPushButton{"
                               "background-color:#00aa00;"
                               "color:white;"
                               "font-size:18px;"
                               "border-radius:10px;"
                               "}"
                               "QPushButton:hover{"
                               "background-color:#00cc00;"
                               "}"
                               );
    connect(retryButton, &QPushButton::clicked, this, &Nivel::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}

//destructor
Nivel::~Nivel()
{
    limpiarSerpiente();

    //integracion de mapa prueba#1
    destruirMapa();

    delete ui;
}

void Nivel::moveSnake()
{
    //integración de nodo prueba #1
    if(cabeza==nullptr)
    {
        return;
    }
    int newX= cabeza->x;
    int newY= cabeza->y;

    switch (direction)
    {
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
    /*
    snake.prepend(Head);
    if(Head==food)
    {
        spawnFood();
    }
    else
    {
        snake.removeLast();
    }
    */
    //bordes infinito
    if(newX<0)
    {
        newX=cols-1;
    }
    else if(newX>=cols)
    {
        newX=0;
    }

    if(newY<0)
    {
        newY=rows-1;
    }
    else if(newY>=rows)
    {
        newY=0;
    }
    //integración de nodo prueba #1
    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;

    //NIVEL 1: bandera para saber si la serpiente comió algo en este movimiento (roja o dorada)
    bool comioAlgo=false;

    //NIVEL 1: primero se revisa la manzana dorada (si está presente)
    if(hayComidaDorada==true && doradaActualComida==false && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += VALOR_DORADA; //NIVEL 1: puntos triples (10 x 3)
        doradasComidas++;
        doradaActualComida=true;
        hayComidaDorada=false; //la dorada desaparece al comerla
        crecimientoExtra += 2; //NIVEL 1: este movimiento ya crece 1 (no se borra la cola); +2 para sumar 3 en total
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y() && rojaActualComida==false)
    {
        comioAlgo=true;
        rojasComidas++;
        rojaActualComida=true;

        manzanasComidas= rojasComidas; //NIVEL 1
        puntuacion += VALOR_ROJA;
        avanzarCicloPorRojaComida();
        /*//NIVEL 1: si se come la roja, la dorada (si estaba en pantalla) desaparece también
        hayComidaDorada=false;

        if(rojasComidas >= ROJAS_MAX_GENERADAS)
        {
            finalizarPorManzanas();
            /*
            //NIVEL 2: se completaron las 6 manzanas rojas -> se gana el nivel
            nivelGanado=true;
            gameover=true;
            timer->stop();
            retryButton->show();
        }
        else
        {
            avanzarCicloPorRojaComida();
            /*spawnFood();
            intentoComidaDorada(); //NIVEL 1: probabilidad de que salga una dorada junto a la nueva roja
        }*/
    }
    if(comioAlgo==false)
    {
        //NIVEL 1: si queda crecimiento pendiente (de una dorada comida antes), la cola NO se recorta y ese crecimiento pendiente se va consumiendo un nodo por movimiento.
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente !=nullptr)//?
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

void Nivel::spawnFood()
{
    int x=0;
    int y=0;
    bool posicionValida;
    int intentos=0;
    do
    {
        x= QRandomGenerator::global()->bounded(cols);
        y= QRandomGenerator::global()->bounded(rows);
        posicionValida=true;
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
        intentos++;
    }while(posicionValida==false && intentos<100);
    food= QPoint(x,y);
}

void Nivel::checkCollision()
{
    //integración de nodo prueba #1
    if(cabeza==nullptr)
    {
        return;
    }

    int cabezaX= cabeza->x;
    int cabezaY= cabeza->y;

    Nodo* actual = cabeza->siguiente;
    while(actual !=nullptr)
    {
        if(cabezaX==actual->x && cabezaY==actual->y)
        {
            gameover=true;
            timer->stop();
            retryButton->show();
            return;
        }
        actual=actual->siguiente;
    }
}

void Nivel::crearMapa()
{
    mapa = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        mapa[i]= new int[cols];
        for (int j = 0; j < cols; j++)
        {
            mapa[i][j]=0; //0=vacía
        }
    }
}

void Nivel::destruirMapa()
{
    if(mapa != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mapa[i];
        }

        delete[] mapa;
        mapa=nullptr;
    }
}

void Nivel::limpiarSerpiente()
{
    Nodo* actual=cabeza;
    while(actual!=nullptr)
    {
        Nodo* siguiente =actual->siguiente;
        delete actual;
        actual=siguiente;
    }
    cabeza=nullptr;
}

int Nivel::obtenerLongitudSerpiente()
{
    int longitud =0;
    Nodo* actual=cabeza;
    while(actual !=nullptr)
    {
        longitud++;
        actual=actual->siguiente;
    }
    return longitud;
}

void Nivel::intentoComidaDorada()
{
    if(doradasGeneradas>=DORADAS_MAX_GENERADAS)
    {
        return;
    }
    int probabilidad = QRandomGenerator::global()->bounded(100);
    if(probabilidad >= 40)
    {
        return;
    }

    int x=0;
    int y=0;
    bool posicionValida;
    int intentos=0;

    do
    {
        x= QRandomGenerator::global()->bounded(cols);
        y= QRandomGenerator::global()->bounded(rows);
        posicionValida=true;

        //no debe salir sobre un muro
        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }

        //no debe salir en la misma celda que la manzana roja
        if(posicionValida && x==food.x() && y==food.y())
        {
            posicionValida=false;
        }

        //no debe salir sobre la serpiente
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

        intentos++;
    } while(!posicionValida && intentos<100); //límite de intentos por seguridad

    if(posicionValida==true)
    {
        comidaDorada= QPoint(x,y);
        hayComidaDorada=true;
        doradasGeneradas++;
        doradaActualComida=false;
    }
}

void Nivel::iniciarSistemaDeManzanas()
{
    tiempoLimiteSegundos=obtenerTiempoLimiteNivel();
    tiempoRestanteSegundos=tiempoLimiteSegundos;
    intervaloGeneracionMs= INTERVALO_GENERACION_MS;

    rojasGeneradas=0;
    rojasComidas=0;
    doradasGeneradas=0;
    doradasComidas=0;

    ganoPremio=false;
    tiempoTerminado=false;
    rojaActualComida=false;
    doradaActualComida=false;

    hayComidaDorada=false;
    manzanasComidas=0;

    if(timerCronometro==nullptr)
    {
        timerCronometro= new QTimer(this);
        connect(timerCronometro, &QTimer::timeout, this, &Nivel::actualizarCronometro);
    }
    if(timerGeneracion==nullptr)
    {
        timerGeneracion= new QTimer(this);
        connect(timerGeneracion, &QTimer::timeout, this, &Nivel::cicloGeneracion);
    }
    ejecutarCicloGeneracion();
    timerGeneracion->start(intervaloGeneracionMs);
    timerCronometro->start(1000);
}

bool Nivel::ejecutarCicloGeneracion()
{
    rojaActualComida=false;
    //descarta la dorada del ciclo anterior
    if(hayComidaDorada && doradaActualComida==false)
    {
        hayComidaDorada=false;
    }
    doradaActualComida=false;
    spawnFood();
    rojasGeneradas++;
    intentoComidaDorada();
    return true;
    /*if(rojasGeneradas<ROJAS_MAX_GENERADAS)
    {
        spawnFood();
        rojasGeneradas++;
        intentoComidaDorada();
        return true;
    }
    else
    {
        timerGeneracion->stop();
        return false;
    }*/

}

void Nivel::avanzarCicloPorRojaComida()
{
    bool huboNuevaRoja= ejecutarCicloGeneracion();
    if(huboNuevaRoja==true && timerGeneracion!=nullptr)
    {
        timerGeneracion->start(intervaloGeneracionMs);
    }
}
void Nivel::cicloGeneracion()
{
    if(tiempoTerminado==true || gameover==true)
    {
        return;
    }
    ejecutarCicloGeneracion();
}

void Nivel::actualizarCronometro()
{
    if(gameover==true)
    {
        timerCronometro->stop();
        return;
    }
    tiempoRestanteSegundos--;
    if(tiempoRestanteSegundos<=0)
    {
        tiempoRestanteSegundos=0;
        finalizarPorTiempo();
    }
    update();
}

void Nivel::finalizarPorTiempo()
{
    tiempoTerminado=true;
    if(timerGeneracion!=nullptr)
    {
        timerGeneracion->stop();
    }
    if(timerCronometro!=nullptr)
    {
        timerCronometro->stop();
    }
    timer->stop();
    //descarta la dorada del ciclo anterior
    if(hayComidaDorada && doradaActualComida==false)
    {
        hayComidaDorada=false;
    }
    ganoPremio=(doradasComidas>=DORADAS_MIN_PREMIO);
    nivelGanado=(rojasComidas>=MANZANAS_META);
    gameover=true;
    retryButton->show();
    update();
}
/*
void Nivel::finalizarPorManzanas()
{
    if(timerGeneracion!=nullptr)
    {
        timerGeneracion->stop();
    }
    if(timerCronometro!=nullptr)
    {
        timerCronometro->stop();
    }
    timer->stop();
    ganoPremio=(doradasComidas>=DORADAS_MIN_PREMIO);
    nivelGanado=true;
    gameover=true;
    retryButton->show();
    update();
}*/
QString Nivel::formatearTiempo(int segundos) const
{
    if(segundos<0)
    {
        segundos=0;
    }
    int m=segundos/60;
    int s=segundos%60;
    return QString("%1:%2").arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0'));

}

void Nivel::gameloop()
{
    if(gameover==true)
    {
        return;
    }

    moveSnake();
    checkCollision();
    update();
}

void Nivel::resetGame()
{
    //integración de nodo prueba #1
    limpiarSerpiente();
    //integración de nodo prueba #1
    cabeza = new Nodo(10, 10);

    direction=Right;
    gameover=false;

    puntuacion=0;
    nivelGanado=false;
    crecimientoExtra=0;

    iniciarSistemaDeManzanas();

    /*//NIVEL 1: reiniciar todo lo relacionado al nivel 2
    manzanasComidas=0;
    puntuacion=0;
    nivelGanado=false;
    hayComidaDorada=false;
    crecimientoExtra=0; //NIVEL 1*/

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(150);
    update();
}

void Nivel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //nuevo: para dibujar la img del fondo
    if(!fondo.isNull())
    {
        //dibuja y escala la imagen de fondo al tama;o de la pantalla
        painter.drawPixmap(rect(), fondo);
    }
    else
    {
        //fondo negro por si no carga la img
        painter.fillRect(rect(), Qt::black);
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

        //nuevo: aplicar margen en x - y
        int posX=marginX+(actual->x*cellsize);
        int posY=marginY+(actual->y*cellsize);

        painter.drawRoundedRect(posX, posY, cellsize, cellsize, 5, 5);
        actual= actual->siguiente;
    }
    /*painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawEllipse(food.x()*cellsize, food.y()*cellsize, cellsize, cellsize);*/

    painter.setBrush(Qt::red);
    int foodX=marginX+(food.x()*cellsize);
    int foodY=marginY+(food.y()*cellsize);
    painter.drawEllipse(foodX, foodY, cellsize, cellsize);

    //nivel 1
    /*if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255,215,0));
        painter.drawEllipse(comidaDorada.x()*cellsize, comidaDorada.y()*cellsize, cellsize, cellsize);
    }*/

    if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255, 215, 0));
        int doradaX=marginX+(comidaDorada.x()*cellsize);
        int doradaY=marginY+(comidaDorada.y()*cellsize);
        painter.drawEllipse(doradaX, doradaY, cellsize, cellsize);
    }
    /*
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1/%2").arg(manzanasComidas).arg(MANZANAS_META));
    painter.drawText(10, 60, QString("Gemas: %1").arg(totalManzanasComidas()));
    painter.drawText(10, 80, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));
*/
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 11, QFont::Bold));

    // 1. CUADRO ROJO (Izquierda): Gemas arriba y Puntos abajo
    QRect rectRojo(210, 40, 190, 60);
    painter.drawText(rectRojo, Qt::AlignHCenter | Qt::AlignTop, QString("Gemas: %1").arg(totalManzanasComidas()));
    painter.drawText(rectRojo, Qt::AlignHCenter | Qt::AlignBottom, QString("Puntos: %1").arg(puntuacion));

    // 2. CUADRO AZUL (Centro): Manzanas Rojas arriba y Doradas abajo
    QRect rectAzul(420, 40, 190, 60);
    painter.drawText(rectAzul, Qt::AlignHCenter | Qt::AlignTop, QString("Rojas: %1").arg(manzanasComidas));
    painter.drawText(rectAzul, Qt::AlignHCenter | Qt::AlignBottom, QString("Doradas: %1").arg(doradasComidas));

    // 3. CUADRO AMARILLO (Derecha): Tiempo centrado
    QRect rectAmarillo(630, 40, 190, 60);
    painter.drawText(rectAmarillo, Qt::AlignCenter, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado==true)
        {
            //NIVEL 1: mensaje de victoria al completar las 6 manzanas rojas
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
        painter.setFont(QFont("Arial", 14));
        painter.drawText(QRect(0, height()/2+20, width(), 30), Qt::AlignCenter,ganoPremio ? "¡Premio de manzanas doradas obtenido!" : "Premio de doradas no obtenido");

    }
}

void Nivel::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    {
        if(direction!=Down)
        {
            direction=Up;
        }
        break;
    }
    case Qt::Key_Down:
    {
        if(direction!=Up)
        {
            direction=Down;
        }
        break;
    }
    case Qt::Key_Left:
    {
        if(direction!=Right)
        {
            direction=Left;
        }
        break;
    }
    case Qt::Key_Right:
    {
        if(direction!=Left)
        {
            direction=Right;
        }
        break;
    }
    case Qt::Key_Space:
    {
        if(retryButton->isVisible()==true)
        {
            retryButton->click();
        }
        break;
    }
    }
}