#include "nivel1.h"
#include "ui_gamewindow.h"

Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
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
        painter.fillRect(rect(), QColor(0,0,0,180));

        int panelW = 460;
        int panelH = nivelGanado ? 520 : 340;
        int panelX = (width() - panelW) / 2;
        int panelY = (height() - panelH) / 2;

        painter.setBrush(QColor(30, 22, 14, 230));
        painter.setPen(QPen(QColor(212, 175, 55), 3));
        painter.drawRoundedRect(panelX, panelY, panelW, panelH, 16, 16);

        if(nivelGanado)
        {
            painter.setPen(QColor(255, 215, 0));
            painter.setFont(QFont("Trebuchet MS", 26, QFont::Bold));
            painter.drawText(QRect(panelX, panelY + 20, panelW, 40), Qt::AlignCenter, "¡NIVEL COMPLETADO!");

            painter.setPen(QColor(244, 232, 193));
            painter.setFont(QFont("Segoe UI", 12, QFont::Bold));
            int startStatsY = panelY + 68;
            int lineHeight = 21;
            painter.drawText(QRect(panelX, startStatsY, panelW, 20), Qt::AlignCenter, QString("Puntaje: %1").arg(puntuacion));
            painter.drawText(QRect(panelX, startStatsY + lineHeight, panelW, 20), Qt::AlignCenter, QString("Gemas: %1").arg(totalManzanasComidas()));
            painter.drawText(QRect(panelX, startStatsY + lineHeight*2, panelW, 20), Qt::AlignCenter, QString("Manzanas rojas: %1").arg(manzanasComidas));
            painter.drawText(QRect(panelX, startStatsY + lineHeight*3, panelW, 20), Qt::AlignCenter, QString("Manzanas doradas: %1").arg(doradasComidas));

            painter.setPen(QColor(212, 175, 55));
            painter.setFont(QFont("Segoe UI", 11, QFont::Bold));
            painter.drawText(QRect(panelX, panelY + 160, panelW, 20), Qt::AlignCenter, ganoPremio ? "¡Ganó la insignia!" : "No ganó la insignia:(");

            QPixmap imgInsignia(":/imagenes/insignia_1.png");
            QPixmap imgMapa(":/imagenes/map_piece_1.png");

            int slotSize = 68;
            int slotY = panelY + 190;

            int slotInsigniaX = panelX + (panelW / 2) - 85;
            painter.setBrush(QColor(20, 15, 10, 180));
            painter.setPen(QPen(QColor(139, 115, 85), 1));
            painter.drawRoundedRect(slotInsigniaX, slotY, slotSize, slotSize, 8, 8);
            if(!imgInsignia.isNull()) {
                painter.drawPixmap(slotInsigniaX + 8, slotY + 8, slotSize - 16, slotSize - 16, imgInsignia);
            }
            painter.setPen(QColor(224, 208, 176));
            painter.setFont(QFont("Segoe UI", 9));
            painter.drawText(QRect(slotInsigniaX, slotY + slotSize + 3, slotSize, 16), Qt::AlignCenter, "Insignia");

            int slotMapaX = panelX + (panelW / 2) + 17;
            painter.setBrush(QColor(20, 15, 10, 180));
            painter.setPen(QPen(QColor(139, 115, 85), 1));
            painter.drawRoundedRect(slotMapaX, slotY, slotSize, slotSize, 8, 8);
            if(!imgMapa.isNull()) {
                painter.drawPixmap(slotMapaX + 8, slotY + 8, slotSize - 16, slotSize - 16, imgMapa);
            }
            painter.setPen(QColor(224, 208, 176));
            painter.drawText(QRect(slotMapaX, slotY + slotSize + 3, slotSize, 16), Qt::AlignCenter, "Parte Mapa");
        }
        else
        {
            painter.setPen(QColor(255, 77, 77));
            painter.setFont(QFont("Trebuchet MS", 26, QFont::Bold));
            painter.drawText(QRect(panelX, panelY + 75, panelW, 40), Qt::AlignCenter, "¡GAME OVER!");

            painter.setPen(QColor(244, 232, 193));
            painter.setFont(QFont("Segoe UI", 13));
            painter.drawText(QRect(panelX, panelY + 140, panelW, 30), Qt::AlignCenter, ganoPremio ? "¡Ganó la insignia!" : "No ganó la insignia:(");
        }
    }

    dibujarEncabezadoPartidaPendiente(painter);
}