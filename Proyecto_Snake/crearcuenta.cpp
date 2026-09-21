#include "crearcuenta.h"
#include "login.h"
#include "menuprincipal.h"
#include "usermanager.h"
#include "menuInicio.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <cctype>

CrearCuenta::CrearCuenta(QWidget *parent)
    : QMainWindow(parent), avatarSeleccionado(-1) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - El Templo Perdido | Registro de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/crear_cuenta_fondo.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // --- TÍTULO DE SECCIÓN DE AVATARES ---
    QLabel *lblSelAvatar = new QLabel("SELECCIONA TU EXPLORADOR", this);
    lblSelAvatar->setGeometry(250, 160, 300, 22);
    lblSelAvatar->setAlignment(Qt::AlignCenter);
    lblSelAvatar->setStyleSheet("font-family: 'Georgia'; font-size: 13px; font-weight: bold; color: #d4af37; background: transparent; letter-spacing: 1px;");

    int avatarAncho = 70;
    int avatarAlto = 70;
    int avatarY = 188;
    // Centrado exacto para 4 elementos de 70px con separación de 15px (total 325px, start = 237)
    int xs[4] = {237, 322, 407, 492};

    for(int i = 0; i < 4; ++i) {
        QPushButton *btnAvatar = new QPushButton(this);
        btnAvatar->setGeometry(xs[i], avatarY, avatarAncho, avatarAlto);
        QString rutaAvatar = QString(":/imagenes/avatar_%1.png").arg(i + 1);
        btnAvatar->setIcon(QIcon(rutaAvatar));
        btnAvatar->setIconSize(QSize(avatarAncho - 14, avatarAlto - 14));
        btnAvatar->setCheckable(true);
        btnAvatar->setStyleSheet(
            "QPushButton { "
            "    border: 2px solid #5c4033; "
            "    background: rgba(30, 20, 15, 0.85); "
            "    border-radius: 8px; "
            "} "
            "QPushButton:hover { "
            "    border: 2px solid #a67c52; "
            "    background: rgba(45, 30, 22, 0.95); "
            "} "
            "QPushButton:checked { "
            "    border: 2px solid #d4af37; "
            "    background: rgba(212, 175, 55, 0.28); "
            "}"
            );

        connect(btnAvatar, &QPushButton::clicked, [this, i]() {
            seleccionarAvatar(i);
        });
        botonesAvatares.append(btnAvatar);
    }

    // --- ESTILO TEMÁTICO PARA CAMPOS DE TEXTO ---
    QString estiloInputs =
        "QLineEdit {"
        "    background: rgba(35, 25, 18, 0.92);"
        "    border: 2px solid #5c4033;"
        "    border-radius: 6px;"
        "    color: #f4efdc;"
        "    font-family: 'Georgia';"
        "    font-size: 15px;"
        "    padding-left: 12px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #d4af37;"
        "    background: rgba(45, 33, 24, 0.98);"
        "}";

    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(270, 278, 260, 38);
    txtUsuario->setPlaceholderText("Nombre de explorador");
    txtUsuario->setStyleSheet(estiloInputs);

    txtContrasena = new QLineEdit(this);
    txtContrasena->setGeometry(270, 328, 260, 38);
    txtContrasena->setEchoMode(QLineEdit::Password);
    txtContrasena->setPlaceholderText("Contraseña secreta");
    txtContrasena->setStyleSheet(estiloInputs);
    connect(txtContrasena, &QLineEdit::textChanged, this, &CrearCuenta::validarContrasena);

    // --- BLOQUE DE REQUISITOS ALINEADO Y CENTRADO ---
    QString estiloReqTitulo = "font-family: 'Georgia'; font-size: 11px; font-weight: bold; color: #d4af37; background: transparent;";
    QString estiloReq = "font-family: 'Georgia'; font-size: 11px; background: transparent;";

    QLabel *lblTituloReq = new QLabel("Requisitos de seguridad:", this);
    lblTituloReq->setGeometry(270, 376, 260, 18);
    lblTituloReq->setStyleSheet(estiloReqTitulo);

    lblReqLongitud = new QLabel("✗ Al menos 5 caracteres", this);
    lblReqLongitud->setGeometry(275, 394, 250, 16);
    lblReqLongitud->setStyleSheet(estiloReq + "color: #e57373;");

    lblReqMayuscula = new QLabel("✗ Al menos una mayúscula", this);
    lblReqMayuscula->setGeometry(275, 410, 250, 16);
    lblReqMayuscula->setStyleSheet(estiloReq + "color: #e57373;");

    lblReqNumero = new QLabel("✗ Al menos un número", this);
    lblReqNumero->setGeometry(275, 426, 250, 16);
    lblReqNumero->setStyleSheet(estiloReq + "color: #e57373;");

    lblReqEspecial = new QLabel("✗ Al menos un carácter especial", this);
    lblReqEspecial->setGeometry(275, 442, 250, 16);
    lblReqEspecial->setStyleSheet(estiloReq + "color: #e57373;");

    // --- BOTÓN PRINCIPAL CON MARCO DE BRONCE ---
    btnCrearCuenta = new QPushButton(this);
    btnCrearCuenta->setGeometry(270, 470, 260, 46);
    QPixmap pixmapBtn(":/btns/crear_cuenta_boton.png");
    btnCrearCuenta->setIcon(QIcon(pixmapBtn));
    btnCrearCuenta->setIconSize(QSize(250, 40));
    btnCrearCuenta->setStyleSheet(
        "QPushButton { border: 2px solid #5c4033; background: rgba(50, 35, 25, 0.9); border-radius: 6px; }"
        "QPushButton:hover { border: 2px solid #d4af37; background: rgba(65, 45, 32, 0.95); }"
        );
    connect(btnCrearCuenta, &QPushButton::clicked, this, &CrearCuenta::onCrearCuentaClicked);

    // --- ENLACE A LOGIN ---
    lblLogin = new QLabel(this);
    lblLogin->setGeometry(250, 528, 300, 24);
    lblLogin->setText("<a href='login' style='color: #d4af37; text-decoration: none; font-weight: bold;'>¿Ya tienes un expediente? Inicia sesión</a>");
    lblLogin->setAlignment(Qt::AlignCenter);
    lblLogin->setStyleSheet("font-family: 'Georgia'; font-size: 12px; background: transparent;");

    // --- BOTÓN REGRESAR ---
    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 65, 65);
    btnRegresar->setStyleSheet(
        "QPushButton { "
        "    border-image: url(:/btns/btn_volver_pequeno.png); "
        "    border: none; "
        "    background: transparent; "
        "} "
        "QPushButton:hover { "
        "    filter: brightness(1.25); "
        "}"
        );

    connect(lblLogin, &QLabel::linkActivated, this, &CrearCuenta::onIniciarSesionClicked);
    connect(btnRegresar, &QPushButton::clicked, this, &CrearCuenta::regresar);
}

CrearCuenta::~CrearCuenta() {}

void CrearCuenta::seleccionarAvatar(int id) {
    avatarSeleccionado = id;
    for(int i = 0; i < botonesAvatares.size(); ++i) {
        botonesAvatares[i]->setChecked(i == id);
    }
}

void CrearCuenta::validarContrasena(const QString &texto) {
    std::string s = texto.toStdString();

    bool cumpleLongitud = (s.length() >= 5);
    bool cumpleMayuscula = false;
    bool cumpleNumero = false;
    bool cumpleEspecial = false;

    for (char c : s) {
        if (std::isupper(c)) cumpleMayuscula = true;
        if (std::isdigit(c)) cumpleNumero = true;
        if (std::ispunct(c)) cumpleEspecial = true;
    }

    QString estiloBase = "font-family: 'Georgia'; font-size: 11px; background: transparent; color: ";

    lblReqLongitud->setText((cumpleLongitud ? "✓" : "✗") + QString(" Al menos 5 caracteres"));
    lblReqLongitud->setStyleSheet(estiloBase + (cumpleLongitud ? "#2e7d32;" : "#b71c1c;"));

    lblReqMayuscula->setText((cumpleMayuscula ? "✓" : "✗") + QString(" Al menos una mayúscula"));
    lblReqMayuscula->setStyleSheet(estiloBase + (cumpleMayuscula ? "#2e7d32;" : "#b71c1c;"));

    lblReqNumero->setText((cumpleNumero ? "✓" : "✗") + QString(" Al menos un número"));
    lblReqNumero->setStyleSheet(estiloBase + (cumpleNumero ? "#2e7d32;" : "#b71c1c;"));

    lblReqEspecial->setText((cumpleEspecial ? "✓" : "✗") + QString(" Al menos un carácter especial"));
    lblReqEspecial->setStyleSheet(estiloBase + (cumpleEspecial ? "#2e7d32;" : "#b71c1c;"));
}

void CrearCuenta::onCrearCuentaClicked() {
    QString usuario = txtUsuario->text().trimmed();
    QString contrasena = txtContrasena->text();

    if (avatarSeleccionado == -1) {
        QMessageBox::warning(this, "Avatar requerido", "Por favor, selecciona un avatar para tu explorador.");
        return;
    }
    if (usuario.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor completa todos los campos.");
        return;
    }

    std::string s = contrasena.toStdString();
    bool cumpleLongitud = (s.length() >= 5);
    bool cumpleMayuscula = false;
    bool cumpleNumero = false;
    bool cumpleEspecial = false;

    for (char c : s) {
        if (std::isupper(c)) cumpleMayuscula = true;
        if (std::isdigit(c)) cumpleNumero = true;
        if (std::ispunct(c)) cumpleEspecial = true;
    }

    if (!cumpleLongitud || !cumpleMayuscula || !cumpleNumero || !cumpleEspecial) {
        QMessageBox::warning(this, "Contraseña no válida", "La contraseña no cumple con todos los requisitos de seguridad.");
        return;
    }

    bool registrado = UserManager::registrarUsuario(usuario.toStdString(), contrasena.toStdString(), avatarSeleccionado);

    if (registrado) {
        QMessageBox::information(this, "¡Éxito!", "Cuenta creada correctamente. ¡Bienvenido al templo!");
        MenuPrincipal *menuPrincipal = new MenuPrincipal(nullptr, usuario);
        menuPrincipal->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Usuario existente", "El nombre de usuario ya está en uso o hubo un error al guardar.");
    }
}

void CrearCuenta::onIniciarSesionClicked() {
    Login *loginWin = new Login();
    loginWin->show();
    this->close();
}

void CrearCuenta::regresar(){
    MenuInicio *inicio = new MenuInicio();
    inicio->show();
    this->close();
}