// #ifndef CREARCUENTA_H
// #define CREARCUENTA_H

// class CrearCuenta
// {
// public:
//     CrearCuenta();
// };

// #endif // CREARCUENTA_H

#ifndef CREARCUENTA_H
#define CREARCUENTA_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>

class CrearCuenta : public QMainWindow {
    Q_OBJECT

public:
    CrearCuenta(QWidget *parent = nullptr);
    ~CrearCuenta();

private slots:
    void onCrearCuentaClicked();
    void onIniciarSesionClicked();
    void validarContrasena(const QString &texto);
    void seleccionarAvatar(int id);

private:
    QLabel *labelFondo;
    QLineEdit *txtUsuario;
    QLineEdit *txtContrasena;
    QPushButton *btnCrearCuenta;
    QLabel *lblLogin;

    // Requisitos de contraseña
    QLabel *lblReqLongitud;
    QLabel *lblReqMayuscula;
    QLabel *lblReqNumero;
    QLabel *lblReqEspecial;

    // Selección de avatares
    QList<QPushButton*> botonesAvatares;
    int avatarSeleccionado;
};

#endif // CREARCUENTA_H