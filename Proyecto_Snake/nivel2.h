#ifndef NIVEL2_H
#define NIVEL2_H

#include <QObject>
#include "nivel.h"

class Nivel2 : public Nivel
{
    Q_OBJECT
public:
    explicit Nivel2(QWidget *parent = nullptr);
protected:
    int velocidadBase;
    bool efectoDoradaActivo;
    int generacionPartida; //evita efecto pendiente arruine la partida siguiente
    static const int VELOCIDAD_INICIAL=150;
    static const int VELOCIDAD_MINIMA=60;

    //muros prueba #1
    void generarMuros();
    //velocidad dinamica prueba #1
    void aumentarVelocidad();
    void activarReduccionVelocidad();


    //sobreescritura de funciones de clase nivel
    void moveSnake() override;
    void spawnFood() override;
    void checkCollision() override;
    void paintEvent(QPaintEvent *) override;
protected slots:
    void resetGame() override;
    //velocidad dinamica prueba #1
    void restaurarVelocidadNormal();
};

#endif // NIVEL2_H