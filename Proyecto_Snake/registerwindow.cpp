/*#include "registerwindow.h"
#include <QPixmap>
#include <QIcon>
#include <QRegularExpression>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent), avatarSeleccionado(-1) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Registro de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/recursos/crear_cuenta_fondo.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QString rutasAvatares[4] = {
        ":/recursos/avatar1.png",   //ARREGLAR LOS AVATARES A OTROS
        ":/recursos/avatar2.png",
        ":/recursos/avatar3.png",
        ":/recursos/avatar4.png"
    };

    int startX = 240;
    int spacing = 75;
    for(int i = 0; i < 4; i++) {
        btnAvatar[i] = new QPushButton(this);
        btnAvatar[i]->setGeometry(startX + (i * spacing), 180, 60, 60);
        btnAvatar[i]->setIcon(QIcon(rutasAvatares[i]));
        btnAvatar[i]->setIconSize(btnAvatar[i]->size());
        btnAvatar[i]->setStyleSheet("QPushButton { border: 2px solid #5c3a21; border-radius: 6px; background: #2b1a0c; }");

        // Conectar selección usando una lambda
        connect(btnAvatar[i], &QPushButton::clicked, this, [=](){ seleccionarAvatar(i); });
    }

    //Campo de Nombre de Usuario
    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(220, 275, 360, 35);
    txtUsuario->setPlaceholderText("Nombre de Usuario");
    txtUsuario->setStyleSheet("QLineEdit { background: transparent; border: none; color: #e6c687; font-size: 14px; font-family: 'Georgia'; }");

    //Campo de Contraseña
    txtPassword = new QLineEdit(this);
    txtPassword->setGeometry(220, 335, 360, 35);
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setPlaceholderText("Contraseña");
    txtPassword->setStyleSheet("QLineEdit { background: transparent; border: none; color: #e6c687; font-size: 14px; font-family: 'Georgia'; }");

    // Conectar señal de cambio de texto para validar requisitos en tiempo real
    connect(txtPassword, &QLineEdit::textChanged, this, &RegisterWindow::validarPassword);

    //Lista de Requisitos de Contraseña (dentro de la cajita del pergamino/fondo)
    int reqX = 230;
    int reqYStart = 390;
    int gapY = 20;

    lblReqLongitud = new QLabel("• Al menos 5 caracteres", this);
    lblReqLongitud->setGeometry(reqX, reqYStart, 250, 20);

    lblReqMayuscula = new QLabel("• Al menos una mayúscula", this);
    lblReqMayuscula->setGeometry(reqX, reqYStart + gapY, 250, 20);

    lblReqNumero = new QLabel("• Al menos un número", this);
    lblReqNumero->setGeometry(reqX, reqYStart + (gapY * 2), 250, 20);

    lblReqEspecial = new QLabel("• Al menos un carácter especial", this);
    lblReqEspecial->setGeometry(reqX, reqYStart + (gapY * 3), 250, 20);

    // Estilo inicial en rojo para los requisitos
    QString estiloRojo = "color: #cc3333; font-size: 11px; font-family: 'Georgia'; font-weight: bold;";
    lblReqLongitud->setStyleSheet(estiloRojo);
    lblReqMayuscula->setStyleSheet(estiloRojo);
    lblReqNumero->setStyleSheet(estiloRojo);
    lblReqEspecial->setStyleSheet(estiloRojo);

    //Botón CREAR CUENTA
    btnCrearCuenta = new QPushButton(this);
    btnCrearCuenta->setGeometry(250, 485, 300, 50);
    QPixmap pixmapBtnCrear(":/recursos/crear_cuenta_boton.png");
    btnCrearCuenta->setIcon(QIcon(pixmapBtnCrear));
    btnCrearCuenta->setIconSize(btnCrearCuenta->size());
    btnCrearCuenta->setStyleSheet("QPushButton { border: none; background: transparent; }");

    //para el texto de abajo
    lblIrLogin = new QLabel(this);
    lblIrLogin->setGeometry(250, 545, 300, 25);
    lblIrLogin->setText("<a href='login' style='color: #c29b38; text-decoration: none;'>¿Ya tienes una cuenta? Inicia sesión</a>");
    lblIrLogin->setAlignment(Qt::AlignCenter);
    lblIrLogin->setOpenExternalLinks(false);

    connect(btnCrearCuenta, &QPushButton::clicked, this, &RegisterWindow::onCrearCuentaClicked);
}

RegisterWindow::~RegisterWindow() {}

void RegisterWindow::seleccionarAvatar(int idAvatar) {
    avatarSeleccionado = idAvatar;
    // Resaltar visualmente el avatar elegido y apagar los demás
    for(int i = 0; i < 4; i++) {
        if(i == idAvatar) {
            btnAvatar[i]->setStyleSheet("QPushButton { border: 3px solid #ffd700; border-radius: 6px; background: #3d2512; }");
        } else {
            btnAvatar[i]->setStyleSheet("QPushButton { border: 2px solid #5c3a21; border-radius: 6px; background: #2b1a0c; }");
        }
    }
}

void RegisterWindow::validarPassword(const QString &texto) {
    // 1. Al menos 5 caracteres
    bool cumpleLongitud = (texto.length() >= 5);
    // 2. Al menos una mayúscula
    bool cumpleMayuscula = texto.contains(QRegularExpression("[A-Z]"));
    // 3. Al menos un número
    bool cumpleNumero = texto.contains(QRegularExpression("[0-9]"));
    // 4. Al menos un carácter especial
    bool cumpleEspecial = texto.contains(QRegularExpression("[^a-zA-Z0-9]"));

    // Estilos dinámicos para cambiar entre rojo y verde con checkmark
    QString estiloRojo = "color: #cc3333; font-size: 11px; font-family: 'Georgia'; font-weight: bold;";
    QString estiloVerde = "color: #33cc66; font-size: 11px; font-family: 'Georgia'; font-weight: bold;";

    lblReqLongitud->setText((cumpleLongitud ? "✔" : "•") + QString(" Al menos 5 caracteres"));
    lblReqLongitud->setStyleSheet(cumpleLongitud ? estiloVerde : estiloRojo);

    lblReqMayuscula->setText((cumpleMayuscula ? "✔" : "•") + QString(" Al menos una mayúscula"));
    lblReqMayuscula->setStyleSheet(cumpleMayuscula ? estiloVerde : estiloRojo);

    lblReqNumero->setText((cumpleNumero ? "✔" : "•") + QString(" Al menos un número"));
    lblReqNumero->setStyleSheet(cumpleNumero ? estiloVerde : estiloRojo);

    lblReqEspecial->setText((cumpleEspecial ? "✔" : "•") + QString(" Al menos un carácter especial"));
    lblReqEspecial->setStyleSheet(cumpleEspecial ? estiloVerde : estiloRojo);
}

void RegisterWindow::onCrearCuentaClicked() {
    // Aquí validar que todos los requisitos se cumplan y guardas los datos del usuario
    // en archivos (fstream) para cumplir con el manejo de archivos del proyecto.
}*/