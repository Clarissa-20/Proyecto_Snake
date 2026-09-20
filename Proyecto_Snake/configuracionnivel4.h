#ifndef CONFIGURACIONNIVEL4_H
#define CONFIGURACIONNIVEL4_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class ConfiguracionNivel4 : public QWidget
{
    Q_OBJECT
public:
    explicit ConfiguracionNivel4(QWidget *parent = nullptr);

private slots:
    void onComenzarClicked();

private:
    QRadioButton *radioMurosInfinitos;
    QRadioButton *radioMurosMortales;
    QButtonGroup *grupoMuros;

    QRadioButton *radioBloquesEstaticos;
    QRadioButton *radioBloquesDinamicos;
    QButtonGroup *grupoBloques;

    QSpinBox *spinCantidadBloques;
    QSpinBox *spinSkin;

    QPushButton *btnComenzar;
};

#endif // CONFIGURACIONNIVEL4_H
