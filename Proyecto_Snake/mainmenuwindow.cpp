/*#include "mainmenuwindow.h"
#include <QPixmap>
#include <QIcon>
#include <QCoreApplication>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Menú Principal");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/recursos/menu_principal_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    int anchoBtn = 320;
    int altoBtn = 48;
    int posX = 240;
    int posYInicial = 260;
    int separacionY = 56;

    btnJugar = new QPushButton(this);
    btnJugar->setGeometry(posX, posYInicial, anchoBtn, altoBtn);
    btnJugar->setIcon(QIcon(":/recursos/boton_jugar.png"));
    btnJugar->setIconSize(btnJugar->size());
    btnJugar->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnInstrucciones = new QPushButton(this);
    btnInstrucciones->setGeometry(posX, posYInicial + separacionY, anchoBtn, altoBtn);
    btnInstrucciones->setIcon(QIcon(":/recursos/boton_instrucciones.png"));
    btnInstrucciones->setIconSize(btnInstrucciones->size());
    btnInstrucciones->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnTienda = new QPushButton(this);
    btnTienda->setGeometry(posX, posYInicial + (separacionY * 2), anchoBtn, altoBtn);
    btnTienda->setIcon(QIcon(":/recursos/boton_tienda.png"));
    btnTienda->setIconSize(btnTienda->size());
    btnTienda->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnRecords = new QPushButton(this);
    btnRecords->setGeometry(posX, posYInicial + (separacionY * 3), anchoBtn, altoBtn);
    btnRecords->setIcon(QIcon(":/recursos/boton_records.png"));
    btnRecords->setIconSize(btnRecords->size());
    btnRecords->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnConfiguracion = new QPushButton(this);
    btnConfiguracion->setGeometry(posX, posYInicial + (separacionY * 4), anchoBtn, altoBtn);
    btnConfiguracion->setIcon(QIcon(":/recursos/boton_config.png"));
    btnConfiguracion->setIconSize(btnConfiguracion->size());
    btnConfiguracion->setStyleSheet("QPushButton { border: none; background: transparent; }");

    btnSalir = new QPushButton(this);
    btnSalir->setGeometry(posX, posYInicial + (separacionY * 5), anchoBtn, altoBtn);
    btnSalir->setIcon(QIcon(":/recursos/boton_salir.png"));
    btnSalir->setIconSize(btnSalir->size());
    btnSalir->setStyleSheet("QPushButton { border: none; background: transparent; }");

    connect(btnJugar, &QPushButton::clicked, this, &MainMenuWindow::onJugarClicked);
    connect(btnInstrucciones, &QPushButton::clicked, this, &MainMenuWindow::onInstruccionesClicked);
    connect(btnTienda, &QPushButton::clicked, this, &MainMenuWindow::onTiendaClicked);
    connect(btnRecords, &QPushButton::clicked, this, &MainMenuWindow::onRecordsClicked);
    connect(btnConfiguracion, &QPushButton::clicked, this, &MainMenuWindow::onConfiguracionClicked);
    connect(btnSalir, &QPushButton::clicked, this, &MainMenuWindow::onSalirClicked);
}

MainMenuWindow::~MainMenuWindow() {}

void MainMenuWindow::onJugarClicked() {
    // Abrir la ventana de selección de niveles o juego directamente
}

void MainMenuWindow::onInstruccionesClicked() {
    // Abrir ventana de instrucciones
}

void MainMenuWindow::onTiendaClicked() {
    // Abrir ventana de tienda
}

void MainMenuWindow::onRecordsClicked() {
    // Abrir ventana de récords (persistencia de archivos)
}

void MainMenuWindow::onConfiguracionClicked() {
    // Abrir ventana de opciones/configuración
}

void MainMenuWindow::onSalirClicked() {
    QCoreApplication::quit();
}*/