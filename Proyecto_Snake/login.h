// #ifndef LOGIN_H
// #define LOGIN_H

// class Login
// {
// public:
//     Login();
// };

// #endif // LOGIN_H


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

private:
    QLabel *labelFondo;
    QLineEdit *txtUsuario;
    QLineEdit *txtContrasena;
    QPushButton *btnEntrar;
    QLabel *lblRegistrarse;
};

#endif // LOGIN_H