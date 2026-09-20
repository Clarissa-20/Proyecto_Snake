#include "configuracion.h"
#include "menuprincipal.h"
#include "musicamanager.h"
#include <QUrl>

int Configuracion::tipoControlGlobal = 0;
int Configuracion::volAmbienteGlobal = 80;
int Configuracion::volEfectosGlobal = 80;

Configuracion::Configuracion(QWidget *parent)
    : QWidget(parent),
    tipoControlActual(tipoControlGlobal),
    volAmbiente(volAmbienteGlobal),
    volEfectos(volEfectosGlobal) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake Avanzado - Ajustes");

    fondoLabel = new QLabel(this);
    fondoLabel->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/config_fondo.png");
    fondoLabel->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(30, 25, 70, 70);
    btnRegresar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btn_volver_pequeno.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );
    connect(btnRegresar, &QPushButton::clicked, this, &Configuracion::regresar);

    QString estiloRadio = "QRadioButton { color: #f4e8c1; font-family: 'Georgia'; font-size: 20px; font-weight: bold; spacing: 12px; }"
                          "QRadioButton::indicator { width: 26px; height: 26px; }";

    rbFlechas = new QRadioButton("Flechas del teclado", this);
    rbWasd = new QRadioButton("WASD", this);
    rbFlechas->setStyleSheet(estiloRadio);
    rbWasd->setStyleSheet(estiloRadio);

    rbFlechas->setChecked(tipoControlActual == 0);
    rbWasd->setChecked(tipoControlActual == 1);

    rbFlechas->setGeometry(210, 330, 320, 40);
    rbWasd->setGeometry(210, 440, 320, 40);

    connect(rbFlechas, &QRadioButton::toggled, this, [=](bool checked){ if(checked) onControlChanged(0); });
    connect(rbWasd, &QRadioButton::toggled, this, [=](bool checked){ if(checked) onControlChanged(1); });

    QString estiloTextoAudio = "QLabel { color: #f4e8c1; font-family: 'Georgia'; font-size: 18px; font-weight: bold; background: transparent; }";

    lblTextoMusica = new QLabel("Música de ambientación", this);
    lblTextoMusica->setStyleSheet(estiloTextoAudio);
    lblTextoMusica->setGeometry(750, 300, 320, 30);

    sliderAmbiente = new QSlider(Qt::Horizontal, this);
    sliderAmbiente->setRange(0, 100);
    sliderAmbiente->setValue(volAmbiente);
    sliderAmbiente->setGeometry(750, 340, 340, 30);

    lblTextoEfectos = new QLabel("Efectos de sonido", this);
    lblTextoEfectos->setStyleSheet(estiloTextoAudio);
    lblTextoEfectos->setGeometry(750, 410, 320, 30);

    sliderEfectos = new QSlider(Qt::Horizontal, this);
    sliderEfectos->setRange(0, 100);
    sliderEfectos->setValue(volEfectos);
    sliderEfectos->setGeometry(750, 450, 340, 30);

    QString estiloSlider = "QSlider::groove:horizontal { border: 1px solid #b8860b; height: 10px; background: #2b1a0c; border-radius: 5px; }"
                           "QSlider::handle:horizontal { background: #ffd700; border: 1px solid #b8860b; width: 22px; margin: -6px 0; border-radius: 11px; }";
    sliderAmbiente->setStyleSheet(estiloSlider);
    sliderEfectos->setStyleSheet(estiloSlider);

    connect(sliderAmbiente, &QSlider::valueChanged, this, &Configuracion::onVolumenAmbienteChanged);
    connect(sliderEfectos, &QSlider::valueChanged, this, &Configuracion::onVolumenEfectosChanged);

    MusicaManager::instance().setVolumenGlobalPorcentaje(volAmbiente);
    MusicaManager::instance().setVolumenNivelesPorcentaje(volAmbiente);
}

Configuracion::~Configuracion() {}

void Configuracion::onControlChanged(int id) {
    tipoControlActual = id;
    Configuracion::tipoControlGlobal = id;
}

void Configuracion::onVolumenAmbienteChanged(int valor) {
    volAmbiente = valor;
    Configuracion::volAmbienteGlobal = valor;
    MusicaManager::instance().setVolumenGlobalPorcentaje(valor);
    MusicaManager::instance().setVolumenNivelesPorcentaje(valor);
}

void Configuracion::onVolumenEfectosChanged(int valor) {
    volEfectos = valor;
    Configuracion::volEfectosGlobal = valor;
}

void Configuracion::regresar() {
    MenuPrincipal *menu = new MenuPrincipal();
    menu->show();
    this->close();
}