/*#include "menuinicio.h"
#include <QPixmap>
#include <QIcon>

MenuInicioWindow::MenuInicioWindow(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - El Templo Perdido");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/recursos/inicio_scree_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnIniciarSesion = new QPushButton(this);
    btnIniciarSesion->setGeometry(100, 420, 280, 55);
    QPixmap pixmapBtn1(":/recursos/iniciar_sesion_boton.png");
    btnIniciarSesion->setIcon(QIcon(pixmapBtn1));
    btnIniciarSesion->setIconSize(btnIniciarSesion->size());
    btnIniciarSesion->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnRegistrarse = new QPushButton(this);
    btnRegistrarse->setGeometry(420, 420, 280, 55);
    QPixmap pixmapBtn2(":/recursos/registrarse_boton.png");
    btnRegistrarse->setIcon(QIcon(pixmapBtn2));
    btnRegistrarse->setIconSize(btnRegistrarse->size());
    btnRegistrarse->setStyleSheet("QPushButton { border: none; background: transparent; }");

    connect(btnIniciarSesion, &QPushButton::clicked, this, &MenuInicioWindow::onIniciarSesionClicked);
    connect(btnRegistrarse, &QPushButton::clicked, this, &MenuInicioWindow::onRegistrarseClicked);
}

MenuInicioWindow::~MenuInicioWindow() {
}

void MenuInicioWindow::onIniciarSesionClicked() {
    // Lógica para abrir la ventana de login o autenticación
}

void MenuInicioWindow::onRegistrarseClicked() {
    // Lógica para abrir la ventana de registro de usuario
}*/