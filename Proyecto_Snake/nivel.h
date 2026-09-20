#ifndef NIVEL_H
#define NIVEL_H

//#include <QtCore>
#include <QTimer>
#include <QPushButton>
#include <QPoint>

//#include <QtWidgets>
#include <QWidget>
#include <QRandomGenerator>
#include <QPainter>
#include <QKeyEvent>
//#include <QtGui>

#include <QPixmap> //nueva libreria para manejar las imagenes
#include <QString>

//sonido
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE
//integración de nodo prueba #1
struct Nodo
{
    int x;
    int y;
    Nodo* siguiente;
    //constructor
    Nodo(int px, int py)
    {
        x=px;
        y=py;
        siguiente=nullptr;
    }
};

class Nivel : public QWidget
{
    Q_OBJECT
private:
    QWidget *menuNiveles;
    bool usandoWASD = false; // false = flechas, true = WASD
    QString usuarioActual;
public:
    explicit Nivel(QWidget *parent = nullptr);
    virtual ~Nivel() override; //PARA EVITAR FUGAS DE MEMORIA EL VIRTUAL
    void setUsuarioActual(const QString &usuario);

    void setMenuNiveles(QWidget *menu)
    {
        menuNiveles=menu;
    }

    void setUsarWASD(bool usar);
    bool getUsarWASD() const;

    void guardarPartida();
    bool cargarPartida();
    void iniciarPartida();
    virtual int numeroNivel() const
    {
        return 0;
    }

public slots:
    void cicloGeneracion();

    virtual void actualizarCronometro();
protected:
    static const int cellsize=20;
    //nuevo: margenes para centrar el área de juego dentro del marco decorativo
    static const int marginX=100;
    static const int marginY=120;
    static const int MANZANAS_META=10;

    //manzanas por tiempo
    //static const int ROJAS_MAX_GENERADAS=15;
    static const int DORADAS_MAX_GENERADAS=6;
    static const int DORADAS_MIN_PREMIO=3;
    static const int INTERVALO_GENERACION_MS=8000; //cada 5s se generan las manzanas
    //PUNTUACION
    static const int VALOR_ROJA=10;
    static const int VALOR_DORADA=15;

    Ui::GameWindow *ui;

    QPixmap fondo; //nuevo: variable para la img de fondo
    QPixmap imgManzanaRoja;
    QPixmap imgManzanaDorada;
    QPixmap imgManzanaMorada;
    QPixmap imgManzanaBlanca;
    QPixmap imgBloque;

    //imagenes del cuerpo de la serpiente
    QPixmap imgCabezaArriba;
    QPixmap imgCabezaAbajo;
    QPixmap imgCabezaIzquierda;
    QPixmap imgCabezaDerecha;

    QPixmap imgColaArriba;
    QPixmap imgColaAbajo;
    QPixmap imgColaIzquierda;
    QPixmap imgColaDerecha;

    QPixmap imgCuerpoHorizaontal;
    QPixmap imgCuerpoVertical;

    QPixmap imgCurvaArribaDerecha;
    QPixmap imgCurvaArribaIzquierda;
    QPixmap imgCurvaAbajoDerecha;
    QPixmap imgCurvaAbajoIzquierda;


    int rows;
    int cols;

    enum Direction
    {
        Up,
        Down,
        Left,
        Right,
    };

    //QVector<QPoint> snake; //luego cambiarlo a nodo
    //integración de nodo prueba #1
    Nodo* cabeza;
    //integracion de mapa prueba#1
    int** mapa;

    QPoint food;
    Direction direction;
    QTimer *timer;

    bool gameover;

    QPushButton *retryButton;

    QPushButton *pausaBtn;
    bool juegoPausado;

    QPushButton *btnReaunudar;
    QPushButton *btnVolver;
    QPushButton *btnSonido;
    QPushButton *btnMusica;

    QPushButton *btnReanudarPartida;
    QPushButton *btnNuevaPartida;

    bool sonidoActivado;
    bool musicaActivada;

    //sonido
    QMediaPlayer *sonidoComio;
    QMediaPlayer *sonidoGano;
    QMediaPlayer *sonidoPerdio;

    QAudioOutput *audioComio;
    QAudioOutput *audioGano;
    QAudioOutput *audioPerdio;


    // manzanas prueba#1
    QPoint comidaDorada;

    // manzanas prueba#1
    int manzanasComidas;
    int puntuacion;
    bool nivelGanado;

    //mecanicas extras
    bool hayComidaDorada;
    int crecimientoExtra;

    //manzanas por tiempo
    int tiempoLimiteSegundos;
    int tiempoRestanteSegundos;
    int intervaloGeneracionMs;
    QTimer *timerCronometro;
    QTimer *timerGeneracion;
    bool tiempoTerminado;

    int rojasGeneradas;
    int rojasComidas;
    bool rojaActualComida; //para ver si ya comio la manzana roja

    int doradasGeneradas;
    int doradasComidas;
    bool doradaActualComida; //para ver si ya comio la manzana dorada

    bool ganoPremio;

    virtual void moveSnake();
    virtual void spawnFood();
    virtual void checkCollision();

    //integracion de mapa prueba#1
    void crearMapa();
    void destruirMapa();
    //integración de nodo prueba #1
    void limpiarSerpiente();
    int obtenerLongitudSerpiente();
    void crearSerpienteInicial(int x, int y, Direction direccionInicial);
    //manzanas prueba#1
    void intentoComidaDorada();

    //imagenes del cuerpo de la serpiente
    void cargarSpritesGusano(int skinId);
    void dibujarGusano(QPainter &painter);
    Direction direccionEntreNodos(Nodo *origen, Nodo *destino) const;
    Direction opuesta(Direction d) const;

    //manzanas por tiempo
    virtual int obtenerTiempoLimiteNivel() const
    {
        return 90;
    }
    void iniciarSistemaDeManzanas();
    virtual bool ejecutarCicloGeneracion();
    void avanzarCicloPorRojaComida();
    virtual void finalizarPorTiempo();
    //virtual void finalizarPorManzanas();
    virtual int totalManzanasComidas() const
    {
        return rojasComidas+doradasComidas;
    }
    QString formatearTiempo(int segundos) const;

    void dibujarEncabezadoPartidaPendiente(QPainter &painter);
    void actualizarUsuarioTrasPartida();
protected slots:
    virtual void gameloop();
    virtual void resetGame();

    void alternarPausa();
    void alternarSonido();
    void volverAlMenu();
    void alternarMusica();
    void onReanudarPartidaClicked();
    void onNuevaPartidaClicked();
protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

    QString nombreArchivoPartida() const;
    bool existePartidaGuardada() const;
    void eliminarPartidaGuardada();
    void mostrarOpcionesPartidaGuardada();
    void ocultarOpcionesPartidaGuardada();
    QString carpetaPartidaUsuarios() const;
    void guardarPartidaCompletada();
};
#endif // NIVEL_H