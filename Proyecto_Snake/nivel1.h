#ifndef NIVEL1_H
#define NIVEL1_H

#include <QObject>
#include "nivel.h"

class Nivel1 : public Nivel{
    Q_OBJECT

public:
    explicit Nivel1(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // NIVEL1_H
