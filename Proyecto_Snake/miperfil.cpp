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

    imgFondoPerfil.load(":/imagenes/miPerfil_fondo.png");

    if (!imgAvatarUser.load(":/imagenes/avatar_usuario.png")) {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
    }
    imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(20, 20, 80, 80);
    btnVolver->setStyleSheet(
        "QPushButton {"
        "    border-image: url(:/btns/btn_volver_pequeno.png);"
        "    border: none;"
        "}"
        "QPushButton:hover { opacity: 0.9; filter: brightness(1.2); }"
        );
    connect(btnVolver, &QPushButton::clicked, this, &MiPerfil::onVolverClicked);

    QString estiloTextoBase = "font-family: 'Georgia'; background: transparent;";

    frameInfoUsuario = new QFrame(this);
    frameInfoUsuario->setGeometry(200, 180, 880, 200);
    frameInfoUsuario->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 rgba(55, 36, 20, 0.96), stop:0.5 rgba(40, 24, 12, 0.96), stop:1 rgba(26, 15, 7, 0.98));"
        "border: 2px solid #D4AF37;"
        "border-radius: 16px;"
        );

    QHBoxLayout *hTopLayout = new QHBoxLayout(frameInfoUsuario);
    hTopLayout->setContentsMargins(30, 22, 30, 22);
    hTopLayout->setSpacing(32);

    lblAvatarMarco = new QLabel(frameInfoUsuario);
    lblAvatarMarco->setFixedSize(150, 150);
    lblAvatarMarco->setAlignment(Qt::AlignCenter);
    lblAvatarMarco->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(15,9,4,0.85), stop:1 rgba(35,22,12,0.85));"
        "border: 2px solid #C5A059; border-radius: 14px;"
        );
    if (!imgAvatarUser.isNull()) {
        lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    hTopLayout->addWidget(lblAvatarMarco, 0, Qt::AlignCenter);

    QVBoxLayout *vDatosLayout = new QVBoxLayout();
    vDatosLayout->setSpacing(12);
    vDatosLayout->setAlignment(Qt::AlignCenter);

    lblNombre = new QLabel("EXPLORADOR:\nCARGANDO...", frameInfoUsuario);
    lblNombre->setStyleSheet(estiloTextoBase + " font-size: 16pt; font-weight: bold; color: #FFF8E7; letter-spacing: 1.5px;");
    lblNombre->setWordWrap(true);

    QString estiloPildoraStat =
        estiloTextoBase +
        " font-size: 12pt; font-weight: bold; color: #FFE082;"
        " background: rgba(0, 0, 0, 0.35);"
        " border: 1px solid rgba(212, 175, 55, 0.4);"
        " border-radius: 8px;"
        " padding: 6px 14px;";

    lblPuntaje = new QLabel("PUNTAJE TOTAL: 0", frameInfoUsuario);
    lblPuntaje->setStyleSheet(estiloPildoraStat);

    lblGemas = new QLabel("GEMAS ACUMULADAS: 0", frameInfoUsuario);
    lblGemas->setStyleSheet(estiloPildoraStat);

    vDatosLayout->addWidget(lblNombre);

    QHBoxLayout *hStatsBox = new QHBoxLayout();
    hStatsBox->setSpacing(12);
    hStatsBox->addWidget(lblPuntaje);
    hStatsBox->addWidget(lblGemas);
    hStatsBox->addStretch();
    vDatosLayout->addLayout(hStatsBox);
    vDatosLayout->addStretch();

    hTopLayout->addLayout(vDatosLayout);
    hTopLayout->addStretch();

    QString estiloMarcoBloque =
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 rgba(50, 32, 18, 0.92), stop:1 rgba(28, 16, 8, 0.96));"
        "border: 2px solid #C5A059;"
        "border-radius: 14px;";

    QString estiloTituloBloque =
        "color: #E2C290; font-weight: bold; font-size: 12pt; font-family: 'Georgia';"
        "background: rgba(0,0,0,0.25); border: 1px solid rgba(197,160,89,0.3); border-radius: 6px;"
        "padding: 4px; letter-spacing: 1px;";

    int yBloques = 400;
    int hBloques = 285;
    int wBloque = 265;
    int startX = 80;
    int gap = 20;

    frameBloqueNiveles = new QFrame(this);
    frameBloqueNiveles->setGeometry(startX, yBloques, wBloque, hBloques);
    frameBloqueNiveles->setStyleSheet(estiloMarcoBloque);

    QVBoxLayout *layoutNiveles = new QVBoxLayout(frameBloqueNiveles);
    layoutNiveles->setContentsMargins(14, 16, 14, 16);
    layoutNiveles->setSpacing(12);

    QLabel *lblTituloNiveles = new QLabel("NIVELES", frameBloqueNiveles);
    lblTituloNiveles->setAlignment(Qt::AlignCenter);
    lblTituloNiveles->setStyleSheet(estiloTituloBloque);
    layoutNiveles->addWidget(lblTituloNiveles);

    for(int i=0; i<3; ++i) {
        QHBoxLayout *hItemNiv = new QHBoxLayout();
        hItemNiv->setSpacing(12);

        QLabel *lblN = new QLabel(QString("Nivel %1").arg(i+1), frameBloqueNiveles);
        lblN->setStyleSheet("color: #F5E6D3; font-size: 11pt; font-weight: bold; font-family: 'Georgia'; background: transparent; border: none;");

        lblNivelStatus[i] = new QLabel(frameBloqueNiveles);
        lblNivelStatus[i]->setFixedSize(32, 32);
        lblNivelStatus[i]->setAlignment(Qt::AlignCenter);
        lblNivelStatus[i]->setStyleSheet("background: rgba(0,0,0,0.3); border-radius: 6px; border: 1px solid rgba(255,255,255,0.1);");

        hItemNiv->addStretch();
        hItemNiv->addWidget(lblN);
        hItemNiv->addWidget(lblNivelStatus[i]);
        hItemNiv->addStretch();
        layoutNiveles->addLayout(hItemNiv);
    }
    layoutNiveles->addStretch();

    int x2 = startX + wBloque + gap;
    frameBloqueInsignias = new QFrame(this);
    frameBloqueInsignias->setGeometry(x2, yBloques, wBloque, hBloques);
    frameBloqueInsignias->setStyleSheet(estiloMarcoBloque);

    QVBoxLayout *layoutInsignias = new QVBoxLayout(frameBloqueInsignias);
    layoutInsignias->setContentsMargins(14, 16, 14, 16);
    layoutInsignias->setSpacing(10);

    QLabel *lblTituloIns = new QLabel("INSIGNIAS", frameBloqueInsignias);
    lblTituloIns->setAlignment(Qt::AlignCenter);
    lblTituloIns->setStyleSheet(estiloTituloBloque);
    layoutInsignias->addWidget(lblTituloIns);

    QHBoxLayout *hIns = new QHBoxLayout();
    hIns->setAlignment(Qt::AlignCenter);
    hIns->setSpacing(8);
    for(int i=0; i<3; ++i) {
        lblInsImg[i] = new QLabel(frameBloqueInsignias);
        lblInsImg[i]->setFixedSize(68, 68);
        lblInsImg[i]->setAlignment(Qt::AlignCenter);
        lblInsImg[i]->setStyleSheet("background: rgba(15,9,4,0.7); border: 2px inset #5A3A22; border-radius: 10px;");
        hIns->addWidget(lblInsImg[i]);
    }
    layoutInsignias->addLayout(hIns);

    lblInsStatus = new QLabel("Desbloqueadas: 0 / 3", frameBloqueInsignias);
    lblInsStatus->setAlignment(Qt::AlignCenter);
    lblInsStatus->setStyleSheet("color: #FFE082; font-size: 11pt; font-weight: bold; font-family: 'Georgia'; background: rgba(0,0,0,0.25); border-radius: 6px; padding: 4px;");
    layoutInsignias->addWidget(lblInsStatus);
    layoutInsignias->addStretch();

    int x3 = x2 + wBloque + gap;
    frameBloqueMapa = new QFrame(this);
    frameBloqueMapa->setGeometry(x3, yBloques, wBloque, hBloques);
    frameBloqueMapa->setStyleSheet(estiloMarcoBloque);

    QVBoxLayout *layoutMapa = new QVBoxLayout(frameBloqueMapa);
    layoutMapa->setContentsMargins(14, 16, 14, 16);
    layoutMapa->setSpacing(10);

    QLabel *lblTituloMapa = new QLabel("MAPA DEL TEMPLO", frameBloqueMapa);
    lblTituloMapa->setAlignment(Qt::AlignCenter);
    lblTituloMapa->setStyleSheet(estiloTituloBloque);
    layoutMapa->addWidget(lblTituloMapa);

    QHBoxLayout *hMapaPieces = new QHBoxLayout();
    hMapaPieces->setAlignment(Qt::AlignCenter);
    hMapaPieces->setSpacing(10);
    for(int i=0; i<3; ++i) {
        lblMapaImg[i] = new QLabel(frameBloqueMapa);
        lblMapaImg[i]->setFixedSize(62, 62);
        lblMapaImg[i]->setAlignment(Qt::AlignCenter);
        lblMapaImg[i]->setStyleSheet("background: rgba(15,9,4,0.7); border: 2px inset #5A3A22; border-radius: 10px;");
        hMapaPieces->addWidget(lblMapaImg[i]);
    }
    layoutMapa->addLayout(hMapaPieces);

    lblMapaStatus = new QLabel("Piezas recolectadas: 0 / 3", frameBloqueMapa);
    lblMapaStatus->setAlignment(Qt::AlignCenter);
    lblMapaStatus->setStyleSheet("color: #FFE082; font-size: 11pt; font-weight: bold; font-family: 'Georgia'; background: rgba(0,0,0,0.25); border-radius: 6px; padding: 4px;");
    layoutMapa->addWidget(lblMapaStatus);
    layoutMapa->addStretch();

    int x4 = x3 + wBloque + gap;
    frameBloqueSkin = new QFrame(this);
    frameBloqueSkin->setGeometry(x4, yBloques, wBloque, hBloques);
    frameBloqueSkin->setStyleSheet(estiloMarcoBloque);

    QVBoxLayout *layoutSkin = new QVBoxLayout(frameBloqueSkin);
    layoutSkin->setContentsMargins(14, 16, 14, 16);
    layoutSkin->setSpacing(10);
    layoutSkin->setAlignment(Qt::AlignCenter);

    QLabel *lblTituloSkinBlock = new QLabel("SKIN ACTIVA", frameBloqueSkin);
    lblTituloSkinBlock->setAlignment(Qt::AlignCenter);
    lblTituloSkinBlock->setStyleSheet(estiloTituloBloque);
    layoutSkin->addWidget(lblTituloSkinBlock);

    lblSkinImgBlock = new QLabel(frameBloqueSkin);
    lblSkinImgBlock->setFixedSize(140, 140);
    lblSkinImgBlock->setAlignment(Qt::AlignCenter);
    lblSkinImgBlock->setStyleSheet("background: rgba(15,9,4,0.75); border: 2px inset #C5A059; border-radius: 12px;");
    if (!imgAvatarSkin.isNull()) {
        lblSkinImgBlock->setPixmap(imgAvatarSkin.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    layoutSkin->addWidget(lblSkinImgBlock, 0, Qt::AlignCenter);

    lblSkinNameBlock = new QLabel("GUARDIÁN", frameBloqueSkin);
    lblSkinNameBlock->setAlignment(Qt::AlignCenter);
    lblSkinNameBlock->setStyleSheet("color: #FFF8E7; font-weight: bold; font-size: 11pt; font-family: 'Georgia'; background: rgba(0,0,0,0.3); border-radius: 6px; padding: 4px;");
    layoutSkin->addWidget(lblSkinNameBlock);

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
    if (lblSkinImgBlock && !imgAvatarSkin.isNull()) {
        lblSkinImgBlock->setPixmap(imgAvatarSkin.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    for(int i=0; i<3; ++i) {
        if (lblNivelStatus[i]) {
            bool completado = (nivelesProgreso[i] >= 100);
            if (completado) {
                lblNivelStatus[i]->setText("✔");
                lblNivelStatus[i]->setStyleSheet("color: #66BB6A; background: rgba(102,187,106,0.15); border: 1px solid #66BB6A; font-size: 15pt; font-weight: bold; border-radius: 6px;");
            } else {
                lblNivelStatus[i]->setText("✖");
                lblNivelStatus[i]->setStyleSheet("color: #EF5350; background: rgba(239,83,80,0.15); border: 1px solid #EF5350; font-size: 14pt; font-weight: bold; border-radius: 6px;");
            }
        }
    }

    int countInsUnlocked = 0;
    for(int i=0; i<3; ++i) {
        if(insigniasDesbloqueadas[i]) countInsUnlocked++;
        if (lblInsImg[i]) {
            QString rutaIns = QString(":/imagenes/insignia_%1.png").arg(i + 1);
            QPixmap badgeIcon(rutaIns);
            if (badgeIcon.isNull()) badgeIcon.load(":/imagenes/insignia_base.png");

            QPixmap target = insigniasDesbloqueadas[i] ? badgeIcon : makeGrayscale(badgeIcon);
            lblInsImg[i]->setPixmap(target.scaled(62, 62, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    if (lblInsStatus) {
        lblInsStatus->setText(QString("Desbloqueadas: %1 / 3").arg(countInsUnlocked));
    }

    for(int i=0; i<3; ++i) {
        if (lblMapaImg[i]) {
            bool pieceUnlocked = (i < pedazosMapaRecolectados);
            QString rutaMapa = QString(":/imagenes/map_piece_%1.png").arg(i + 1);
            QPixmap mapPieceIcon(rutaMapa);
            if (mapPieceIcon.isNull()) mapPieceIcon.load(":/imagenes/insignia_base.png");

            QPixmap pTarget = pieceUnlocked ? mapPieceIcon : makeGrayscale(mapPieceIcon);
            lblMapaImg[i]->setPixmap(pTarget.scaled(56, 56, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
    QString nombresSkins[7] = {
        "GUARDIÁN",            // ID 0 - por defecto
        "SERPIENTE ESMERALDA", // ID 1
        "SERPIENTE CÍTRICA",   // ID 2
        "SERPIENTE RUBÍ",      // ID 3
        "SERPIENTE ZAFIR",     // ID 4
        "SERPIENTE AMESTISTA", // ID 5
        "SERPIENTE AUREA"      // ID 6
    };

    if (usuarioActual.isEmpty()) {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
        if (lblAvatarMarco && !imgAvatarUser.isNull()) {
            lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
        if (lblSkinNameBlock) lblSkinNameBlock->setText("GUARDIÁN");
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
        int avId = (user.avatarId >= 1 && user.avatarId <= 4) ? user.avatarId : 1;
        QString rutaAvatar = QString(":/imagenes/avatar_%1.png").arg(avId);
        if (!imgAvatarUser.load(rutaAvatar)) {
            imgAvatarUser.load(":/imagenes/avatar_default.png");
        }
        if (lblAvatarMarco && !imgAvatarUser.isNull()) {
            lblAvatarMarco->setPixmap(imgAvatarUser.scaled(138, 138, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }

        if (lblGemas) lblGemas->setText(QString("GEMAS ACUMULADAS: %L1").arg(user.gemas));
        if (lblPuntaje) lblPuntaje->setText(QString("PUNTAJE TOTAL: %L1").arg(user.puntosTotales));

        int skinId = user.skinActual;
        QString rutaSkin = QString(":/skins/skin%1_tienda.png").arg(skinId);
        if (skinId <= 0 || !imgAvatarSkin.load(rutaSkin)) {
            imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
            skinId = 0;
        }

        if (lblSkinNameBlock) {
            int idx = (skinId >= 0 && skinId <= 6) ? skinId : 0;
            lblSkinNameBlock->setText(nombresSkins[idx]);
        }

        for(int i=0; i<3; ++i) {
            nivelesProgreso[i] = (user.completoJuego || user.nivelActual > (i + 1)) ? 100 : 0;
        }

        for(int i=0; i<3; ++i) {
            insigniasDesbloqueadas[i] = ((user.insignias & (1 << i)) != 0);
        }

        int countMapPieces = 0;
        for(int i=0; i<3; ++i) {
            if ((user.pedazosMapa & (1 << i)) != 0) {
                countMapPieces++;
            }
        }
        pedazosMapaRecolectados = countMapPieces;

        actualizarBloquesVisuales();
    } else {
        imgAvatarUser.load(":/imagenes/avatar_default.png");
        imgAvatarSkin.load(":/skins/skin_predeterminada_tienda.png");
        if (lblSkinNameBlock) lblSkinNameBlock->setText("GUARDIÁN");
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

void MiPerfil::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    cargarDatosUsuario();
    qDebug() << "MiPerfil - usuarioActual:" << usuarioActual;
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