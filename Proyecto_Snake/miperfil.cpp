#include "miperfil.h"
#include "menuprincipal.h"
#include "usermanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MiPerfil::MiPerfil(QWidget *parent)
    : QWidget(parent)
    , menuAnterior(nullptr)
    , btnVolver(nullptr)
    , frameInfoUsuario(nullptr)
    , lblAvatarMarco(nullptr)
    , lblNombre(nullptr)
    , lblPuntaje(nullptr)
    , lblGemas(nullptr)
    , frameBloqueNiveles(nullptr)
    , frameBloqueInsignias(nullptr)
    , frameBloqueMapa(nullptr)
    , frameBloqueSkin(nullptr)
    , lblSkinImgBlock(nullptr)
    , lblSkinNameBlock(nullptr)
    , lblMapaStatus(nullptr)
    , lblInsStatus(nullptr)
{
    setFixedSize(1280, 720);
    move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
    setFocusPolicy(Qt::StrongFocus);

    // Cargar recursos base
    imgFondoPerfil.load(":/imagenes/miPerfil_fondo.png");

    if (!imgAvatarUser.load(":/imagenes/avatar_usuario.png")) {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
    }
    imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");

    // Botón volver (esquina superior izquierda)
    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(20, 20, 80, 80);
    btnVolver->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_volver_pequeno.png);"
        "    border: none;"
        "}"
        "QPushButton:hover { opacity: 0.85; }"
        );
    connect(btnVolver, &QPushButton::clicked, this, &MiPerfil::onVolverClicked);

    QString estiloTexto = "color: #2C1D11; font-weight: bold; font-family: 'Georgia'; background: transparent;";

    // --- TARJETA UNIFICADA DE DATOS DEL USUARIO ---
    frameInfoUsuario = new QFrame(this);
    frameInfoUsuario->setGeometry(200, 180, 880, 200);
    frameInfoUsuario->setStyleSheet(
        "background: rgba(45, 28, 15, 0.85);"
        "border: 2px solid #5A3A22;"
        "border-radius: 14px;"
        );

    QHBoxLayout *hTopLayout = new QHBoxLayout(frameInfoUsuario);
    hTopLayout->setContentsMargins(30, 22, 30, 22);
    hTopLayout->setSpacing(32);

    lblAvatarMarco = new QLabel(frameInfoUsuario);
    lblAvatarMarco->setFixedSize(150, 150);
    lblAvatarMarco->setAlignment(Qt::AlignCenter);
    lblAvatarMarco->setStyleSheet("background: rgba(0,0,0,0.25); border: 2px solid #7A4E31; border-radius: 12px;");
    if (!imgAvatarUser.isNull()) {
        lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    hTopLayout->addWidget(lblAvatarMarco, 0, Qt::AlignCenter);

    QVBoxLayout *vDatosLayout = new QVBoxLayout();
    vDatosLayout->setSpacing(14);
    vDatosLayout->setAlignment(Qt::AlignCenter);

    lblNombre = new QLabel("EXPLORADOR:\nCARGANDO...", frameInfoUsuario);
    lblNombre->setStyleSheet(estiloTexto + " font-size: 15pt; color: #F5E6D3;");
    lblNombre->setWordWrap(true);

    lblPuntaje = new QLabel("PUNTAJE TOTAL: 0", frameInfoUsuario);
    lblPuntaje->setStyleSheet(estiloTexto + " font-size: 13pt; color: #E2C290;");

    lblGemas = new QLabel("GEMAS ACUMULADAS: 0", frameInfoUsuario);
    lblGemas->setStyleSheet(estiloTexto + " font-size: 13pt; color: #E2C290;");

    vDatosLayout->addWidget(lblNombre);
    vDatosLayout->addWidget(lblPuntaje);
    vDatosLayout->addWidget(lblGemas);
    vDatosLayout->addStretch();
    hTopLayout->addLayout(vDatosLayout);
    hTopLayout->addStretch();

    // --- Estilo común para los 4 bloques inferiores grandes ---
    QString estiloMarcoBloque =
        "background: rgba(45, 28, 15, 0.85);"
        "border: 2px solid #5A3A22;"
        "border-radius: 12px;";

    int yBloques = 400;
    int hBloques = 285;
    int wBloque = 265;
    int startX = 80;
    int gap = 20;

    // --- Bloque 1: Niveles ---
    frameBloqueNiveles = new QFrame(this);
    frameBloqueNiveles->setGeometry(startX, yBloques, wBloque, hBloques);
    frameBloqueNiveles->setStyleSheet(estiloMarcoBloque);

    QVBoxLayout *layoutNiveles = new QVBoxLayout(frameBloqueNiveles);
    layoutNiveles->setContentsMargins(14, 18, 14, 18);
    layoutNiveles->setSpacing(14);
    QLabel *lblTituloNiveles = new QLabel("NIVELES", frameBloqueNiveles);
    lblTituloNiveles->setAlignment(Qt::AlignCenter);
    lblTituloNiveles->setStyleSheet("color: #E2C290; font-weight: bold; font-size: 13pt; background: transparent; border: none;");
    layoutNiveles->addWidget(lblTituloNiveles);

    for(int i=0; i<3; ++i) {
        QHBoxLayout *hItemNiv = new QHBoxLayout();
        hItemNiv->setSpacing(12);

        QLabel *lblN = new QLabel(QString("Nivel %1").arg(i+1), frameBloqueNiveles);
        lblN->setStyleSheet("color: #F5E6D3; font-size: 12pt; background: transparent; border: none;");

        lblNivelStatus[i] = new QLabel(frameBloqueNiveles);
        lblNivelStatus[i]->setFixedSize(30, 30);
        lblNivelStatus[i]->setAlignment(Qt::AlignCenter);

        hItemNiv->addStretch();
        hItemNiv->addWidget(lblN);
        hItemNiv->addWidget(lblNivelStatus[i]);
        hItemNiv->addStretch();
        layoutNiveles->addLayout(hItemNiv);
    }
    layoutNiveles->addStretch();

    // --- Bloque 2: Insignias ---
    int x2 = startX + wBloque + gap;
    frameBloqueInsignias = new QFrame(this);
    frameBloqueInsignias->setGeometry(x2, yBloques, wBloque, hBloques);
    frameBloqueInsignias->setStyleSheet(estiloMarcoBloque);
    QVBoxLayout *layoutInsignias = new QVBoxLayout(frameBloqueInsignias);
    layoutInsignias->setContentsMargins(14, 18, 14, 18);
    layoutInsignias->setSpacing(12);

    QLabel *lblTituloIns = new QLabel("INSIGNIAS", frameBloqueInsignias);
    lblTituloIns->setAlignment(Qt::AlignCenter);
    lblTituloIns->setStyleSheet("color: #E2C290; font-weight: bold; font-size: 13pt; background: transparent; border: none;");
    layoutInsignias->addWidget(lblTituloIns);

    QHBoxLayout *hIns = new QHBoxLayout();
    hIns->setAlignment(Qt::AlignCenter);
    hIns->setSpacing(10);
    for(int i=0; i<3; ++i) {
        lblInsImg[i] = new QLabel(frameBloqueInsignias);
        lblInsImg[i]->setFixedSize(70, 70);
        lblInsImg[i]->setAlignment(Qt::AlignCenter);
        hIns->addWidget(lblInsImg[i]);
    }
    layoutInsignias->addLayout(hIns);

    lblInsStatus = new QLabel("Desbloqueadas: 0 / 3", frameBloqueInsignias);
    lblInsStatus->setAlignment(Qt::AlignCenter);
    lblInsStatus->setStyleSheet("color: #F5E6D3; font-size: 12pt; font-weight: bold; background: transparent; border: none;");
    layoutInsignias->addWidget(lblInsStatus);
    layoutInsignias->addStretch();

    // --- Bloque 3: Mapa del Templo ---
    int x3 = x2 + wBloque + gap;
    frameBloqueMapa = new QFrame(this);
    frameBloqueMapa->setGeometry(x3, yBloques, wBloque, hBloques);
    frameBloqueMapa->setStyleSheet(estiloMarcoBloque);
    QVBoxLayout *layoutMapa = new QVBoxLayout(frameBloqueMapa);
    layoutMapa->setContentsMargins(14, 18, 14, 18);
    layoutMapa->setSpacing(12);

    QLabel *lblTituloMapa = new QLabel("MAPA DEL TEMPLO", frameBloqueMapa);
    lblTituloMapa->setAlignment(Qt::AlignCenter);
    lblTituloMapa->setStyleSheet("color: #E2C290; font-weight: bold; font-size: 13pt; background: transparent; border: none;");
    layoutMapa->addWidget(lblTituloMapa);

    QHBoxLayout *hMapaPieces = new QHBoxLayout();
    hMapaPieces->setAlignment(Qt::AlignCenter);
    hMapaPieces->setSpacing(12);
    for(int i=0; i<3; ++i) {
        lblMapaImg[i] = new QLabel(frameBloqueMapa);
        lblMapaImg[i]->setFixedSize(62, 62);
        lblMapaImg[i]->setAlignment(Qt::AlignCenter);
        hMapaPieces->addWidget(lblMapaImg[i]);
    }
    layoutMapa->addLayout(hMapaPieces);

    lblMapaStatus = new QLabel("Piezas recolectadas: 0 / 3", frameBloqueMapa);
    lblMapaStatus->setAlignment(Qt::AlignCenter);
    lblMapaStatus->setStyleSheet("color: #F5E6D3; font-size: 12pt; font-weight: bold; background: transparent; border: none;");
    layoutMapa->addWidget(lblMapaStatus);
    layoutMapa->addStretch();

    // --- Bloque 4: Skin Activa ---
    int x4 = x3 + wBloque + gap;
    frameBloqueSkin = new QFrame(this);
    frameBloqueSkin->setGeometry(x4, yBloques, wBloque, hBloques);
    frameBloqueSkin->setStyleSheet(estiloMarcoBloque);
    QVBoxLayout *layoutSkin = new QVBoxLayout(frameBloqueSkin);
    layoutSkin->setContentsMargins(14, 18, 14, 18);
    layoutSkin->setSpacing(12);
    layoutSkin->setAlignment(Qt::AlignCenter);

    QLabel *lblTituloSkinBlock = new QLabel("SKIN ACTIVA", frameBloqueSkin);
    lblTituloSkinBlock->setAlignment(Qt::AlignCenter);
    lblTituloSkinBlock->setStyleSheet("color: #E2C290; font-weight: bold; font-size: 13pt; background: transparent; border: none;");
    layoutSkin->addWidget(lblTituloSkinBlock);

    lblSkinImgBlock = new QLabel(frameBloqueSkin);
    lblSkinImgBlock->setFixedSize(145, 145);
    lblSkinImgBlock->setAlignment(Qt::AlignCenter);
    lblSkinImgBlock->setStyleSheet("background: rgba(0,0,0,0.35); border: 2px solid #7A4E31; border-radius: 10px;");
    if (!imgAvatarSkin.isNull()) {
        lblSkinImgBlock->setPixmap(imgAvatarSkin.scaled(135, 135, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    layoutSkin->addWidget(lblSkinImgBlock, 0, Qt::AlignCenter);

    lblSkinNameBlock = new QLabel("GUARDIÁN", frameBloqueSkin);
    lblSkinNameBlock->setAlignment(Qt::AlignCenter);
    lblSkinNameBlock->setStyleSheet("color: #F5E6D3; font-weight: bold; font-size: 12pt; background: transparent; border: none;");
    layoutSkin->addWidget(lblSkinNameBlock);

    // Render inicial
    actualizarBloquesVisuales();
}

MiPerfil::~MiPerfil() {}

QPixmap MiPerfil::makeGrayscale(const QPixmap &pix) const {
    if (pix.isNull()) return pix;
    return QPixmap::fromImage(pix.toImage().convertToFormat(QImage::Format_Grayscale8));
}

void MiPerfil::setMenuAnterior(QWidget *menu) {
    menuAnterior = menu;
}

void MiPerfil::setProgresoDatos(int n1, int n2, int n3, bool ins1, bool ins2, bool ins3, int mapPieces) {
    nivelesProgreso[0] = n1;
    nivelesProgreso[1] = n2;
    nivelesProgreso[2] = n3;
    insigniasDesbloqueadas[0] = ins1;
    insigniasDesbloqueadas[1] = ins2;
    insigniasDesbloqueadas[2] = ins3;
    pedazosMapaRecolectados = mapPieces;
    actualizarBloquesVisuales();
}

void MiPerfil::actualizarBloquesVisuales() {
    // 1. Skin activa
    if (lblSkinImgBlock && !imgAvatarSkin.isNull()) {
        lblSkinImgBlock->setPixmap(imgAvatarSkin.scaled(135, 135, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 2. Niveles (Check / Cross)
    for(int i=0; i<3; ++i) {
        if (lblNivelStatus[i]) {
            bool completado = (nivelesProgreso[i] >= 100);
            if (completado) {
                lblNivelStatus[i]->setText("✔");
                lblNivelStatus[i]->setStyleSheet("color: #4CAF50; font-size: 16pt; font-weight: bold; background: transparent; border: none;");
            } else {
                lblNivelStatus[i]->setText("✖");
                lblNivelStatus[i]->setStyleSheet("color: #E53935; font-size: 15pt; font-weight: bold; background: transparent; border: none;");
            }
        }
    }

    // 3. Insignias
    int countInsUnlocked = 0;
    for(int i=0; i<3; ++i) {
        if(insigniasDesbloqueadas[i]) countInsUnlocked++;
        if (lblInsImg[i]) {
            QString rutaIns = QString(":/imagenes/insignia_%1.png").arg(i + 1);
            QPixmap badgeIcon(rutaIns);
            if (badgeIcon.isNull()) badgeIcon.load(":/imagenes/insignia_base.png");

            QPixmap target = insigniasDesbloqueadas[i] ? badgeIcon : makeGrayscale(badgeIcon);
            lblInsImg[i]->setPixmap(target.scaled(66, 66, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    if (lblInsStatus) {
        lblInsStatus->setText(QString("Desbloqueadas: %1 / 3").arg(countInsUnlocked));
    }

    // 4. Mapa del Templo
    for(int i=0; i<3; ++i) {
        if (lblMapaImg[i]) {
            bool pieceUnlocked = (i < pedazosMapaRecolectados);
            QString rutaMapa = QString(":/imagenes/map_piece_%1.png").arg(i + 1);
            QPixmap mapPieceIcon(rutaMapa);
            if (mapPieceIcon.isNull()) mapPieceIcon.load(":/imagenes/insignia_base.png");

            QPixmap pTarget = pieceUnlocked ? mapPieceIcon : makeGrayscale(mapPieceIcon);
            lblMapaImg[i]->setPixmap(pTarget.scaled(58, 58, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    if (lblMapaStatus) {
        lblMapaStatus->setText(QString("Piezas recolectadas: %1 / 3").arg(pedazosMapaRecolectados));
    }
}

void MiPerfil::setUsuarioActual(const QString &usuario) {
    setUsuario(usuario);
}

void MiPerfil::setUsuario(const QString &usuario) {
    usuarioActual = usuario;
    if (lblNombre) {
        lblNombre->setText(QString("EXPLORADOR:\n%1").arg(usuarioActual.isEmpty() ? "ANÓNIMO" : usuarioActual.toUpper()));
    }
    cargarDatosUsuario();
}

void MiPerfil::cargarDatosUsuario() {
    if (usuarioActual.isEmpty()) {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
        if (lblAvatarMarco && !imgAvatarUser.isNull()) {
            lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
        if (lblGemas) lblGemas->setText("GEMAS ACUMULADAS: 0");
        if (lblPuntaje) lblPuntaje->setText("PUNTAJE TOTAL: 0");
        for(int i=0; i<3; ++i) {
            nivelesProgreso[i] = 0;
            insigniasDesbloqueadas[i] = false;
        }
        pedazosMapaRecolectados = 0;
        actualizarBloquesVisuales();
        return;
    }

    std::string uStr = usuarioActual.toStdString();
    Usuario user;

    if (UserManager::cargarDatosUsuario(uStr, user)) {
        int avId = (user.avatarId > 0) ? user.avatarId : 1;
        QString rutaAvatar = QString(":/imagenes/avatar_%1.png").arg(avId);
        if (!imgAvatarUser.load(rutaAvatar)) {
            imgAvatarUser.load(":/imagenes/avatar_default.png");
        }
        if (lblAvatarMarco && !imgAvatarUser.isNull()) {
            lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }

        if (lblGemas) lblGemas->setText(QString("GEMAS ACUMULADAS: %L1").arg(user.gemas));
        if (lblPuntaje) lblPuntaje->setText(QString("PUNTAJE TOTAL: %L1").arg(user.puntosTotales));

        int skinId = (user.skinActual > 0) ? user.skinActual : 1;
        QString rutaSkin = QString(":/skins/skin_%1.png").arg(skinId);
        if (!imgAvatarSkin.load(rutaSkin)) {
            imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
        }

        for(int i=0; i<3; ++i) {
            nivelesProgreso[i] = (user.completoJuego || user.nivelActual > (i + 1)) ? 100 : 0;
        }

        for(int i=0; i<3; ++i) {
            insigniasDesbloqueadas[i] = (i < user.insignias);
        }

        pedazosMapaRecolectados = user.pedazosMapa;

        actualizarBloquesVisuales();
    } else {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
        imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
        if (lblGemas) lblGemas->setText("GEMAS ACUMULADAS: 0");
        if (lblPuntaje) lblPuntaje->setText("PUNTAJE TOTAL: 0");
        actualizarBloquesVisuales();
    }
}

void MiPerfil::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (!imgFondoPerfil.isNull()) {
        painter.drawPixmap(rect(), imgFondoPerfil);
    }
}

void MiPerfil::onVolverClicked() {
    if (menuAnterior) {
        menuAnterior->show();
    } else {
        MenuPrincipal *menu = new MenuPrincipal(nullptr, usuarioActual);
        menu->show();
    }
    this->close();
}