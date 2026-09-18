#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MenuPrincipal : public QMainWindow {
    Q_OBJECT

public:
    MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:
    void onJugarClicked();
    void onInstruccionesClicked();
    void onTiendaClicked();
    void onRecordsClicked();
    void onConfiguracionClicked();
    //void onSalirClicked();
    void miPerfil();
    void verManualUsuario();
    void regresar();
    void nivelLibre();

private:
    QLabel *labelFondo;
    QPushButton *btnJugar;
    QPushButton *btnInstrucciones;
    QPushButton *btnTienda;
    QPushButton *btnRecords;
    QPushButton *btnConfiguracion;
    //QPushButton *btnSalir;
    QPushButton *iconoPerfil;
    QPushButton *btnManualUsuario;
    QPushButton *btnRegresar;
};

#endif // MENUPRINCIPAL_H