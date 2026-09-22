#include "inicioscreen.h"
#include "menuinicio.h"
#include "musicamanager.h"
#include <QPixmap>

InicioScreen::InicioScreen(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - El Templo Perdido");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/inicio_screen_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnIniciar = new QPushButton(this);
    btnIniciar->setGeometry(270, 420, 740, 200);
    btnIniciar->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/boton_play.png);"
        "    border: none;"
        "    background: transparent;"
        "}"
        "QPushButton:hover {"
        "    filter: brightness(1.25);"
        "}"
        );

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

    connect(btnIniciar, &QPushButton::clicked, this, &InicioScreen::onIniciarAventuraClicked);
    connect(btnRegresar, &QPushButton::clicked, this, &InicioScreen::regresar);

    MusicaManager::instance().playMusicaJuego();
}

InicioScreen::~InicioScreen() {}

void InicioScreen::onIniciarAventuraClicked() {
    MenuInicio *menuInicio = new MenuInicio();
    menuInicio->show();
    this->close();
}

void InicioScreen::setUsuario(const QString &usuario) {
    usuarioActual = usuario;
}

void InicioScreen::regresar(){
    this->close();
}

