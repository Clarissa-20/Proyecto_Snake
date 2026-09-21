#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MenuPrincipal : public QMainWindow {
    Q_OBJECT

public:
    MenuPrincipal(QWidget *parent = nullptr, const QString &usuario= "");
    ~MenuPrincipal();

private slots:
    void onJugarClicked();
    void onInstruccionesClicked();
    void onTiendaClicked();
    void onRecordsClicked();
    void onConfiguracionClicked();
    void miPerfil();
    void verManualUsuario();
    void regresar();

private:
    QLabel *labelFondo;
    QPushButton *btnJugar;
    QPushButton *btnInstrucciones;
    QPushButton *btnTienda;
    QPushButton *btnRecords;
    QPushButton *btnConfiguracion;
    QPushButton *iconoPerfil;
    QPushButton *btnManualUsuario;
    QPushButton *btnRegresar;
    QString usuarioActual;
};

#endif // MENUPRINCIPAL_H