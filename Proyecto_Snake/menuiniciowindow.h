/*#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MenuInicioWindow : public QMainWindow {
    Q_OBJECT

public:
    MenuInicioWindow(QWidget *parent = nullptr);
    ~MenuInicioWindow();

private slots:
    void onIniciarSesionClicked();
    void onRegistrarseClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnIniciarSesion;
    QPushButton *btnRegistrarse;
};

#endif // MENUINICIO_H*/