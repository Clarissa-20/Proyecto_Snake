#include "login.h"
#include "menuprincipal.h"
#include "crearcuenta.h"
#include "usermanager.h"
#include "menuinicio.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <fstream>
#include <sstream>

Login::Login(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Acceso de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/login_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QString estiloInputs = "QLineEdit {"
                           "background: transparent;"
                           "border: none;"
                           "color: #e6dfc8;"
                           "font-family: 'Georgia';"
                           "font-size: 16px;"
                           "padding-left: 10px;"
                           "}";

    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(255, 230, 290, 45);
    txtUsuario->setPlaceholderText("Usuario");
    txtUsuario->setStyleSheet(estiloInputs);

    //ARREGLAR LO DE LOS CAMPOS DE DATOS

    txtContrasena = new QLineEdit(this);
    txtContrasena->setGeometry(255, 335, 290, 45);
    txtContrasena->setEchoMode(QLineEdit::Password);
    txtContrasena->setPlaceholderText("Contraseña");
    txtContrasena->setStyleSheet(estiloInputs);

    btnEntrar = new QPushButton(this);
    btnEntrar->setGeometry(265, 435, 270, 55);
    QPixmap pixmapBtn(":/btns/boton_entrar.png");
    btnEntrar->setIcon(QIcon(pixmapBtn));
    btnEntrar->setIconSize(btnEntrar->size());
    btnEntrar->setStyleSheet("QPushButton { border: none; background: transparent; }");

    lblRegistrarse = new QLabel(this);
    lblRegistrarse->setGeometry(250, 530, 300, 30);
    lblRegistrarse->setText("<a href='registrar' style='color: #d4af37; text-decoration: none;'>¿No tienes cuenta? Registrate aqui</a>");
    lblRegistrarse->setAlignment(Qt::AlignCenter);
    lblRegistrarse->setStyleSheet("font-family: 'Georgia'; font-size: 14px; background: transparent;");

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 80, 80);
    btnRegresar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btn_volver_pequeno.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
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
        MenuPrincipal *menuPrincipal = new MenuPrincipal();
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