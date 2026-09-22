#include "modojuego.h"
#include "menuprincipal.h"
#include "menuniveles.h"
#include "ConfiguracionNivel4.h"
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QDebug>

ModoJuego::ModoJuego(QWidget *parent)
    : QWidget(parent)
    , btnModoHistoria(nullptr)
    , btnModoLibre(nullptr)
    , btnVolver(nullptr)
    , menuAnterior(nullptr)
{
    setFixedSize(1280, 720);
    move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
    setFocusPolicy(Qt::StrongFocus);

    imgFondo.load(":/imagenes/menu_principal_fondo.jpg");

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(20, 20, 80, 80);
    btnVolver->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_volver_pequeno.png);"
        "    border: none;"
        "}"
        "QPushButton:hover { opacity: 0.8; }"
        );
    connect(btnVolver, &QPushButton::clicked, this, &ModoJuego::onVolverClicked);

    int anchoBtn = 380;
    int altoBtn = 68;
    int posX = (1280 - anchoBtn) / 2;
    int posYInicial = 280;
    int separacionY = 90;

    btnModoHistoria = new QPushButton(this);
    btnModoHistoria->setGeometry(posX, posYInicial, anchoBtn, altoBtn);
    btnModoHistoria->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_modo_historia.png);"
        "    border: none;"
        "}"
        "QPushButton:hover { opacity: 0.8; }"
        );
    connect(btnModoHistoria, &QPushButton::clicked, this, &ModoJuego::onModoHistoriaClicked);

    btnModoLibre = new QPushButton(this);
    btnModoLibre->setGeometry(posX, posYInicial + separacionY, anchoBtn, altoBtn);
    btnModoLibre->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_modo_libre.png);"
        "    border: none;"
        "}"
        "QPushButton:hover { opacity: 0.8; }"
        );
    connect(btnModoLibre, &QPushButton::clicked, this, &ModoJuego::onModoLibreClicked);
}

ModoJuego::~ModoJuego() {
}

void ModoJuego::setMenuAnterior(QWidget *menu) {
    menuAnterior = menu;
}

void ModoJuego::setUsuarioActual(const QString &usuario) {
    usuarioActual = usuario;
}

void ModoJuego::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    if (!imgFondo.isNull()) {
        painter.drawPixmap(rect(), imgFondo);
    }
}

void ModoJuego::onModoHistoriaClicked() {
    menuNiveles *niveles = new menuNiveles(this, true, usuarioActual);
    niveles->show();
    this->close();
}

void ModoJuego::onModoLibreClicked() {
    ConfiguracionNivel4 *nivel = new ConfiguracionNivel4();
    nivel->setUsuarioActual(usuarioActual);
    nivel->show();
    this->close();
}

void ModoJuego::onVolverClicked() {
    if (menuAnterior) {
        menuAnterior->show();
    } else {
        MenuPrincipal *menu = new MenuPrincipal();
        menu->show();
    }
    this->close();
}