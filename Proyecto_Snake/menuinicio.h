// #ifndef MENUINICIO_H
// #define MENUINICIO_H

// class MenuInicio
// {
// public:
//     MenuInicio();
// };

// #endif // MENUINICIO_H


#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MenuInicio : public QMainWindow {
    Q_OBJECT

public:
    MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

private slots:
    void onIniciarSesionClicked();
    void onRegistrarseClicked();
    void regresar();

private:
    QLabel *labelFondo;
    QPushButton *btnIniciarSesion;
    QPushButton *btnRegistrarse;
    QPushButton *btnRegresar;
};

#endif // MENUINICIO_H