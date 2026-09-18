#include "menuinicio.h"
#include "login.h"
#include "crearcuenta.h"
#include "inicioscreen.h"
#include <QPixmap>
#include <QIcon>

MenuInicio::MenuInicio(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Menú de Inicio");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/inicio_screen_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnIniciarSesion = new QPushButton(this);
    btnIniciarSesion->setGeometry(100, 420, 280, 55);
    QPixmap pixmapBtn1(":/imagenes/iniciar_sesion_boton.png");
    btnIniciarSesion->setIcon(QIcon(pixmapBtn1));
    btnIniciarSesion->setIconSize(btnIniciarSesion->size());
    btnIniciarSesion->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnRegistrarse = new QPushButton(this);
    btnRegistrarse->setGeometry(420, 420, 280, 55);
    QPixmap pixmapBtn2(":/imagenes/registrarse_boton.png");
    btnRegistrarse->setIcon(QIcon(pixmapBtn2));
    btnRegistrarse->setIconSize(btnRegistrarse->size());
    btnRegistrarse->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 80, 80);
    btnRegresar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/btn_volver_pequeno.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );

    connect(btnIniciarSesion, &QPushButton::clicked, this, &MenuInicio::onIniciarSesionClicked);
    connect(btnRegistrarse, &QPushButton::clicked, this, &MenuInicio::onRegistrarseClicked);
    connect(btnRegresar, &QPushButton::clicked, this, &MenuInicio::regresar);
}

MenuInicio::~MenuInicio() {}

void MenuInicio::onIniciarSesionClicked() {
    Login *loginWin = new Login();
    loginWin->show();
    this->close();
}

void MenuInicio::onRegistrarseClicked() {
    CrearCuenta *crearCuentaWin = new CrearCuenta();
    crearCuentaWin->show();
    this->close();
}

void MenuInicio::regresar(){
    InicioScreen *inicio = new InicioScreen();
    inicio->show();
    this->close();
}