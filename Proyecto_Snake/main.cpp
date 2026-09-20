#include <QApplication>
//#include "configuracionnivel4.h"
#include "inicioscreen.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InicioScreen w;
    w.show();
    /*ConfiguracionNivel4 x;
    x.show();*/

    return a.exec();
}