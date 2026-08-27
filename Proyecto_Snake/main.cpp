#include <QApplication>
#include "nivel1.h"
#include "nivel2.h"
#include "nivel3.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nivel3 w;
    w.show();
    return a.exec();
}

