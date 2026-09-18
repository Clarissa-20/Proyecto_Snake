#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Login : public QMainWindow {
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void onEntrarClicked();
    void onRegistrarClicked();
    void regresar();

private:
    QLabel *labelFondo;
    QLineEdit *txtUsuario;
    QLineEdit *txtContrasena;
    QPushButton *btnEntrar;
    QLabel *lblRegistrarse;
    QPushButton *btnRegresar;
};

#endif // LOGIN_H