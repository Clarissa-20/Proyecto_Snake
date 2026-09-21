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
    void setUsuarioActual(const QString &usuario);
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

    QString usuarioActual;
};

#endif // CONFIGURACIONNIVEL4_H
