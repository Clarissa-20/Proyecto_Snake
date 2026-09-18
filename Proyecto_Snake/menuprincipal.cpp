#include "menuprincipal.h"
#include "instruccionesgenerales.h"
#include "menuNiveles.h"
#include "tienda.h"
#include "inicioscreen.h"
#include <QPixmap>
#include <QIcon>
#include <QCoreApplication>
#include <QMessageBox>
#include "ranking.h"

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

    //NIVEL LIBRE
    // btnSalir = new QPushButton(this);
    // btnSalir->setGeometry(posX, posYInicial + (separacionY * 5), anchoBtn, altoBtn);
    // btnSalir->setIcon(QIcon(":/imagenes/boton_salir.png"));
    // btnSalir->setIconSize(btnSalir->size());
    // btnSalir->setStyleSheet("QPushButton { border: none; background: transparent; }");

    iconoPerfil = new QPushButton(this);
    iconoPerfil->setGeometry(710, 20, 80, 80);
    iconoPerfil->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/icono_miPerfil.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );

    btnManualUsuario = new QPushButton(this);
    btnManualUsuario->setGeometry(710, 510, 80, 80);
    btnManualUsuario->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/icono_manualUsuario.png);"
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

    connect(btnJugar, &QPushButton::clicked, this, &MenuPrincipal::onJugarClicked);
    connect(btnInstrucciones, &QPushButton::clicked, this, &MenuPrincipal::onInstruccionesClicked);
    connect(btnTienda, &QPushButton::clicked, this, &MenuPrincipal::onTiendaClicked);
    connect(btnRecords, &QPushButton::clicked, this, &MenuPrincipal::onRecordsClicked);
    connect(btnConfiguracion, &QPushButton::clicked, this, &MenuPrincipal::onConfiguracionClicked);
    //connect(btnSalir, &QPushButton::clicked, this, &MenuPrincipal::onSalirClicked); NIVEL LIBRE
    connect(iconoPerfil, &QPushButton::clicked, this, &MenuPrincipal::miPerfil);
    connect(btnManualUsuario, &QPushButton::clicked, this, &MenuPrincipal::verManualUsuario);
    connect(btnRegresar, &QPushButton::clicked, this, &MenuPrincipal::regresar);
}

MenuPrincipal::~MenuPrincipal() {}

void MenuPrincipal::onJugarClicked() {
    menuNiveles *niveles = new menuNiveles(this, true);
    niveles->show();
    this->close();
}

void MenuPrincipal::onInstruccionesClicked() {
    InstruccionesGenerales *instrucciones = new InstruccionesGenerales();
    instrucciones->show();
    this->close();
}

void MenuPrincipal::onTiendaClicked() {
    Tienda *tienda = new Tienda();
    tienda->show();
    this->close();
}

void MenuPrincipal::onRecordsClicked() {
    Ranking *ranking= new Ranking(this, nullptr);
    ranking->setAttribute(Qt::WA_DeleteOnClose);
    ranking->show();
    this->hide();
}

void MenuPrincipal::onConfiguracionClicked() {
    //vtn de configuración
}

void MenuPrincipal::miPerfil(){
    //vtn de mi perfil
}

void MenuPrincipal::verManualUsuario(){
    //vtn manual usuario
}

//poner el boton de jugar modo libre
//cambiar el boton de salir a la flecha

void MenuPrincipal::nivelLibre(){

}

void MenuPrincipal::regresar() {
    InicioScreen *inicio = new InicioScreen();
    inicio->show();
    this->close();
}


//presentacion: mucho del manual de usuario, parte del dis;o, que se va a esperar, dinamica del juego como tal, vender el juego