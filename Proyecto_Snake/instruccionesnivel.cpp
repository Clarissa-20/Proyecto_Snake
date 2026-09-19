#include "instruccionesnivel.h"

InstruccionesNivel::InstruccionesNivel(int nivel, menuNiveles *menuPadre, QWidget *parent)
    : QWidget(parent),
    nivelSeleccionado(nivel),
    menuPadre(menuPadre)
{
    setWindowTitle("Instrucciones del nivel");
    setFixedSize(980,600);
    move(QGuiApplication::primaryScreen()->availableGeometry().center()-rect().center());

    switch(nivelSeleccionado)
    {
    case 1:
    {
        fondoInstrucciones.load(":/imagenes/instrucciones_nivel1.png");
        break;
    }
    case 2:
    {
        fondoInstrucciones.load(":/imagenes/instrucciones_nivel2.png");
        break;
    }
    case 3:
    {
        fondoInstrucciones.load(":/imagenes/instrucciones_nivel3.png");
        break;
    }
    default:
    {
        break;
    }
    }

    btnVolver= new QPushButton(this);
    btnComenzar= new QPushButton(this);

    btnVolver->setGeometry(270,480, 200,50);
    btnComenzar->setGeometry(510,480, 200, 50);

    btnVolver->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/btnVolverMenu.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/btnVolverMenu.png);"
        "}"
        );
    btnComenzar->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/btnComenzarNivel.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/btnComenzarNivel.png);"
        "}"
        );
    connect(btnVolver, &QPushButton::clicked, this, &InstruccionesNivel::volverAlMenu);
    connect(btnComenzar, &QPushButton::clicked, this, &InstruccionesNivel::comenzarNivel);
}

void InstruccionesNivel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!fondoInstrucciones.isNull())
    {
        painter.drawPixmap(rect(), fondoInstrucciones);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }
}

void InstruccionesNivel::volverAlMenu()
{
    if(menuPadre!=nullptr)
    {
        menuPadre->show();
    }
    this->close();
}

void InstruccionesNivel::comenzarNivel()
{
    if(menuPadre!=nullptr)
    {
        switch (nivelSeleccionado)
        {
        case 1:
        {
            menuPadre->abrirNivel1();
            break;
        }
        case 2:
        {
            menuPadre->abrirNivel2();
            break;
        }
        case 3:
        {
            menuPadre->abrirNivel3();
            break;
        }
        default:
            break;
        }
    }
    this->close();
}
