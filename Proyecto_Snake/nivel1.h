#ifndef NIVEL1_H
#define NIVEL1_H

#include "nivel.h"

class Nivel1 : public Nivel{
    Q_OBJECT //qwidget trae integrado a Q_OBJECT

public:
    explicit Nivel1(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    int numeroNivel() const override
    {
        return 1;
    }
};

#endif // NIVEL1_H
