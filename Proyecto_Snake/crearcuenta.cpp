#include "crearcuenta.h"
#include "login.h"
#include "menuprincipal.h"
#include "usermanager.h"
#include "menuInicio.h"
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include <QFrame>
#include <fstream>
#include <sstream>
#include <cctype>

CrearCuenta::CrearCuenta(QWidget *parent)
    : QMainWindow(parent), avatarSeleccionado(-1) {

    this->setFixedSize(1280, 720);
    this->setWindowTitle("Snake - El Templo Perdido | Registro de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 1280, 720);
    QPixmap pixmapFondo(":/imagenes/crear_cuenta_fondo.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    int xCentro = 430;
    int anchoBloque = 420;

    QLabel *lblSelAvatar = new QLabel("SELECCIONA TU EXPLORADOR", this);
    lblSelAvatar->setGeometry(xCentro, 182, anchoBloque, 26);
    lblSelAvatar->setAlignment(Qt::AlignCenter);
    lblSelAvatar->setStyleSheet("font-family: 'Georgia'; font-size: 14px; font-weight: bold; color: #ffd700; background: rgba(20, 12, 8, 0.78); border-radius: 4px; padding: 2px; letter-spacing: 1px;");

    int avatarAncho = 78;
    int avatarAlto = 78;
    int avatarY = 214;
    int avatarSpacing = 14;
    int totalAvatarWidth = (4 * avatarAncho) + (3 * avatarSpacing);
    int startAvatarX = xCentro + (anchoBloque - totalAvatarWidth) / 2;

    for(int i = 0; i < 4; ++i) {
        QPushButton *btnAvatar = new QPushButton(this);
        int ax = startAvatarX + i * (avatarAncho + avatarSpacing);
        btnAvatar->setGeometry(ax, avatarY, avatarAncho, avatarAlto);
        QString rutaAvatar = QString(":/imagenes/avatar_%1.png").arg(i + 1);
        btnAvatar->setIcon(QIcon(rutaAvatar));
        btnAvatar->setIconSize(QSize(avatarAncho - 14, avatarAlto - 14));
        btnAvatar->setCheckable(true);
        btnAvatar->setStyleSheet(
            "QPushButton { "
            "    border: 2.5px solid #5c4033; "
            "    background: rgba(30, 20, 15, 0.88); "
            "    border-radius: 12px; "
            "} "
            "QPushButton:hover { "
            "    border: 2.5px solid #a67c52; "
            "    background: rgba(45, 30, 22, 0.95); "
            "} "
            "QPushButton:checked { "
            "    border: 3px solid #d4af37; "
            "    background: rgba(212, 175, 55, 0.38); "
            "}"
            );

        connect(btnAvatar, &QPushButton::clicked, [this, i]() {
            seleccionarAvatar(i + 1);
        });
    }

    QString estiloInputs =
        "QLineEdit {"
        "    background: rgba(35, 25, 18, 0.94);"
        "    border: 2.5px solid #5c4033;"
        "    border-radius: 9px;"
        "    color: #f4efdc;"
        "    font-family: 'Georgia';"
        "    font-size: 17px;"
        "    padding-left: 14px;"
        "}"
        "QLineEdit:focus {"
        "    border: 3px solid #d4af37;"
        "    background: rgba(45, 33, 24, 0.98);"
        "}";

    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(xCentro, 304, anchoBloque, 48);
    txtUsuario->setPlaceholderText("Nombre de explorador");
    txtUsuario->setStyleSheet(estiloInputs);

    txtContrasena = new QLineEdit(this);
    txtContrasena->setGeometry(xCentro, 362, anchoBloque, 48);
    txtContrasena->setEchoMode(QLineEdit::Password);
    txtContrasena->setPlaceholderText("Contraseña secreta");
    txtContrasena->setStyleSheet(estiloInputs);
    connect(txtContrasena, &QLineEdit::textChanged, this, &CrearCuenta::validarContrasena);

    QFrame *frameReq = new QFrame(this);
    frameReq->setGeometry(xCentro, 420, anchoBloque, 108);
    frameReq->setStyleSheet("background: rgba(18, 10, 6, 0.85); border: 2px solid #5c4033; border-radius: 8px;");

    QString estiloReqTitulo = "font-family: 'Georgia'; font-size: 13px; font-weight: bold; color: #ffd700; background: transparent;";
    QString estiloReq = "font-family: 'Georgia'; font-size: 13px; background: transparent; font-weight: bold;";

    QLabel *lblTituloReq = new QLabel("Requisitos de seguridad:", frameReq);
    lblTituloReq->setGeometry(14, 8, anchoBloque - 28, 20);
    lblTituloReq->setStyleSheet(estiloReqTitulo);

    lblReqLongitud = new QLabel("✗ Al menos 5 caracteres", frameReq);
    lblReqLongitud->setGeometry(18, 28, anchoBloque - 36, 18);
    lblReqLongitud->setStyleSheet(estiloReq + "color: #ff5252;");

    lblReqMayuscula = new QLabel("✗ Al menos una mayúscula", frameReq);
    lblReqMayuscula->setGeometry(18, 46, anchoBloque - 36, 18);
    lblReqMayuscula->setStyleSheet(estiloReq + "color: #ff5252;");

    lblReqNumero = new QLabel("✗ Al menos un número", frameReq);
    lblReqNumero->setGeometry(18, 64, anchoBloque - 36, 18);
    lblReqNumero->setStyleSheet(estiloReq + "color: #ff5252;");

    lblReqEspecial = new QLabel("✗ Al menos un carácter especial", frameReq);
    lblReqEspecial->setGeometry(18, 82, anchoBloque - 36, 18);
    lblReqEspecial->setStyleSheet(estiloReq + "color: #ff5252;");

    btnCrearCuenta = new QPushButton(this);
    btnCrearCuenta->setGeometry(xCentro, 538, anchoBloque, 66);
    QPixmap pixmapBtn(":/btns/crear_cuenta_boton.png");
    btnCrearCuenta->setIcon(QIcon(pixmapBtn));
    btnCrearCuenta->setIconSize(QSize(anchoBloque - 10, 58));
    btnCrearCuenta->setStyleSheet(
        "QPushButton { border: none; background: transparent; }"
        "QPushButton:hover { filter: brightness(1.25); }"
        );
    connect(btnCrearCuenta, &QPushButton::clicked, this, &CrearCuenta::onCrearCuentaClicked);

    lblLogin = new QLabel(this);
    lblLogin->setGeometry(xCentro, 616, anchoBloque, 30);
    lblLogin->setText("<a href='login' style='color: #ffd700; text-decoration: none; font-weight: bold;'>¿Ya tienes un expediente? Inicia sesión</a>");
    lblLogin->setAlignment(Qt::AlignCenter);
    lblLogin->setStyleSheet("font-family: 'Georgia'; font-size: 14px; background: rgba(20, 12, 8, 0.7); border-radius: 4px; padding: 2px;");

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 80, 80);
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
        botonesAvatares[i]->setChecked((i + 1) == id);
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

    QString estiloBase = "font-family: 'Georgia'; font-size: 13px; background: transparent; font-weight: bold; color: ";

    lblReqLongitud->setText((cumpleLongitud ? "✓" : "✗") + QString(" Al menos 5 caracteres"));
    lblReqLongitud->setStyleSheet(estiloBase + (cumpleLongitud ? "#2e7d32;" : "#ff5252;"));

    lblReqMayuscula->setText((cumpleMayuscula ? "✓" : "✗") + QString(" Al menos una mayúscula"));
    lblReqMayuscula->setStyleSheet(estiloBase + (cumpleMayuscula ? "#2e7d32;" : "#ff5252;"));

    lblReqNumero->setText((cumpleNumero ? "✓" : "✗") + QString(" Al menos un número"));
    lblReqNumero->setStyleSheet(estiloBase + (cumpleNumero ? "#2e7d32;" : "#ff5252;"));

    lblReqEspecial->setText((cumpleEspecial ? "✓" : "✗") + QString(" Al menos un carácter especial"));
    lblReqEspecial->setStyleSheet(estiloBase + (cumpleEspecial ? "#2e7d32;" : "#ff5252;"));
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