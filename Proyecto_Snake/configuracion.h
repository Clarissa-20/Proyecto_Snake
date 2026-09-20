#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSlider>

class Configuracion : public QWidget {
    Q_OBJECT

public:
    explicit Configuracion(QWidget *parent = nullptr);
    ~Configuracion();

    static int tipoControlGlobal; // 0 = Flechas, 1 = WASD
    static int volAmbienteGlobal; // 0 a 100
    static int volEfectosGlobal;  // 0 a 100

signals:
    void volverMenuClicked();

private slots:
    void onControlChanged(int id);
    void onVolumenAmbienteChanged(int valor);
    void onVolumenEfectosChanged(int valor);
    void regresar();

private:
    QLabel *fondoLabel;
    QPushButton *btnRegresar;

    QRadioButton *rbFlechas;
    QRadioButton *rbWasd;
    QButtonGroup *grupoControles;
    int tipoControlActual;

    QLabel *lblTextoMusica;
    QLabel *lblTextoEfectos;
    QSlider *sliderAmbiente;
    QSlider *sliderEfectos;
    int volAmbiente;
    int volEfectos;
};

#endif // CONFIGURACION_H