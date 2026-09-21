#include <QApplication>
#include "inicioscreen.h"
#include "filtroventanas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.installEventFilter(new FiltroVentanas(&a));

    InicioScreen w;
    w.show();

    return a.exec();
}