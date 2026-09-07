#include "nivel1.h"
#include "ui_gamewindow.h"
//#include <QDebug>
//#include <QPainter>

Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
    //cargamos aqui la img de fondo para el nivel 1
    fondo.load(":/imagenes/nivel1_fondo.png");

    cols=((width()-(2*marginX))/cellsize)-1;
    rows=((height()-marginY-120)/cellsize);
    crearMapa();
    cabeza=new Nodo(5, 5);

    iniciarSistemaDeManzanas();
    //timer= new QTimer(this);

    //connect(timer, &QTimer::timeout, this, &Nivel1::gameloop);

    timer->start(150); //aqui se modifica la rapidez del guano entre mas alto mas lento

    //connect(retryButton, &QPushButton::clicked, this, &Nivel1::resetGame);

}

void Nivel1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!fondo.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), fondo);
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    // Cuadro semitransparente para delimitar el área jugable
    painter.setBrush(QColor(0, 0, 0, 140));
    painter.setPen(QPen(QColor(120, 110, 100), 2));
    painter.drawRect(marginX, marginY, cols * cellsize, rows * cellsize);

    Nodo* actual = cabeza;
    bool esCabeza=true;
    while (actual != nullptr)
    {
        if(esCabeza==true)
        {
            painter.setBrush(QColor(0, 255, 180));
            esCabeza=false;
        }
        else
        {
            painter.setBrush(QColor(0, 180, 0));
        }
        painter.setPen(Qt::NoPen);
        int posX = marginX + (actual->x * cellsize);
        int posY = marginY + (actual->y * cellsize);
        painter.drawRoundedRect(posX, posY, cellsize, cellsize, 5, 5);
        actual= actual->siguiente;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    int foodX = marginX + (food.x() * cellsize);
    int foodY = marginY + (food.y() * cellsize);
    painter.drawEllipse(foodX, foodY, cellsize, cellsize);


    if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255, 215, 0));
        int doradaX= marginX+(comidaDorada.x()*cellsize);
        int doradaY= marginY+(comidaDorada.y()*cellsize);
        painter.drawEllipse(doradaX, doradaY, cellsize, cellsize);
    }
    /*
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas Rojas: %1").arg(manzanasComidas));
    painter.drawText(10, 60, QString("Manzanas Doradas: %1").arg(doradasComidas));

    painter.drawText(10, 80, QString("Gemas: %1").arg(totalManzanasComidas()));
    painter.drawText(10, 100, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));
*/
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    int topY = 24;
    int bottomY = 40;

    QRect rect1Top(185, topY, 140, 18);
    QRect rect1Bottom(185, bottomY, 140, 18);
    painter.drawText(rect1Top, Qt::AlignCenter, QString("Gemas: %1").arg(totalManzanasComidas()));
    painter.drawText(rect1Bottom, Qt::AlignCenter, QString("Puntos: %1").arg(puntuacion));

    QRect rect2Top(335, topY, 140, 18);
    QRect rect2Bottom(335, bottomY, 140, 18);
    painter.drawText(rect2Top, Qt::AlignCenter, QString("Rojas: %1").arg(manzanasComidas));
    painter.drawText(rect2Bottom, Qt::AlignCenter, QString("Doradas: %1").arg(doradasComidas));

    QRect rect3(494, 22, 140, 36);
    painter.drawText(rect3, Qt::AlignCenter, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        painter.drawText(QRect(0, height()/2-30, width(), 50), Qt::AlignHCenter, nivelGanado?"¡NIVEL COMPLETADO!":"GAME OVER");

        painter.setFont(QFont("Trebuchet MS", 14, QFont::Bold));
        painter.drawText(QRect(0, height()/2, width(), 30), Qt::AlignCenter,ganoPremio ? "¡Premio de manzanas doradas obtenido!" : "Premio de doradas no obtenido");

    }
}