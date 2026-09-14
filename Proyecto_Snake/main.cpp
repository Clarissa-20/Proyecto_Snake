#include <QApplication>
//#include "nivel1.h"
//#include "nivel2.h"
//#include "nivel3.h"
#include "menuniveles.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Nivel3 w;
    //w.show();
    menuNiveles menu;
    menu.showFullScreen();
    return a.exec();
}

/*#include <QApplication>
#include "inicioscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InicioScreen w;
    w.show();

    return a.exec();
}*/