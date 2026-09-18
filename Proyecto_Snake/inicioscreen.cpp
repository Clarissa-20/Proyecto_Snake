#include "inicioscreen.h"
#include "menuinicio.h"
#include "musicamanager.h"
#include <QPixmap>

InicioScreen::InicioScreen(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - El Templo Perdido");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/inicio_screen_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnIniciar = new QPushButton(this);
    btnIniciar->setGeometry(160, 250, 490, 200);
    btnIniciar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/boton_play.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );

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

    connect(btnIniciar, &QPushButton::clicked, this, &InicioScreen::onIniciarAventuraClicked);
    connect(btnRegresar, &QPushButton::clicked, this, &InicioScreen::regresar);

    MusicaManger::instance().playMusicaJuego();
}

InicioScreen::~InicioScreen() {}

void InicioScreen::onIniciarAventuraClicked() {
    MenuInicio *menuInicio = new MenuInicio();
    menuInicio->show();
    this->close();
}

void InicioScreen::regresar(){
    this->close();
}

