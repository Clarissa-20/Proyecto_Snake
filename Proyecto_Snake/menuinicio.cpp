#include "menuinicio.h"
#include "login.h"
#include "crearcuenta.h"
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

    connect(btnIniciarSesion, &QPushButton::clicked, this, &MenuInicio::onIniciarSesionClicked);
    connect(btnRegistrarse, &QPushButton::clicked, this, &MenuInicio::onRegistrarseClicked);
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