#include "configuracionnivel4.h"
#include "nivel4.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

ConfiguracionNivel4::ConfiguracionNivel4(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Configuración - Nivel Personalizado");
    setFixedSize(360, 340);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    QGroupBox *cajaMuros = new QGroupBox("Tipo de muros", this);
    QVBoxLayout *layoutMuros = new QVBoxLayout(cajaMuros);
    radioMurosInfinitos = new QRadioButton("Muros infinitos (atravesables)", cajaMuros);
    radioMurosMortales = new QRadioButton("Muros mortales", cajaMuros);
    radioMurosInfinitos->setChecked(true);
    grupoMuros = new QButtonGroup(this);
    grupoMuros->addButton(radioMurosInfinitos);
    grupoMuros->addButton(radioMurosMortales);
    layoutMuros->addWidget(radioMurosInfinitos);
    layoutMuros->addWidget(radioMurosMortales);

    QGroupBox *cajaBloques = new QGroupBox("Tipo de bloques", this);
    QVBoxLayout *layoutBloques = new QVBoxLayout(cajaBloques);
    radioBloquesEstaticos = new QRadioButton("Estáticos", cajaBloques);
    radioBloquesDinamicos = new QRadioButton("Dinámicos (se regeneran)", cajaBloques);
    radioBloquesEstaticos->setChecked(true);
    grupoBloques = new QButtonGroup(this);
    grupoBloques->addButton(radioBloquesEstaticos);
    grupoBloques->addButton(radioBloquesDinamicos);
    layoutBloques->addWidget(radioBloquesEstaticos);
    layoutBloques->addWidget(radioBloquesDinamicos);

    QHBoxLayout *layoutCantidad = new QHBoxLayout();
    QLabel *lblCantidad = new QLabel("Cantidad de bloques:", this);
    spinCantidadBloques = new QSpinBox(this);
    spinCantidadBloques->setRange(0, 60);
    spinCantidadBloques->setValue(10);
    layoutCantidad->addWidget(lblCantidad);
    layoutCantidad->addWidget(spinCantidadBloques);

    QHBoxLayout *layoutSkin = new QHBoxLayout();
    QLabel *lblSkin = new QLabel("Skin (0-6):", this);
    spinSkin = new QSpinBox(this);
    spinSkin->setRange(0, 6);
    spinSkin->setValue(0);
    layoutSkin->addWidget(lblSkin);
    layoutSkin->addWidget(spinSkin);

    btnComenzar = new QPushButton("Comenzar nivel", this);
    connect(btnComenzar, &QPushButton::clicked, this, &ConfiguracionNivel4::onComenzarClicked);

    layoutPrincipal->addWidget(cajaMuros);
    layoutPrincipal->addWidget(cajaBloques);
    layoutPrincipal->addLayout(layoutCantidad);
    layoutPrincipal->addLayout(layoutSkin);
    layoutPrincipal->addWidget(btnComenzar);
}

void ConfiguracionNivel4::onComenzarClicked()
{
    bool murosInfinitos   = radioMurosInfinitos->isChecked();
    bool bloquesEstaticos = radioBloquesEstaticos->isChecked();
    int cantidadBloques   = spinCantidadBloques->value();
    int skinSeleccionada  = spinSkin->value();

    Nivel4 *nivel4 = new Nivel4(murosInfinitos, bloquesEstaticos, cantidadBloques, skinSeleccionada);
    nivel4->setAttribute(Qt::WA_DeleteOnClose);
    nivel4->setUsuarioRetorno(usuarioActual);
    nivel4->iniciarPartida();
    nivel4->show();
    this->close();
}

void ConfiguracionNivel4::setUsuarioActual(const QString &usuario)
{
    usuarioActual=usuario;
}

