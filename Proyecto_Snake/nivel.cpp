#include "nivel.h"
#include "ui_gamewindow.h"
#include "musicamanager.h"
#include <QDebug>
#include <QFile>
//#include <QGuiApplication>
//#include <QScreen>

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

    //btn pausa
    , pausaBtn(nullptr)

    , juegoPausado(false)
    , btnReaunudar(nullptr)
    , btnSonido(nullptr)
    , btnVolver(nullptr)
    , sonidoActivado(true)
    , musicaActivada(true)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);

    setFixedSize(800,800);

    move(QGuiApplication::primaryScreen()->availableGeometry().center()-rect().center());

    imgManzanaRoja.load(":/imagenes/manzana_roja.png");
    imgManzanaDorada.load(":/imagenes/manzana_dorada.png");
    imgManzanaMorada.load(":/imagenes/manzana_morada.png");
    imgManzanaBlanca.load(":/imagenes/manzana_blanca.png");
    imgBloque.load(":/imagenes/bloque.png");
    setFocusPolicy(Qt::StrongFocus);

    //imagenes del cuerpo de la serpiente
    cargarSpritesGusano();

    direction=Right;
    gameover=false;

    //spawnFood();
    timer= new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Nivel::gameloop);

    retryButton= new QPushButton(this);
    retryButton->setGeometry(330, 440, 150, 50);
    retryButton->setStyleSheet("QPushButton {"
                               "border-image: url(:/btns/btnReintentar.png);"
                               "border: none;"
                               "}"
                               "QPushButton:hover {"
                               "opacity: 0.8;"
                               "}"
                               "QPushButton:pressed {"
                               "border-image: url(:/btns/btnReintentar.png);"
                               "}"
                               );
    connect(retryButton, &QPushButton::clicked, this, &Nivel::resetGame);

    pausaBtn = new QPushButton(this);
    pausaBtn->setGeometry(656, 6, 140, 60);
    pausaBtn->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/boton_pausa_nivel1_2.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "   border-image: url(:/btns/boton_pausa_nivel1_2.png);"
        "}"
        );
    connect(pausaBtn, &QPushButton::clicked, this, &Nivel::alternarPausa);

    btnReaunudar = new QPushButton(this);
    btnReaunudar->setGeometry(330, 400, 150, 50);
    btnReaunudar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnReanudar.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnReaunudar, &QPushButton::clicked, this, &Nivel::alternarPausa);



    btnSonido = new QPushButton(this);
    btnSonido->setGeometry(330, 450, 150, 50);
    btnSonido->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnConSonido.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnSonido, &QPushButton::clicked, this, &Nivel::alternarSonido);

    btnMusica = new QPushButton(this);
    btnMusica->setGeometry(330, 500, 150, 50);
    btnMusica->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnConMusica.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnMusica, &QPushButton::clicked, this, &Nivel::alternarMusica);

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(330, 550, 150, 50);
    btnVolver->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnVolverMenu.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnVolver, &QPushButton::clicked, this, &Nivel::volverAlMenu);

    btnReaunudar->hide();
    btnVolver->hide();
    btnSonido->hide();
    btnMusica->hide();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);

    // Sonido
    audioComio = new QAudioOutput(this);
    sonidoComio = new QMediaPlayer(this);

    sonidoComio->setAudioOutput(audioComio);
    sonidoComio->setSource(
        QUrl::fromLocalFile("sonidos/comio.wav")
        );
    audioComio->setVolume(1.0);

    qDebug() << "Comio:" << sonidoComio->source();
    qDebug() << "Estado:" << sonidoComio->mediaStatus();
    qDebug() << "Existe recurso:" << QFile("qrc:/sonidos/comio.wav").exists();


    audioGano = new QAudioOutput(this);
    sonidoGano = new QMediaPlayer(this);

    sonidoGano->setAudioOutput(audioGano);
    sonidoGano->setSource(
        QUrl::fromLocalFile("sonidos/gano.wav")
        );
    audioGano->setVolume(1.0);

    audioPerdio = new QAudioOutput(this);
    sonidoPerdio = new QMediaPlayer(this);

    sonidoPerdio->setAudioOutput(audioPerdio);
    sonidoPerdio->setSource(
        QUrl::fromLocalFile("sonidos/perdio.wav")
        );

    audioPerdio->setVolume(1.0);

    MusicaManger::instance().playMusicaNiveles();
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

    if(comioAlgo==true && sonidoActivado==true)
    {
        sonidoComio->stop();
        sonidoComio->play();
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
            if (sonidoActivado==true)
            {
                sonidoPerdio->stop();
                sonidoPerdio->play();
            }
            retryButton->show();
            btnVolver->setGeometry(330, 490, 150,50);
            btnVolver->show();
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

void Nivel::crearSerpienteInicial(int x, int y, Direction direccionInicial)
{
    cabeza= new Nodo(x, y);

    int colaX=x;
    int colaY=y;

    switch (direccionInicial)
    {
        case Up:
        {
            colaY=y+1;
            break;
        }
        case Down:
        {
            colaY=y-1;
            break;
        }
        case Left:
        {
            colaX=x+1;
            break;
        }
        case Right:
        {
            colaX=x-1;
            break;
        }
    }

    Nodo *cola= new Nodo(colaX, colaY);
    cabeza->siguiente=cola;
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

void Nivel::cargarSpritesGusano()
{
    imgCabezaArriba.load(":/skins/skin_predeterminada_cabeza_arriba.png");
    imgCabezaAbajo.load(":/skins/skin_predeterminada_cabeza_abajo.png");
    imgCabezaIzquierda.load(":/skins/skin_predeterminada_cabeza_izquierda.png");
    imgCabezaDerecha.load(":/skins/skin_predeterminada_cabeza_derecha.png");

    imgColaArriba.load(":/skins/skin_predeterminada_cola_vertical_arriba.png");
    imgColaAbajo.load(":/skins/skin_predeterminada_cola_vertical_abajo.png");
    imgColaIzquierda.load(":/skins/skin_predeterminada_cola_horizontal_izquierda.png");
    imgColaDerecha.load(":/skins/skin_predeterminada_cola_horizontal_derecha.png");

    imgCuerpoHorizaontal.load(":/skins/skin_predeterminada_cuerpo_horizontal.png");
    imgCuerpoVertical.load(":/skins/skin_predeterminada_cuerpo_vertical.png");

    imgCurvaArribaDerecha.load(":/skins/skin_predeterminada_curva_abajo_izquierda.png");
    imgCurvaArribaIzquierda.load(":/skins/skin_predeterminada_curva_arriba_derecha.png");
    imgCurvaAbajoDerecha.load(":/skins/skin_predeterminada_curva_arriba_izquierda.png");//
    imgCurvaAbajoIzquierda.load(":/skins/skin_predeterminada_curva_abajo_derecha.png");//
}

void Nivel::dibujarGusano(QPainter &painter)
{
    if(cabeza==nullptr)
    {
        return;
    }

    if(cabeza->siguiente==nullptr)
    {
        const QPixmap *spriteCabeza= &imgCabezaDerecha;
        switch(direction)
        {
        case Up:
        {
            spriteCabeza=&imgCabezaArriba;
            break;
        }
        case Down:
        {
            spriteCabeza=&imgCabezaAbajo;
            break;
        }
        case Left:
        {
            spriteCabeza=&imgCabezaIzquierda;
            break;
        }
        case Right:
        {
            spriteCabeza=&imgCabezaDerecha;
            break;
        }
        }

        int posX=marginX+(cabeza->x*cellsize);
        int posY=marginY+(cabeza->y*cellsize);
        if(spriteCabeza->isNull()==false)
        {
            painter.drawPixmap(posX, posY, cellsize, cellsize, *spriteCabeza);
        }
        return;
    }

    Nodo *anterior=nullptr;
    Nodo *actual=cabeza;

    while(actual!=nullptr)
    {
        Nodo *siguiente= actual->siguiente;
        int posX=marginX+(actual->x*cellsize);
        int posY=marginY+(actual->y*cellsize);
        const QPixmap *sprite=nullptr;

        if(actual==cabeza)
        {
            switch(direction)
            {
            case Up:
            {
                sprite=&imgCabezaArriba;
                break;
            }
            case Down:
            {
                sprite=&imgCabezaAbajo;
                break;
            }
            case Left:
            {
                sprite=&imgCabezaIzquierda;
                break;
            }
            case Right:
            {
                sprite=&imgCabezaDerecha;
                break;
            }
            }
        }
        else if(siguiente==nullptr)
        {
            Direction dirCola= direccionEntreNodos(actual, anterior);
            switch(dirCola)
            {
            case Up:
            {
                sprite=&imgColaArriba;
                break;
            }
            case Down:
            {
                sprite=&imgColaAbajo;
                break;
            }
            case Left:
            {
                sprite=&imgColaIzquierda;
                break;
            }
            case Right:
            {
                sprite=&imgColaDerecha;
                break;
            }
            }
        }
        else
        {
            Direction direccionEntrada= direccionEntreNodos(actual, anterior);
            Direction direccionSalida= direccionEntreNodos(actual, siguiente);

            bool entradaHorizontal=((direccionEntrada==Left) || (direccionEntrada==Right));
            bool salidaHorizontal=((direccionSalida==Left) || (direccionSalida==Right));

            if(entradaHorizontal==salidaHorizontal)
            {
                sprite= entradaHorizontal? &imgCuerpoHorizaontal: &imgCuerpoVertical;
            }
            else
            {
                //Direction ladoCabeza= opuesta(direccionEntrada);
                //Direction ladoCola= direccionSalida;

                bool tieneArriba=((direccionEntrada==Up) || (direccionSalida==Up));
                bool tieneAbajo=((direccionEntrada==Down) || (direccionSalida==Down));
                bool tieneIzquierda=((direccionEntrada==Left) || (direccionSalida==Left));
                bool tieneDerecha=((direccionEntrada==Right) || (direccionSalida==Right));

                if(tieneArriba==true && tieneDerecha==true)
                {
                    sprite=&imgCurvaArribaDerecha;
                }
                else if(tieneArriba==true && tieneIzquierda==true)
                {
                    sprite=&imgCurvaArribaIzquierda;
                }
                else if(tieneAbajo==true && tieneDerecha==true)
                {
                    sprite=&imgCurvaAbajoDerecha;
                }
                else //tiene abajo y a la izquierda
                {
                    sprite=&imgCurvaAbajoIzquierda;
                }
            }
        }

        if(sprite!=nullptr && sprite->isNull()==false)
        {
            painter.drawPixmap(posX, posY, cellsize, cellsize, *sprite);
        }
        anterior=actual;
        actual=siguiente;
    }
}

Nivel::Direction Nivel::opuesta(Direction d) const
{
    switch(d)
    {
    case Up:
        return Down;
    case Down:
        return Up;
    case Left:
        return Right;
    case Right:
        return Left;
    }
    return d;
}

Nivel::Direction Nivel::direccionEntreNodos(Nodo *origen, Nodo *destino) const
{
    if(origen==nullptr || destino==nullptr)
    {
        return direction;
    }

    int direccionX= destino->x -origen->x;
    int direccionY= destino->y-origen->y;

    if(direccionX>1)
    {
        direccionX=-1;
    }
    else if(direccionX<-1)
    {
        direccionX=1;
    }

    if(direccionY>1)
    {
        direccionY=-1;
    }
    else if(direccionY<-1)
    {
        direccionY=1;
    }

    if(direccionX==1)
    {
        return Right;
    }
    if(direccionX==-1)
    {
        return Left;
    }
    if(direccionY==1)
    {
        return Down;
    }
    if(direccionY==-1)
    {
        return Up;
    }
    return direction;
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
    if (sonidoActivado==true)
    {
        if (nivelGanado==true)
        {
            sonidoGano->stop();
            sonidoGano->play();
        }
        else
        {
            sonidoPerdio->stop();
            sonidoPerdio->play();
        }
    }
    gameover=true;
    retryButton->show();
    btnVolver->setGeometry(330, 490, 150,50);
    btnVolver->show();
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

void Nivel::alternarPausa()
{
    if(gameover==true)
    {
        return;
    }
    juegoPausado=!juegoPausado;

    if(juegoPausado==true)
    {
        timer->stop();
        if(timerCronometro!=nullptr)
        {
            timerCronometro->stop();
        }
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->stop();
        }
        //pausaBtn->setText("Reanudar");

        btnReaunudar->show();

        btnVolver->show();
        btnSonido->show();
        btnMusica->show();
    }
    else
    {
        timer->start();
        if(timerCronometro!=nullptr)
        {
            timerCronometro->start();
        }
        if(timerCronometro!=nullptr)
        {
            timerGeneracion->start();
        }
        //pausaBtn->setText("Pausa");
        btnReaunudar->hide();
        btnVolver->hide();
        btnSonido->hide();
        btnMusica->hide();

        setFocus();
    }
    update();

}

void Nivel::alternarSonido()
{
    if(sonidoActivado==true)
    {
        btnSonido->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/imagenes/btnSinSonido.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        sonidoActivado=false;
    }
    else
    {
        btnSonido->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/imagenes/btnConSonido.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        sonidoActivado=true;

    }
}

void Nivel::volverAlMenu()
{
    if(menuNiveles!=nullptr)
    {
        menuNiveles->show();
    }
    this->close();
}

void Nivel::alternarMusica()
{
    if(musicaActivada==true)
    {
        btnMusica->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/imagenes/btnSinMusica.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        musicaActivada=false;
    }
    else
    {
        btnMusica->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/imagenes/btnConMusica.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        musicaActivada=true;

    }
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
    crearSerpienteInicial(10,10,Right);

    direction=Right;
    gameover=false;

    puntuacion=0;
    nivelGanado=false;
    crecimientoExtra=0;

    btnReaunudar->hide();
    btnVolver->setGeometry(330, 550, 150, 50);
    btnVolver->hide();
    btnSonido->hide();
    btnMusica->hide();
    pausaBtn->show();
    juegoPausado=false;
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



void Nivel::keyPressEvent(QKeyEvent *event)
{
    if(juegoPausado==true)
    {
        return;
    }
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