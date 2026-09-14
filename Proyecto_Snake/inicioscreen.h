// #ifndef INICIOSCREEN_H
// #define INICIOSCREEN_H

// class InicioScreen
// {
// public:
//     InicioScreen();
// };

// #endif // INICIOSCREEN_H


#ifndef INICIOSCREEN_H
#define INICIOSCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class InicioScreen : public QMainWindow {
    Q_OBJECT

public:
    InicioScreen(QWidget *parent = nullptr);
    ~InicioScreen();

private slots:
    void onIniciarAventuraClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnIniciar;
};

#endif // INICIOSCREEN_H