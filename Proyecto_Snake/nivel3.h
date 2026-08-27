#ifndef NIVEL3_H
#define NIVEL3_H

#include "nivel.h"
#include <QObject>

class Nivel3 : public Nivel
{
    Q_OBJECT
public:
    explicit Nivel3(QWidget *parent = nullptr);

protected:
    //nivel 3 frutas Especiales
    QPoint frutaVelocidad;
    bool hayFrutaVelocidad;
    bool frutaVelocidadBlanca;

    //velocidad dinamica prueba #1
    int velocidadBase;
    bool efectoDoradaActivo;
    int generacionPartida; //evita efecto pendiente arruine la partida siguiente

    //nivel 3 bloques movibles
    int centroFilaBloques;
    int centroColumnaBloques;
    int altoBloqueMovil;
    int grosorBoqueMovil;
    int desplazamientoBloques;
    int direccionBloques;
    int contadorMovimientoBloques;
    int maxDesplazamientoBloques;
    static const int INTERVALO_MOVIMIENTO_BLOQUES=5;

    //nivel 3 velocidades
    static const int VELOCIDAD_INICIAL=150;
    static const int VELOCIDAD_MINIMA=20;
    static const int VELOCIDAD_MAXIMA=150;
    static const int CAMBIO_VELOCIDAD_FRUTA=10;

    //velocidad dinamica prueba #1
    void aumentarVelocidad();
    void activarReduccionVelocidad();

    //nivel 3 frutas especiales
    void intentoFrutaVelocidad();

    //nivel 3 bloques movibles
    void inicializarBloquesMovibles();
    void actualizarBloquesMovibles();
    bool puntoEnBloqueMovil(int x, int y) const;

    //sobreescritura de funciones de clase nivel
    void moveSnake() override;
    void spawnFood() override;
    void checkCollision() override;
    void paintEvent(QPaintEvent *) override;

protected slots:
    void gameloop();
    void resetGame() override;
    //velocidad dinamica prueba #1
    void restaurarVelocidadNormal();
};

#endif // NIVEL3_H