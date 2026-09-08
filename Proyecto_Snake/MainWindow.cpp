/*//#mainwindow.cpp
#include "mainwindow.h"
#include <QPixmap>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - El Templo Perdido");

    QLabel *labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/recursos/inicio_screen_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QPushButton *btnIniciar = new QPushButton(this);
    btnIniciar->setGeometry(250, 420, 300, 60);

    QPixmap pixmapBoton(":/recursos/boton_play.png");
    QIcon iconoBoton(pixmapBoton);
    btnIniciar->setIcon(iconoBoton);
    btnIniciar->setIconSize(btnIniciar->size());

    btnIniciar->setStyleSheet("QPushButton { border: none; background: transparent; }");

    // Conectar la señal del botón para pasar a la siguiente pantalla
    connect(btnIniciar, &QPushButton::clicked, this, &MainWindow::onIniciarAventuraClicked);
}*/