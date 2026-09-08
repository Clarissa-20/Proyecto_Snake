#ifndef NIVEL_H
#define NIVEL_H

#include <QWidget>

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

#include <QPixmap> //nuevo]a libreria para manejar las imagenes

#include <QString>

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

public:
    explicit Nivel(QWidget *parent = nullptr);
    virtual ~Nivel() override; //PARA EVITAR FUGAS DE MEMORIA EL VIRTUAL

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

    //manzanas prueba#1
    void intentoComidaDorada();

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

protected slots:
    virtual void gameloop();
    virtual void resetGame();

    void alternarPausa();
protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // GAMEWINDOW_H
