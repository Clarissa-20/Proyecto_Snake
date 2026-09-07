#ifndef NIVEL3_H
#define NIVEL3_H

#include "nivel.h"

class Nivel3 : public Nivel {
    Q_OBJECT

public:
    explicit Nivel3(QWidget *parent = nullptr);

protected:
    QPoint frutaVelocidad;
    bool hayFrutaVelocidad;
    bool frutaVelocidadBlanca;
    bool frutaVelocidadCafe;

    int velocidadBase;
    int generacionPartida;
    bool efectoDoradaActivo;

    int centroFilaBloques;
    int centroColumnaBloques;
    int altoBloqueMovil;
    int grosorBloqueMovil;
    int desplazamientoBloques;
    int direccionBloques;
    int contadorMovimientoBloques;
    int maxDesplazamientoBloques;

    static const int INTERVALO_MOVIMIENTO_BLOQUES = 5;
    static const int VELOCIDAD_INICIAL = 50;
    static const int VELOCIDAD_MINIMA = 20;
    static const int VELOCIDAD_MAXIMA = 150;
    static const int CAMBIO_VELOCIDAD_FRUTA = 10;
    //manzanas por tiempo
    int cafesGeneradas;
    int blancasGeneradas;
    static const int CAFES_MAX_GENERADAS=6;
    static const int BLANCAS_MAX_GENERADAS=4;

    void aumentarVelocidad();
    void activarReduccionVelocidad();
    void restaurarVelocidadNormal();
    void intentoFrutaVelocidad();

    void inicializarBloquesMovibles();
    void actualizarBloquesMovibles();
    void limpiarMapa();                    // Limpia mapa[][] antes de redibujar
    void dibujarBloquesEnMapa();           // Marca los bloques en mapa[][]
    bool puntoEnBloqueMovil(int x, int y) const;

    void moveSnake() override;
    void spawnFood() override;
    void checkCollision() override;
    void paintEvent(QPaintEvent *event) override;

    //manzanas por tiempo
    int obtenerTiempoLimiteNivel() const override
    {
        return 120;
    }
    bool ejecutarCicloGeneracion() override;
protected slots:
    void gameloop() override;
    void resetGame() override;
};

#endif