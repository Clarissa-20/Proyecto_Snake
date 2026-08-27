#ifndef NIVEL1_H
#define NIVEL1_H

#include <QObject>
#include "nivel.h"

class Nivel1 : public Nivel
{
    Q_OBJECT

public:
    explicit Nivel1(QWidget *parent = nullptr);
};

#endif // NIVEL1_H
