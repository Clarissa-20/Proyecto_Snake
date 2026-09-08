/*#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class RegisterWindow : public QMainWindow {
    Q_OBJECT

public:
    RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void validarPassword(const QString &texto);
    void seleccionarAvatar(int idAvatar);
    void onCrearCuentaClicked();

private:
    QLabel *labelFondo;

    // Avatares (4 botones con imagen)
    QPushButton *btnAvatar[4];
    int avatarSeleccionado;

    QLineEdit *txtUsuario;
    QLineEdit *txtPassword;

    // Etiquetas de requisitos de contraseña
    QLabel *lblReqLongitud;
    QLabel *lblReqMayuscula;
    QLabel *lblReqNumero;
    QLabel *lblReqEspecial;

    QPushButton *btnCrearCuenta;
    QLabel *lblIrLogin;
};

#endif // REGISTERWINDOW_H*/