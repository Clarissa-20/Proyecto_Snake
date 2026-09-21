#include "manualusuario.h"
#include "menuprincipal.h"
#include <QPixmap>

ManualUsuario::ManualUsuario(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - Manual de Usuario");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/manualUsuario.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(30, 30, 160, 65);

    btnVolver->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnVolverMenu.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );

    connect(btnVolver, &QPushButton::clicked, this, &ManualUsuario::onVolverMenuClicked);
}

ManualUsuario::~ManualUsuario() {}

void ManualUsuario::setUsuario(const QString &usuario) {
    usuarioActual = usuario;
}

void ManualUsuario::onVolverMenuClicked() {
    MenuPrincipal *menuPrincipal = new MenuPrincipal(nullptr, usuarioActual);
    menuPrincipal->show();
    this->close();
}