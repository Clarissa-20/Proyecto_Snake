#ifndef NIVEL4_H
#define NIVEL4_H

#include "nivel.h"
#include <QPoint>

class Nivel4 : public Nivel
{
    Q_OBJECT
public:
    explicit Nivel4(bool murosInfinitos, bool bloquesEstaticos, int cantidadBloques, int skinSeleccionada, QWidget *parent = nullptr);

    ~Nivel4() override;

protected:
    bool murosInfinitos;
    bool bloquesEstaticos;
    int cantidadBloquesConfigurada;
    QPoint *bloques;
    int cantidadBloquesActual;
    QPoint frutaBlanca;
    bool hayFrutaBlanca;
    int blancasGeneradasNivel4;
    static const int BLANCAS_MAX_NIVEL4 = 6;
    void generarBloques();
    void marcarBloquesEnMapa();
    void intentarFrutaBlanca();
    void moveSnake() override;
    void spawnFood() override;
    void checkCollision() override;
    void paintEvent(QPaintEvent *event) override;
    bool ejecutarCicloGeneracion() override;

    int numeroNivel() const override
    {
        return 4;
    }

protected slots:
    void resetGame() override;
};

#endif // NIVEL4_H
