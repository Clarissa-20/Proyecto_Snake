#include "menuprincipal.h"
#include <QPixmap>
#include <QIcon>
#include <QCoreApplication>
#include <QMessageBox>

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Menú Principal");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/menu_principal_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    int anchoBtn = 300;
    int altoBtn = 48;
    int posX = 250;
    int posYInicial = 265;
    int separacionY = 53;

    btnJugar = new QPushButton(this);
    btnJugar->setGeometry(posX, posYInicial, anchoBtn, altoBtn);
    btnJugar->setIcon(QIcon(":/imagenes/boton_jugar.png"));
    btnJugar->setIconSize(btnJugar->size());
    btnJugar->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnInstrucciones = new QPushButton(this);
    btnInstrucciones->setGeometry(posX, posYInicial + separacionY, anchoBtn, altoBtn);
    btnInstrucciones->setIcon(QIcon(":/imagenes/boton_instrucciones.png"));
    btnInstrucciones->setIconSize(btnInstrucciones->size());
    btnInstrucciones->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnTienda = new QPushButton(this);
    btnTienda->setGeometry(posX, posYInicial + (separacionY * 2), anchoBtn, altoBtn);
    btnTienda->setIcon(QIcon(":/imagenes/boton_tienda.png"));
    btnTienda->setIconSize(btnTienda->size());
    btnTienda->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnRecords = new QPushButton(this);
    btnRecords->setGeometry(posX, posYInicial + (separacionY * 3), anchoBtn, altoBtn);
    btnRecords->setIcon(QIcon(":/imagenes/boton_records.png"));
    btnRecords->setIconSize(btnRecords->size());
    btnRecords->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnConfiguracion = new QPushButton(this);
    btnConfiguracion->setGeometry(posX, posYInicial + (separacionY * 4), anchoBtn, altoBtn);
    btnConfiguracion->setIcon(QIcon(":/imagenes/boton_config.png"));
    btnConfiguracion->setIconSize(btnConfiguracion->size());
    btnConfiguracion->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnSalir = new QPushButton(this);
    btnSalir->setGeometry(posX, posYInicial + (separacionY * 5), anchoBtn, altoBtn);
    btnSalir->setIcon(QIcon(":/imagenes/boton_salir.png"));
    btnSalir->setIconSize(btnSalir->size());
    btnSalir->setStyleSheet("QPushButton { border: none; background: transparent; }");

    connect(btnJugar, &QPushButton::clicked, this, &MenuPrincipal::onJugarClicked);
    connect(btnInstrucciones, &QPushButton::clicked, this, &MenuPrincipal::onInstruccionesClicked);
    connect(btnTienda, &QPushButton::clicked, this, &MenuPrincipal::onTiendaClicked);
    connect(btnRecords, &QPushButton::clicked, this, &MenuPrincipal::onRecordsClicked);
    connect(btnConfiguracion, &QPushButton::clicked, this, &MenuPrincipal::onConfiguracionClicked);
    connect(btnSalir, &QPushButton::clicked, this, &MenuPrincipal::onSalirClicked);
}

MenuPrincipal::~MenuPrincipal() {}

void MenuPrincipal::onJugarClicked() {
    //vtn del mapa de los niveles
}

void MenuPrincipal::onInstruccionesClicked() {
    //vtn de instrucciones
}

void MenuPrincipal::onTiendaClicked() {
    //vtn de tienda
}

void MenuPrincipal::onRecordsClicked() {
    //vtn de récords
}

void MenuPrincipal::onConfiguracionClicked() {
    //vtn de configuración
}

void MenuPrincipal::onSalirClicked() {
    QCoreApplication::quit();
}