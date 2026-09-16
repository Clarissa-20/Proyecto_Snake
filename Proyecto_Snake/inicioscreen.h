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
    void regresar();

private:
    QLabel *labelFondo;
    QPushButton *btnIniciar;
    QPushButton *btnRegresar;
};

#endif // INICIOSCREEN_H