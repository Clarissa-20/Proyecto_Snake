// #include "tienda.h"
// #include "menuprincipal.h"
// #include <QPixmap>
// #include <QDebug>

// Tienda::Tienda(QWidget *parent)
//     : QMainWindow(parent) {

//     this->setFixedSize(1280, 720);
//     this->setWindowTitle("Snake - La Botica del Bazar Perdido");

//     labelFondo = new QLabel(this);
//     labelFondo->setGeometry(0, 0, 1280, 720);
//     QPixmap pixmapFondo(":/imagenes/tienda_fondo.jpg");
//     labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

//     btnVolver = new QPushButton(this);
//     btnVolver->setGeometry(50, 35, 180, 50);
//     btnVolver->setStyleSheet(
//         "QPushButton {"
//         "   border-image: url(:/btns/btnVolverMenu.png);"
//         "   border: none;"
//         "   background: transparent;"
//         "}"
//         "QPushButton:hover {"
//         "   filter: brightness(1.2);"
//         "}"
//         );
//     connect(btnVolver, &QPushButton::clicked, this, &Tienda::onVolverMenuClicked);

//     QLabel *labelContenedorGemas = new QLabel(this);
//     labelContenedorGemas->setGeometry(1050, 30, 180, 55);
//     labelContenedorGemas->setStyleSheet("background: transparent;");

//     QLabel *labelFondoGemas = new QLabel(labelContenedorGemas);
//     labelFondoGemas->setGeometry(0, 0, 180, 55);
//     QPixmap pixGemasFondo(":/imagenes/etiqueta_gemas.png");
//     labelFondoGemas->setPixmap(pixGemasFondo.scaled(labelFondoGemas->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

//     labelGemasCantidad = new QLabel("1,250", labelContenedorGemas);
//     labelGemasCantidad->setGeometry(65, 12, 105, 30);
//     labelGemasCantidad->setAlignment(Qt::AlignCenter);
//     labelGemasCantidad->setStyleSheet("color: #FFFFFF; font-weight: bold; font-size: 18px; background: transparent;");

//     QString nombresSkins[6] = {
//         "SERPIENTE ESMERALDA", "SERPIENTE CÍTRICA", "SERPIENTE RUBÍ",
//         "SERPIENTE ZAFIR", "SERPIENTE AMESTISTA", "SERPIENTE AUREA"
//     };
//     int costosSkins[6] = { 250, 150, 300, 200, 100, 280 };
//     QString rutasImagenes[6] = {
//         ":/skins/skin1_tienda.png",
//         ":/skins/skin2_tienda.png",
//         ":/skins/skin3_tienda.png",
//         ":/skins/skin4_tienda.png",
//         ":/skins/skin5_tienda.png",
//         ":/skins/skin6_tienda.png"
//     };

//     int baseX = 145;
//     int baseY = 110;
//     int anchoItem = 310;
//     int altoItem = 230;
//     int separacionX = 40;
//     int separacionY = 40;

//     for (int i = 0; i < 6; ++i) {
//         int fila = i / 3;
//         int col = i % 3;
//         int posX = baseX + col * (anchoItem + separacionX);
//         int posY = baseY + fila * (altoItem + 55);

//         labelSkins[i] = new QLabel(this);
//         labelSkins[i]->setGeometry(posX, posY, anchoItem, altoItem);
//         QPixmap pixSkin(rutasImagenes[i]);
//         labelSkins[i]->setPixmap(pixSkin.scaled(labelSkins[i]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//         labelSkins[i]->setAlignment(Qt::AlignCenter);
//         labelSkins[i]->setStyleSheet("background: transparent;");

//         labelNombres[i] = new QLabel(nombresSkins[i], labelSkins[i]);
//         labelNombres[i]->setGeometry(10, altoItem - 60, anchoItem - 20, 24);
//         labelNombres[i]->setAlignment(Qt::AlignCenter);
//         labelNombres[i]->setStyleSheet(
//             "color: #FFF1C1;"
//             "font-weight: bold;"
//             "font-size: 13px;"
//             "background: transparent;"
//             );

//         labelPrecios[i] = new QLabel(QString("💎 %1 Gemas 💎").arg(costosSkins[i]), labelSkins[i]);
//         labelPrecios[i]->setGeometry(10, altoItem - 35, anchoItem - 20, 22);
//         labelPrecios[i]->setAlignment(Qt::AlignCenter);
//         labelPrecios[i]->setStyleSheet(
//             "color: #55FFCC;"
//             "font-weight: bold;"
//             "font-size: 12px;"
//             "background: transparent;"
//             );

//         btnComprar[i] = new QPushButton("BUY", this);
//         btnComprar[i]->setGeometry(posX + (anchoItem - 150) / 2, posY + altoItem + 6, 150, 36);
//         btnComprar[i]->setStyleSheet(
//             "QPushButton {"
//             "   background-color: #5A3D28;"
//             "   color: #F4E2BB;"
//             "   border: 2px solid #8C6239;"
//             "   border-radius: 5px;"
//             "   font-weight: bold;"
//             "   font-size: 12px;"
//             "}"
//             "QPushButton:hover {"
//             "   background-color: #764E33;"
//             "   color: #FFFFFF;"
//             "}"
//             );

//         int costoActual = costosSkins[i];
//         connect(btnComprar[i], &QPushButton::clicked, [=]() {
//             onComprarSkinClicked(i, costoActual);
//         });
//     }
// }

// Tienda::~Tienda() {}

// void Tienda::onVolverMenuClicked() {
//     MenuPrincipal *menuPrincipal = new MenuPrincipal();
//     menuPrincipal->show();
//     this->close();
// }

// void Tienda::onComprarSkinClicked(int skinId, int costo) {
//     //falta implementar el conteo de las gemas cuando se compra la skin
//     qDebug() << "Skin comprada con ID:" << skinId << "por un costo de:" << costo;
// }


#include "tienda.h"
#include "menuprincipal.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

Tienda::Tienda(QWidget *parent, const QString &usuario)
    : QMainWindow(parent), usuarioActual(usuario) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - La Botica del Bazar Perdido");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/tienda_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    btnVolver = new QPushButton(this);
    btnVolver->setGeometry(50, 35, 180, 50);
    btnVolver->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/btns/btnVolverMenu.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
        "}"
        );
    connect(btnVolver, &QPushButton::clicked, this, &Tienda::onVolverMenuClicked);

    QLabel *labelContenedorGemas = new QLabel(this);
    labelContenedorGemas->setGeometry(1050, 30, 180, 55);
    labelContenedorGemas->setStyleSheet("background: transparent;");

    QLabel *labelFondoGemas = new QLabel(labelContenedorGemas);
    labelFondoGemas->setGeometry(0, 0, 180, 55);
    QPixmap pixGemasFondo(":/imagenes/etiqueta_gemas.png");
    labelFondoGemas->setPixmap(pixGemasFondo.scaled(labelFondoGemas->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    labelGemasCantidad = new QLabel("0", labelContenedorGemas);
    labelGemasCantidad->setGeometry(65, 12, 105, 30);
    labelGemasCantidad->setAlignment(Qt::AlignCenter);
    labelGemasCantidad->setStyleSheet("color: #FFFFFF; font-weight: bold; font-size: 18px; background: transparent;");

    QString nombresSkins[6] = {
        "SERPIENTE ESMERALDA", "SERPIENTE CÍTRICA", "SERPIENTE RUBÍ",
        "SERPIENTE ZAFIR", "SERPIENTE AMESTISTA", "SERPIENTE AUREA"
    };
    int costosSkins[6] = { 250, 150, 300, 200, 100, 280 };
    QString rutasImagenes[6] = {
        ":/skins/skin1_tienda.png",
        ":/skins/skin2_tienda.png",
        ":/skins/skin3_tienda.png",
        ":/skins/skin4_tienda.png",
        ":/skins/skin5_tienda.png",
        ":/skins/skin6_tienda.png"
    };

    int baseX = 145;
    int baseY = 110;
    int anchoItem = 310;
    int altoItem = 230;
    int separacionX = 40;
    int separacionY = 40;

    for (int i = 0; i < 6; ++i) {
        int fila = i / 3;
        int col = i % 3;
        int posX = baseX + col * (anchoItem + separacionX);
        int posY = baseY + fila * (altoItem + 55);

        labelSkins[i] = new QLabel(this);
        labelSkins[i]->setGeometry(posX, posY, anchoItem, altoItem);
        QPixmap pixSkin(rutasImagenes[i]);
        labelSkins[i]->setPixmap(pixSkin.scaled(labelSkins[i]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        labelSkins[i]->setAlignment(Qt::AlignCenter);
        labelSkins[i]->setStyleSheet("background: transparent;");

        labelNombres[i] = new QLabel(nombresSkins[i], labelSkins[i]);
        labelNombres[i]->setGeometry(10, altoItem - 60, anchoItem - 20, 24);
        labelNombres[i]->setAlignment(Qt::AlignCenter);
        labelNombres[i]->setStyleSheet(
            "color: #FFF1C1;"
            "font-weight: bold;"
            "font-size: 13px;"
            "background: transparent;"
            );

        labelPrecios[i] = new QLabel(QString("💎 %1 Gemas 💎").arg(costosSkins[i]), labelSkins[i]);
        labelPrecios[i]->setGeometry(10, altoItem - 35, anchoItem - 20, 22);
        labelPrecios[i]->setAlignment(Qt::AlignCenter);
        labelPrecios[i]->setStyleSheet(
            "color: #55FFCC;"
            "font-weight: bold;"
            "font-size: 12px;"
            "background: transparent;"
            );

        btnComprar[i] = new QPushButton("BUY", this);
        btnComprar[i]->setGeometry(posX + (anchoItem - 150) / 2, posY + altoItem + 6, 150, 36);
        btnComprar[i]->setStyleSheet(
            "QPushButton {"
            "   background-color: #5A3D28;"
            "   color: #F4E2BB;"
            "   border: 2px solid #8C6239;"
            "   border-radius: 5px;"
            "   font-weight: bold;"
            "   font-size: 12px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #764E33;"
            "   color: #FFFFFF;"
            "}"
            );

        int skinIdReal = i + 1; // IDs del 1 al 6
        int costoActual = costosSkins[i];
        connect(btnComprar[i], &QPushButton::clicked, [=]() {
            onComprarSkinClicked(skinIdReal, costoActual);
        });
    }

    actualizarUI();
}

Tienda::~Tienda() {}

void Tienda::setUsuarioActual(const QString &usuario) {
    usuarioActual = usuario;
    actualizarUI();
}

void Tienda::actualizarUI() {
    if (!usuarioActual.isEmpty()) {
        usuarioCargado = UserManager::cargarDatosUsuario(usuarioActual.toStdString(), usuarioData);
        if (usuarioCargado) {
            if (labelGemasCantidad) {
                labelGemasCantidad->setText(QString::number(usuarioData.gemas));
            }
            verificarEstadosSkins();
            return;
        }
    }
    usuarioCargado = false;
    if (labelGemasCantidad) labelGemasCantidad->setText("0");
}

void Tienda::verificarEstadosSkins() {
    if (!usuarioCargado) return;

    for (int i = 0; i < 6; ++i) {
        int skinId = i + 1;
        bool comprada = usuarioData.tieneSkin(skinId);
        bool equipada = (usuarioData.skinActual == skinId);

        if (equipada) {
            btnComprar[i]->setText("EQUIPADA");
            btnComprar[i]->setEnabled(false);
            btnComprar[i]->setStyleSheet(
                "QPushButton { background-color: #2E7D32; color: #FFFFFF; border: 2px solid #4CAF50; border-radius: 5px; font-weight: bold; font-size: 12px; }"
                );
        } else if (comprada) {
            btnComprar[i]->setText("EQUIPAR");
            btnComprar[i]->setEnabled(true);
            btnComprar[i]->setStyleSheet(
                "QPushButton { background-color: #1565C0; color: #FFFFFF; border: 2px solid #42A5F5; border-radius: 5px; font-weight: bold; font-size: 12px; }"
                "QPushButton:hover { background-color: #1976D2; }"
                );
        } else {
            btnComprar[i]->setText("BUY");
            btnComprar[i]->setEnabled(true);
            btnComprar[i]->setStyleSheet(
                "QPushButton { background-color: #5A3D28; color: #F4E2BB; border: 2px solid #8C6239; border-radius: 5px; font-weight: bold; font-size: 12px; }"
                "QPushButton:hover { background-color: #764E33; color: #FFFFFF; }"
                );
        }
    }
}

void Tienda::onVolverMenuClicked() {
    MenuPrincipal *menuPrincipal = new MenuPrincipal(nullptr, usuarioActual);
    menuPrincipal->show();
    this->close();
}

void Tienda::onComprarSkinClicked(int skinId, int costo) {
    if (usuarioActual.isEmpty() || !usuarioCargado) {
        QMessageBox::warning(this, "Aviso", "Inicia sesión para gestionar skins.");
        return;
    }

    // Refrescar datos actuales
    UserManager::cargarDatosUsuario(usuarioActual.toStdString(), usuarioData);

    bool comprada = usuarioData.tieneSkin(skinId);
    bool equipada = (usuarioData.skinActual == skinId);

    if (equipada) return;

    if (comprada) {
        // Equipar skin ya poseída
        usuarioData.skinActual = skinId;
        UserManager::guardarProgresoUsuario(usuarioData);
        qDebug() << "Skin equipada:" << skinId;
        actualizarUI();
        return;
    }

    // Comprar nueva skin
    if (usuarioData.gemas >= costo) {
        usuarioData.gemas -= costo;
        usuarioData.skinActual = skinId;

        if (!usuarioData.tieneSkin(skinId)) {
            usuarioData.skinsCompradasStr += "-" + std::to_string(skinId);
        }

        UserManager::guardarProgresoUsuario(usuarioData);

        qDebug() << "Skin comprada y equipada ID:" << skinId << "por costo:" << costo;
        QMessageBox::information(this, "¡Éxito!", "Has adquirido y equipado la skin.");
        actualizarUI();
    } else {
        QMessageBox::warning(this, "Fondos Insuficientes", "No tienes suficientes gemas para adquirir esta skin.");
    }
}