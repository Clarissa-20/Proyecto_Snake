#include "login.h"
#include "menuprincipal.h"
#include "crearcuenta.h"
#include "usermanager.h"
#include "menuinicio.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QLabel>
#include <fstream>
#include <sstream>

Login::Login(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - Acceso de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/login_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QString estiloInputs = "QLineEdit {"
                           "background-color: rgba(25, 20, 15, 210);"
                           "border: 2px solid #d4af37;"
                           "border-radius: 8px;"
                           "color: #e6dfc8;"
                           "font-family: 'Georgia';"
                           "font-size: 16px;"
                           "padding-left: 12px;"
                           "selection-background-color: #d4af37;"
                           "}";

    int xCentro = 475;
    int anchoBloque = 330;

    QLabel *lblLabelUsuario = new QLabel("USUARIO", this);
    lblLabelUsuario->setGeometry(xCentro, 290, anchoBloque, 22);
    lblLabelUsuario->setStyleSheet("font-family: 'Georgia'; font-size: 13px; color: #d4af37; font-weight: bold; background: transparent;");

    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(xCentro, 315, anchoBloque, 48);
    txtUsuario->setPlaceholderText("Ingresa tu usuario");
    txtUsuario->setStyleSheet(estiloInputs);

    QLabel *lblLabelContrasena = new QLabel("CONTRASEÑA", this);
    lblLabelContrasena->setGeometry(xCentro, 385, anchoBloque, 22);
    lblLabelContrasena->setStyleSheet("font-family: 'Georgia'; font-size: 13px; color: #d4af37; font-weight: bold; background: transparent;");

    txtContrasena = new QLineEdit(this);
    txtContrasena->setGeometry(xCentro, 410, anchoBloque, 48);
    txtContrasena->setEchoMode(QLineEdit::Password);
    txtContrasena->setPlaceholderText("Ingresa tu contraseña");
    txtContrasena->setStyleSheet(estiloInputs);

    btnEntrar = new QPushButton(this);
    btnEntrar->setGeometry(xCentro, 480, anchoBloque, 75);
    QPixmap pixmapBtn(":/btns/boton_entrar.png");
    btnEntrar->setIcon(QIcon(pixmapBtn));
    btnEntrar->setIconSize(btnEntrar->size());
    btnEntrar->setStyleSheet("QPushButton { border: none; background: transparent; } QPushButton:hover { filter: brightness(1.2); }");

    lblRegistrarse = new QLabel(this);
    lblRegistrarse->setGeometry(xCentro, 570, anchoBloque, 32);
    lblRegistrarse->setText("<a href='registrar' style='color: #ffd700; text-decoration: none; font-weight: bold;'>¿No tienes cuenta? Regístrate aquí</a>");
    lblRegistrarse->setAlignment(Qt::AlignCenter);
    lblRegistrarse->setStyleSheet("font-family: 'Georgia'; font-size: 14px; background: rgba(20, 12, 8, 0.7); border-radius: 4px; padding: 2px;");

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 80, 80);
    btnRegresar->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_volver_pequeno.png);"
        "    border: none;"
        "    background: transparent;"
        "}"
        "QPushButton:hover {"
        "    filter: brightness(1.25);"
        "}"
        );

    connect(lblRegistrarse, &QLabel::linkActivated, this, &Login::onRegistrarClicked);
    connect(btnEntrar, &QPushButton::clicked, this, &Login::onEntrarClicked);
    connect(btnRegresar, &QPushButton::clicked, this, &Login::regresar);
}

Login::~Login() {}

void Login::onEntrarClicked() {
    QString usuario = txtUsuario->text().trimmed();
    QString contrasena = txtContrasena->text();

    if (usuario.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor, ingresa tu usuario y contraseña.");
        return;
    }

    bool accesoConcedido = UserManager::verificarCredenciales(usuario.toStdString(), contrasena.toStdString());

    if (accesoConcedido) {
        MenuPrincipal *menuPrincipal = new MenuPrincipal(nullptr, usuario);
        menuPrincipal->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Error de Acceso", "Usuario o contraseña incorrectos.");
    }
}

void Login::onRegistrarClicked() {
    CrearCuenta *crearCuentaWin = new CrearCuenta();
    crearCuentaWin->show();
    this->close();
}

void Login::regresar(){
    MenuInicio *inicio = new MenuInicio();
    inicio->show();
    this->close();
}