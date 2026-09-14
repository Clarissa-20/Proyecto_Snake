#ifndef INSTRUCCIONESNIVEL_H
#define INSTRUCCIONESNIVEL_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include "menuniveles.h"

class InstruccionesNivel : public QWidget
{
    Q_OBJECT
public:
    explicit InstruccionesNivel(int nivel, menuNiveles *menuPadre, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void volverAlMenu();
    void comenzarNivel();

private:
    int nivelSeleccionado;
    menuNiveles *menuPadre;
    QPixmap fondoInstrucciones;
    QPushButton *btnVolver;
    QPushButton *btnComenzar;
};

#endif // INSTRUCCIONESNIVEL_H
