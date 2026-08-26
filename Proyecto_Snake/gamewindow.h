#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include <QtCore>
#include <QtWidgets>
#include <QtGui>

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

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;

private slots:
    void gameloop();
    void resetGame();
private:
    Ui::GameWindow *ui;

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

    int cellsize;
    int rows;
    int cols;

    bool gameover;

    QPushButton *retryButton;

    // manzanas prueba#1
    QPoint comidaDorada;
    bool hayComidaDorada;
    int crecimientoExtra;
    // manzanas prueba#1
    int manzanasComidas;
    int puntuacion;
    bool nivelGanado;
    static const int MANZANAS_META=6;

    void moveSnake();
    void spawnFood();
    void checkCollision();

    //integracion de mapa prueba#1
    void crearMapa();
    void destruirMapa();
    //integración de nodo prueba #1
    void limpiarSerpiente();
    int obtenerLongitudSerpiente();

    //manzanas prueba#1
    void intentoComidaDorada();
protected:
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;

};
#endif // GAMEWINDOW_H