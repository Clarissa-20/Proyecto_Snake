/*#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainMenuWindow : public QMainWindow {
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private slots:
    void onJugarClicked();
    void onInstruccionesClicked();
    void onTiendaClicked();
    void onRecordsClicked();
    void onConfiguracionClicked();
    void onSalirClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnJugar;
    QPushButton *btnInstrucciones;
    QPushButton *btnTienda;
    QPushButton *btnRecords;
    QPushButton *btnConfiguracion;
    QPushButton *btnSalir;
};

#endif // MAINMENUWINDOW_H*/