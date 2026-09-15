#include "instruccionesgenerales.h"
#include "menuprincipal.h"
#include <QPixmap>

InstruccionesGenerales::InstruccionesGenerales(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - Manual de Expedición");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/instrucciones_generales_fondo.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(30, 30, 160, 65);

    btnVolver->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/btnVolverMenu.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );

    connect(btnVolver, &QPushButton::clicked, this, &InstruccionesGenerales::onVolverMenuClicked);
}

InstruccionesGenerales::~InstruccionesGenerales() {}

void InstruccionesGenerales::onVolverMenuClicked() {
    MenuPrincipal *menuPrincipal = new MenuPrincipal();
    menuPrincipal->show();
    this->close();
}