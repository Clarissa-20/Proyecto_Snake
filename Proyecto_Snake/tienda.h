// #ifndef TIENDA_H
// #define TIENDA_H

// #include <QMainWindow>
// #include <QLabel>
// #include <QPushButton>

// class Tienda : public QMainWindow {
//     Q_OBJECT

// public:
//     explicit Tienda(QWidget *parent = nullptr);
//     ~Tienda();

// private slots:
//     void onVolverMenuClicked();
//     void onComprarSkinClicked(int skinId, int costo);

// private:
//     QLabel *labelFondo;
//     QPushButton *btnVolver;


//     QLabel *labelGemasIcono;
//     QLabel *labelGemasCantidad;

//     QLabel *labelSkins[6];
//     QLabel *labelNombres[6];
//     QLabel *labelPrecios[6];
//     QPushButton *btnComprar[6];
// };

// #endif // TIENDA_H

#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "usermanager.h"

class Tienda : public QMainWindow {
    Q_OBJECT

public:
    explicit Tienda(QWidget *parent = nullptr, const QString &usuario = "");
    ~Tienda();

    void setUsuarioActual(const QString &usuario);

private slots:
    void onVolverMenuClicked();
    void onComprarSkinClicked(int skinId, int costo);

private:
    void actualizarUI();
    void verificarEstadosSkins();

    QLabel *labelFondo;
    QPushButton *btnVolver;

    QLabel *labelGemasIcono;
    QLabel *labelGemasCantidad;

    QLabel *labelSkins[6];
    QLabel *labelNombres[6];
    QLabel *labelPrecios[6];
    QPushButton *btnComprar[6];

    QString usuarioActual;
    Usuario usuarioData;
    bool usuarioCargado = false;
};

#endif // TIENDA_H