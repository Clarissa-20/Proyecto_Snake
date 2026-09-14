#include "menuniveles.h"
#include <QPainter>
#include "instruccionesnivel.h"

menuNiveles::menuNiveles(QWidget *parent)
    : QWidget(parent),
    ventanaNivel1(nullptr),
    ventanaNivel2(nullptr),
    ventanaNivel3(nullptr)
{
    setWindowTitle("Mapa de niveles");
    fondoMenu.load(":/imagenes/mapaNiveles.png");

    QScreen *pantalla= QGuiApplication::primaryScreen();
    QRect geometriaPantalla= pantalla->geometry();
    this->setGeometry(geometriaPantalla);


    btnNivel3= new QPushButton(this);
    btnNivel1= new QPushButton(this);
    btnNivel2= new QPushButton(this);


    btnNivel1->setGeometry(410,565, 240,270);
    btnNivel2->setGeometry(875,450, 220,250);
    btnNivel3->setGeometry(468,358, 200,230);

    btnNivel1->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/imagenes/monoNivel1.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/imagenes/monoNivel1.png);"
        "}"
        );
    btnNivel2->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/imagenes/monoNivel2.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/imagenes/monoNivel2.png);"
        "}"
        );
    btnNivel3->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/imagenes/monoNivel3.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/imagenes/monoNivel3.png);"
        "}"
        );

    connect(btnNivel1, &QPushButton::clicked, this, [this](){mostrarInstrucciones(1);});
    connect(btnNivel2, &QPushButton::clicked, this, [this](){mostrarInstrucciones(2);});
    connect(btnNivel3, &QPushButton::clicked, this, [this](){mostrarInstrucciones(3);});

}

void menuNiveles::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(!fondoMenu.isNull())
    {
        painter.drawPixmap(rect(), fondoMenu);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }
}

void menuNiveles::mostrarInstrucciones(int nivel)
{
    InstruccionesNivel *ventanaInstrucciones= new InstruccionesNivel(nivel, this);
    ventanaInstrucciones->setAttribute(Qt::WA_DeleteOnClose);
    ventanaInstrucciones->show();
    this->hide();
}

void menuNiveles::abrirNivel1()
{
    if(ventanaNivel1==nullptr)
    {
        ventanaNivel1= new Nivel1();
        ventanaNivel1->setAttribute(Qt::WA_DeleteOnClose);
    }
    ventanaNivel1->show();
    this->hide();
}

void menuNiveles::abrirNivel2()
{
    if(ventanaNivel2==nullptr)
    {
        ventanaNivel2= new Nivel2();
        ventanaNivel2->setAttribute(Qt::WA_DeleteOnClose);
    }
    ventanaNivel2->show();
    this->hide();
}

void menuNiveles::abrirNivel3()
{
    if(ventanaNivel3==nullptr)
    {
        ventanaNivel3= new Nivel3();
        ventanaNivel3->setAttribute(Qt::WA_DeleteOnClose);
    }
    ventanaNivel3->show();
    this->hide();
}