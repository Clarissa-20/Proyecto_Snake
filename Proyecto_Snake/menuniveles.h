#ifndef MENUNIVELES_H
#define MENUNIVELES_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>

#include "nivel1.h"
#include "nivel2.h"
#include "nivel3.h"

class menuNiveles : public QWidget
{
    Q_OBJECT //slots
public:
    explicit menuNiveles(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap fondoMenu;

    QPushButton *btnNivel1;
    QPushButton *btnNivel2;
    QPushButton *btnNivel3;
    QPushButton *btnVolver;
    QPushButton *btnSonido;

    bool sonidoActivado;
    Nivel1 *ventanaNivel1;
    Nivel2 *ventanaNivel2;
    Nivel3 *ventanaNivel3;

    void mostrarInstrucciones(int nivel);
public slots:
    void abrirNivel1();
    void abrirNivel2();
    void abrirNivel3();
    void alternarSonido();
    void volverAlMenu();
};

#endif // MENUNIVELES_H
