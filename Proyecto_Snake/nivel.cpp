#include "nivel.h"
#include "ui_gamewindow.h"
#include "musicamanager.h"
#include "configuracion.h"
#include <QDebug>
#include <QFile>
#include <QPainter>
#include "usermanager.h"
#include <fstream>
#include <cstdio>
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
    , usandoWASD(false)
    , menuNiveles(nullptr)
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
    //cargarSpritesGusano(0);

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

    btnReanudarPartida = new QPushButton(this);
    btnReanudarPartida->setGeometry(325, 400, 150, 50);
    btnReanudarPartida->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnReanudarPartida.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnReanudarPartida, &QPushButton::clicked, this, &Nivel::onReanudarPartidaClicked);

    btnNuevaPartida = new QPushButton(this);
    btnNuevaPartida->setGeometry(325, 460, 150, 50);
    btnNuevaPartida->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnNuevaPartida.png);"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   opacity: 0.8;"
        "}"
        );
    connect(btnNuevaPartida, &QPushButton::clicked, this, &Nivel::onNuevaPartidaClicked);


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
    btnReanudarPartida->hide();
    btnNuevaPartida->hide();
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

    MusicaManager::instance().playMusicaNiveles();
    setFocusPolicy(Qt::StrongFocus);
}

//destructor
Nivel::~Nivel()
{
    limpiarSerpiente();
    destruirMapa();
    delete ui;
}

void Nivel::setUsarWASD(bool usar) {
    usandoWASD = usar;
}

bool Nivel::getUsarWASD() const {
    return usandoWASD;
}

void Nivel::moveSnake()
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

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;

    bool comioAlgo=false;

    if(hayComidaDorada==true && doradaActualComida==false && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += VALOR_DORADA;
        doradasComidas++;
        doradaActualComida=true;
        hayComidaDorada=false;
        crecimientoExtra += 2;
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y() && rojaActualComida==false)
    {
        comioAlgo=true;
        rojasComidas++;
        rojaActualComida=true;

        manzanasComidas= rojasComidas;
        puntuacion += VALOR_ROJA;
        avanzarCicloPorRojaComida();
    }

    if(comioAlgo==true && sonidoActivado==true)
    {
        sonidoComio->stop();
        sonidoComio->play();
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
            guardarPartidaCompletada();
            actualizarUsuarioTrasPartida();
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
            mapa[i][j]=0;
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

        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }

        if(posicionValida && x==food.x() && y==food.y())
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

        intentos++;
    } while(!posicionValida && intentos<100);

    if(posicionValida==true)
    {
        comidaDorada= QPoint(x,y);
        hayComidaDorada=true;
        doradasGeneradas++;
        doradaActualComida=false;
    }
}

void Nivel::cargarSpritesGusano(int skinId)
{
    QString prefijo;
    switch(skinId)
    {
        case 1:
        {
            prefijo="skin1";
            break;
        }
        case 2:
        {
            prefijo="skin2";
            break;
        }
        case 3:
        {
            prefijo="skin3";
            break;
        }
        case 4:
        {
            prefijo="skin4";
            break;
        }
        case 5:
        {
            prefijo="skin5";
            break;
        }
        case 6:
        {
            prefijo="skin6";
            break;
        }
        default:
        {
            prefijo="skin_predeterminada";
            break;
        }
    }

    imgCabezaArriba.load(":/skins/"+prefijo+"_cabeza_arriba.png");
    imgCabezaAbajo.load(":/skins/"+prefijo+"_cabeza_abajo.png");
    imgCabezaIzquierda.load(":/skins/"+prefijo+"_cabeza_izquierda.png");
    imgCabezaDerecha.load(":/skins/"+prefijo+"_cabeza_derecha.png");

    imgColaArriba.load(":/skins/"+prefijo+"_cola_vertical_arriba.png");
    imgColaAbajo.load(":/skins/"+prefijo+"_cola_vertical_abajo.png");
    imgColaIzquierda.load(":/skins/"+prefijo+"_cola_horizontal_izquierda.png");
    imgColaDerecha.load(":/skins/"+prefijo+"_cola_horizontal_derecha.png");

    imgCuerpoHorizaontal.load(":/skins/"+prefijo+"_cuerpo_horizontal.png");
    imgCuerpoVertical.load(":/skins/"+prefijo+"_cuerpo_vertical.png");

    imgCurvaArribaDerecha.load(":/skins/"+prefijo+"_curva_abajo_izquierda.png");
    imgCurvaArribaIzquierda.load(":/skins/"+prefijo+"_curva_arriba_derecha.png");
    imgCurvaAbajoDerecha.load(":/skins/"+prefijo+"_curva_arriba_izquierda.png");
    imgCurvaAbajoIzquierda.load(":/skins/"+prefijo+"_curva_abajo_derecha.png");
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
                else
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
    if(hayComidaDorada && doradaActualComida==false)
    {
        hayComidaDorada=false;
    }
    doradaActualComida=false;
    spawnFood();
    rojasGeneradas++;
    intentoComidaDorada();
    return true;
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
    guardarPartidaCompletada();
    actualizarUsuarioTrasPartida();
    retryButton->show();
    btnVolver->setGeometry(330, 490, 150,50);
    btnVolver->show();
    update();
}

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
        if(timerGeneracion!=nullptr)
        {
            timerGeneracion->start();
        }
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
            );
        sonidoActivado=true;
    }
}

void Nivel::volverAlMenu()
{
    if(gameover == false)
    {
        guardarPartida();
    }
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
    limpiarSerpiente();
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

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(150);
    update();
}

void Nivel::keyPressEvent(QKeyEvent *event)
{
    if(juegoPausado == true) return;

    int ctrl = (usandoWASD || Configuracion::tipoControlGlobal == 1) ? 1 : 0; // 0 = Flechas, 1 = WASD

    if (ctrl == 0) {
        //modo flechas
        switch (event->key()) {
        case Qt::Key_Up:    if(direction != Down)  direction = Up;    break;
        case Qt::Key_Down:  if(direction != Up)    direction = Down;  break;
        case Qt::Key_Left:  if(direction != Right) direction = Left;  break;
        case Qt::Key_Right: if(direction != Left)  direction = Right; break;
        default: QWidget::keyPressEvent(event); break;
        }
    } else {
        //mdo WASD
        switch (event->key()) {
        case Qt::Key_W:     if(direction != Down)  direction = Up;    break;
        case Qt::Key_S:     if(direction != Up)    direction = Down;  break;
        case Qt::Key_A:     if(direction != Right) direction = Left;  break;
        case Qt::Key_D:     if(direction != Left)  direction = Right; break;
        default: QWidget::keyPressEvent(event); break;
        }
    }

    if (event->key() == Qt::Key_Space && retryButton->isVisible() == true) {
        retryButton->click();
    }
}

void Nivel::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    dibujarGusano(painter);
}

void Nivel::setUsuarioActual(const QString &usuario)
{
    usuarioActual=usuario;

    std::string nombreUsuario= usuario.toStdString();
    Usuario datosUsuario;
    if(UserManager::cargarDatosUsuario(nombreUsuario, datosUsuario)==true)
    {
        cargarSpritesGusano(datosUsuario.skinActual);
    }
}



QString Nivel::nombreArchivoPartida() const
{
    return carpetaPartidaUsuarios()+"partida_" + usuarioActual + "_nivel" + QString::number(numeroNivel()) + ".txt";
}

void Nivel::guardarPartida()
{
    if(usuarioActual.isEmpty())
    {
        return;
    }

    QString nombreArchivoQt=nombreArchivoPartida();
    std::string nombreArchivo= nombreArchivoQt.toStdString();
    std::ofstream archivo(nombreArchivo, std::ios::out | std::ios::trunc);
    if(archivo.is_open()==false)
    {
        return;
    }
    archivo<<rows<<"\n";
    archivo<<cols<<"\n";
    archivo<<static_cast<int>(direction)<<"\n";
    archivo<<gameover<<"\n";
    archivo<<juegoPausado<<"\n";
    archivo<<nivelGanado<<"\n";
    archivo<<crecimientoExtra<<"\n";
    archivo<<puntuacion<<"\n";
    archivo<<manzanasComidas<<"\n";
    archivo<<food.x()<<"\n";
    archivo<<food.y()<<"\n";
    archivo<<rojaActualComida<<"\n";
    archivo<<rojasGeneradas<<"\n";
    archivo<<rojasComidas<<"\n";
    archivo<<comidaDorada.x()<<"\n";
    archivo<<comidaDorada.y()<<"\n";
    archivo<<hayComidaDorada<<"\n";
    archivo<<doradaActualComida<<"\n";
    archivo<<doradasGeneradas<<"\n";
    archivo<<doradasComidas<<"\n";
    archivo<<tiempoLimiteSegundos<<"\n";
    archivo<<tiempoRestanteSegundos<<"\n";
    archivo<<intervaloGeneracionMs<<"\n";
    archivo<<tiempoTerminado<<"\n";
    archivo<<ganoPremio<<"\n";
    int cantidadNodos=obtenerLongitudSerpiente();
    archivo<<cantidadNodos<<"\n";
    Nodo *actual=cabeza;
    while(actual!=nullptr)
    {
        archivo<<actual->x<<"\n";
        archivo<<actual->y<<"\n";
        actual=actual->siguiente;
    }
    archivo.close();

}

bool Nivel::cargarPartida()
{

    if(usuarioActual.isEmpty())
    {
        return false;
    }

    QString nombreArchivoQt=nombreArchivoPartida();
    std::string nombreArchivo= nombreArchivoQt.toStdString();
    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open()==false)
    {
        return false;
    }
    archivo>>rows;
    archivo>>cols;
    int direccionGuardada;
    archivo>>direccionGuardada;
    direction=static_cast<Direction>(direccionGuardada);
    int valorGameOver;
    int valorJuegoPausado;
    int valorNivelGanado;
    archivo>>valorGameOver;
    archivo>>valorJuegoPausado;
    archivo>>valorNivelGanado;
    archivo>>crecimientoExtra;

    gameover=(valorGameOver!=0);
    juegoPausado=(valorJuegoPausado!=0);
    nivelGanado=(valorNivelGanado!=0);
    archivo>>puntuacion;
    archivo>>manzanasComidas;

    int foodX;
    int foodY;
    int valorRojaActualComida;

    archivo>>foodX;
    archivo>>foodY;
    food=QPoint(foodX, foodY);

    archivo>>valorRojaActualComida;
    archivo>>rojasGeneradas;
    archivo>>rojasComidas;

    rojaActualComida=(valorRojaActualComida!=0);

    int doradaX;
    int doradaY;
    int valorHayComidaDorada;
    int valorDoradaActualComida;

    archivo>>doradaX;
    archivo>>doradaY;
    comidaDorada=QPoint(doradaX, doradaY);

    archivo>>valorHayComidaDorada;
    archivo>>valorDoradaActualComida;
    archivo>>doradasGeneradas;
    archivo>>doradasComidas;
    hayComidaDorada=(valorHayComidaDorada!=0);
    doradaActualComida=(valorDoradaActualComida!=0);

    archivo>>tiempoLimiteSegundos;
    archivo>>tiempoRestanteSegundos;
    archivo>>intervaloGeneracionMs;

    int valorTiempoTerminado;
    archivo>>valorTiempoTerminado;
    tiempoTerminado=(valorTiempoTerminado!=0);
    int valorGanoPremio;
    archivo>>valorGanoPremio;
    ganoPremio=(valorGanoPremio!=0);

    int cantidadNodos;
    archivo>>cantidadNodos;
    limpiarSerpiente();
    Nodo *ultimo=nullptr;
    for(int i=0; i<cantidadNodos; i++)
    {
        int x;
        int y;
        archivo>>x;
        archivo>>y;
        Nodo *nuevo= new Nodo(x, y);
        if(cabeza==nullptr)
        {
            cabeza=nuevo;
            ultimo=nuevo;
        }
        else
        {
            ultimo->siguiente=nuevo;
            ultimo=nuevo;
        }
    }
    archivo.close();
    return true;
}

void Nivel::iniciarPartida()
{
    btnReanudarPartida->hide();
    btnNuevaPartida->hide();

    if(existePartidaGuardada()==true)
    {
        mostrarOpcionesPartidaGuardada();
    }
    else
    {
        resetGame();
    }
}

bool Nivel::existePartidaGuardada() const
{
    if(usuarioActual.isEmpty())
    {
        return false;
    }

    std::string nombreArchivo = nombreArchivoPartida().toStdString();
    std::ifstream archivo(nombreArchivo);
    return archivo.is_open();
}

void Nivel::eliminarPartidaGuardada()
{
    std::string nombreArchivo = nombreArchivoPartida().toStdString();
    std::remove(nombreArchivo.c_str());
}

void Nivel::mostrarOpcionesPartidaGuardada()
{
    pausaBtn->hide();
    retryButton->hide();
    btnReaunudar->hide();
    btnVolver->hide();
    btnSonido->hide();
    btnMusica->hide();

    btnReanudarPartida->show();
    btnNuevaPartida->show();
}

void Nivel::ocultarOpcionesPartidaGuardada()
{
    btnReanudarPartida->hide();
    btnNuevaPartida->hide();
    pausaBtn->show();

}

QString Nivel::carpetaPartidaUsuarios() const
{
    QString carpeta="PartidasUsuarios";
    QDir dir;
    if(dir.exists(carpeta)==false)
    {
        dir.mkpath(carpeta);
    }
    return carpeta+"/";
}

void Nivel::guardarPartidaCompletada()
{
    if(usuarioActual.isEmpty())
    {
        return;
    }
    QString nombreArchivoQt=carpetaPartidaUsuarios()+"partidasCompletadas_"+usuarioActual+".txt";
    std::string nombreArchivo= nombreArchivoQt.toStdString();
    std::ofstream archivo(nombreArchivo, std::ios::out | std::ios::binary | std::ios::app);
    if(archivo.is_open()==false)
    {
        return;
    }

    archivo<<numeroNivel()<<" "<<manzanasComidas<<" "<<doradasComidas<<" "<<nivelGanado<<"\n";
    archivo.close();
}

void Nivel::dibujarEncabezadoPartidaPendiente(QPainter &painter)
{
    if(btnReanudarPartida->isVisible()==false)
    {
        return;
    }

    painter.fillRect(rect(), QColor(0,0,0,150));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
    painter.drawText(QRect(0, 300, width(), 40), Qt::AlignCenter, "Tienes una partida pendiente");

    painter.setFont(QFont("Trebuchet MS", 13, QFont::Bold));
    painter.drawText(QRect(0, 345, width(), 30), Qt::AlignCenter, "Elige si deseas continuar donde la dejaste o comenzar una nueva partida");
}

void Nivel::actualizarUsuarioTrasPartida()
{
    if(usuarioActual.isEmpty())
    {
        return;
    }

    if(nivelGanado==false)
    {
        return;
    }
    std::string nombreUsuario= usuarioActual.toStdString();
    Usuario usuario;
    if(UserManager::cargarDatosUsuario(nombreUsuario, usuario)==false)
    {
        return;
    }
    usuario.puntosTotales= usuario.puntosTotales+puntuacion;
    usuario.gemas= usuario.gemas+totalManzanasComidas();

    if(nivelGanado==true && numeroNivel()==usuario.nivelActual && usuario.nivelActual<3)
    {
        usuario.nivelActual= usuario.nivelActual+1;
    }
    else if(nivelGanado==true && numeroNivel()==3)
    {
        usuario.completoJuego=true;
    }

    UserManager::guardarProgresoUsuario(usuario);
}

void Nivel::onReanudarPartidaClicked()
{
    ocultarOpcionesPartidaGuardada();

    if(cargarPartida()==true)
    {
        juegoPausado=false;

        timer->start(150);
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
        if(tiempoTerminado==false && gameover==false)
        {
            if(timerCronometro!=nullptr)
            {
                timerCronometro->start(1000);
            }
            if(timerGeneracion!=nullptr)
            {
                timerGeneracion->start(intervaloGeneracionMs);
            }
        }
        setFocus();
        update();
    }
    else
    {
        resetGame();
    }
}

void Nivel::onNuevaPartidaClicked()
{
    ocultarOpcionesPartidaGuardada();
    eliminarPartidaGuardada();
    resetGame();
}

