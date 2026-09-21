#include "nivel1.h"
#include "ui_gamewindow.h"

Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
    //cargamos aqui la img de fondo para el nivel 1
    fondo.load(":/imagenes/nivel1_fondo.png");

    cols=((width()-(2*marginX))/cellsize)-1;
    rows=((height()-marginY-120)/cellsize);
    crearMapa();
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

    dibujarGusano(painter);
    painter.setPen(Qt::NoPen);

    int foodX=marginX+(food.x()*cellsize);
    int foodY=marginY+(food.y()*cellsize);
    painter.drawPixmap(foodX, foodY, cellsize, cellsize, imgManzanaRoja);


    if(hayComidaDorada==true)
    {
        int doradaX=marginX+(comidaDorada.x()*cellsize);
        int doradaY=marginY+(comidaDorada.y()*cellsize);
        painter.drawPixmap(doradaX, doradaY, cellsize, cellsize, imgManzanaDorada);
    }

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

    if(juegoPausado==true)
    {
        painter.fillRect(rect(), QColor(0,0,0,150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        painter.drawText(QRect(0,330, width(), 60), Qt::AlignCenter, "PARTIDA PAUSADA");

    }
    if(gameover==true)
    {
        painter.fillRect(rect(), QColor(0,0,0,150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        if(nivelGanado)
        {
            painter.drawText(QRect(0, height()/2-130, width(), 50), Qt::AlignHCenter, "¡NIVEL COMPLETADO!");
            painter.setFont(QFont("Trebuchet MS", 14, QFont::Bold));
            painter.drawText(QRect(0, height()/2-95, width(), 20), Qt::AlignCenter,QString("Puntaje: %1").arg(puntuacion));
            painter.drawText(QRect(0, height()/2-72, width(), 20), Qt::AlignCenter,QString("Gemas: %1").arg(totalManzanasComidas()));
            painter.drawText(QRect(0, height()/2-49, width(), 20), Qt::AlignCenter,QString("Manzanas rojas: %1").arg(manzanasComidas));
            painter.drawText(QRect(0, height()/2-26, width(), 20), Qt::AlignCenter,QString("Manzanas doradas: %1").arg(doradasComidas));
        }
        else
        {
            painter.drawText(QRect(0, height()/2-35, width(), 50), Qt::AlignHCenter, "¡GAME OVER!");
            painter.setFont(QFont("Trebuchet MS", 14, QFont::Bold));
        }

        painter.drawText(QRect(0, height()/2, width(), 30), Qt::AlignCenter,ganoPremio ? "¡Ganó la insignia!" : "No ganó la insignia:(");

    }
    dibujarEncabezadoPartidaPendiente(painter);
}