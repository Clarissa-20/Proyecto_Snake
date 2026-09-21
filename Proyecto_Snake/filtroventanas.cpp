#include "filtroventanas.h"
#include <QWidget>
#include <QDialog>
#include <QScreen>
#include <QGuiApplication>

FiltroVentanas::FiltroVentanas(QObject *parent)
    : QObject(parent)
{
}

bool FiltroVentanas::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *w = qobject_cast<QWidget*>(obj);
    if (w == nullptr || w->isWindow() == false ||
        w->windowType() != Qt::Window || qobject_cast<QDialog*>(w) != nullptr)
    {
        return false;
    }

    switch (event->type())
    {
    case QEvent::Polish:
        // Antes de mostrarse: barra de título + minimizar, sin botón de cerrar,
        // y siempre por encima de la barra de tareas
        if (w->property("_configurada").toBool() == false)
        {
            w->setProperty("_configurada", true);
            w->setWindowFlags(Qt::Window
                              | Qt::CustomizeWindowHint
                              | Qt::WindowTitleHint
                              | Qt::WindowSystemMenuHint
                              | Qt::WindowMinimizeButtonHint
                              | Qt::WindowStaysOnTopHint);
        }
        break;

    case QEvent::Show:
    {
        // Solo se centra en la primera vez que se muestra. Así, al restaurar
        // la ventana desde la barra de tareas (minimizar) no se mueve de sitio.
        if (w->property("_centrada").toBool() == false)
        {
            w->setProperty("_centrada", true);

            QScreen *pantalla = w->screen();
            if (pantalla == nullptr)
            {
                pantalla = QGuiApplication::primaryScreen();
            }
            QRect g = pantalla->geometry();

            // frameSize() incluye la barra de título; así se centra la ventana completa
            QSize marco = w->frameSize();
            int x = g.x() + (g.width() - marco.width()) / 2;
            int y = g.y() + (g.height() - marco.height()) / 2;

            // Si la ventana es tan grande como la pantalla, que no se salga por arriba/izquierda
            if (x < g.x()) x = g.x();
            if (y < g.y()) y = g.y();

            w->move(x, y);
        }
        w->raise();
        w->activateWindow();
        break;
    }

    case QEvent::Close:
        // Cierres del sistema: se ignoran. Los close() por código no son espontáneos.
        if (event->spontaneous())
        {
            event->ignore();
            return true;
        }
        break;

    default:
        break;
    }
    return false;
}