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
        if (w->property("_centrada").toBool() == false)
        {
            w->setProperty("_centrada", true);

            QScreen *pantalla = w->screen();
            if (pantalla == nullptr)
            {
                pantalla = QGuiApplication::primaryScreen();
            }
            QRect g = pantalla->geometry();

            QSize marco = w->frameSize();
            int x = g.x() + (g.width() - marco.width()) / 2;
            int y = g.y() + (g.height() - marco.height()) / 2;

            if (x < g.x()) x = g.x();
            if (y < g.y()) y = g.y();

            w->move(x, y);
        }
        w->raise();
        w->activateWindow();
        break;
    }

    case QEvent::Close:
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