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
    this->setWindowTitle("Snake - Registro de Explorador");


    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/imagenes/crear_cuenta_fondo.png");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QString estiloInputs = "QLineEdit {"
                           "background: transparent;"
                           "border: none;"
                           "color: #e6dfc8;"
                           "font-family: 'Georgia';"
                           "font-size: 16px;"
                           "padding-left: 10px;"
                           "}";

    int avatarAncho = 65;
    int avatarAlto = 65;
    int avatarY = 195;
    int xs[4] = {295, 370, 445, 520};

    for(int i = 0; i < 4; ++i) {  //CAMBIAR LOS AVATARES
        QPushButton *btnAvatar = new QPushButton(this);
        btnAvatar->setGeometry(xs[i], avatarY, avatarAncho, avatarAlto);
        QString rutaAvatar = QString(":/imagenes/avatar_%1.png").arg(i + 1);
        btnAvatar->setIcon(QIcon(rutaAvatar));
        btnAvatar->setIconSize(QSize(avatarAncho - 10, avatarAlto - 10));
        btnAvatar->setCheckable(true);
        btnAvatar->setStyleSheet("QPushButton { border: 2px solid transparent; background: rgba(0,0,0,0.3); border-radius: 5px; }"
                                 "QPushButton:checked { border: 2px solid #d4af37; background: rgba(212,175,55,0.3); }");

        connect(btnAvatar, &QPushButton::clicked, [this, i]() {
            seleccionarAvatar(i);
        });
        botonesAvatares.append(btnAvatar);
    }


    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(275, 290, 260, 35);
    txtUsuario->setPlaceholderText("Usuario");
    txtUsuario->setStyleSheet(estiloInputs);


    txtContrasena = new QLineEdit(this);
    txtContrasena->setGeometry(275, 345, 260, 35);
    txtContrasena->setEchoMode(QLineEdit::Password);
    txtContrasena->setPlaceholderText("Contraseña");
    txtContrasena->setStyleSheet(estiloInputs);
    connect(txtContrasena, &QLineEdit::textChanged, this, &CrearCuenta::validarContrasena);

    QString estiloReq = "font-family: 'Georgia'; font-size: 11px; background: transparent;";

    QLabel *lblTituloReq = new QLabel("Requisitos de Contraseña:", this);
    lblTituloReq->setGeometry(390, 395, 180, 20);
    lblTituloReq->setStyleSheet("font-family: 'Georgia'; font-size: 12px; font-weight: bold; color: #3e2723; background: transparent;");

    lblReqLongitud = new QLabel("✗ Al menos 5 caracteres", this);
    lblReqLongitud->setGeometry(395, 415, 180, 18);
    lblReqLongitud->setStyleSheet(estiloReq + "color: #b71c1c;");

    lblReqMayuscula = new QLabel("✗ Al menos una mayúscula", this);
    lblReqMayuscula->setGeometry(395, 433, 180, 18);
    lblReqMayuscula->setStyleSheet(estiloReq + "color: #b71c1c;");

    lblReqNumero = new QLabel("✗ Al menos un número", this);
    lblReqNumero->setGeometry(395, 451, 180, 18);
    lblReqNumero->setStyleSheet(estiloReq + "color: #b71c1c;");

    lblReqEspecial = new QLabel("✗ Al menos un carácter especial", this);
    lblReqEspecial->setGeometry(395, 469, 195, 18);
    lblReqEspecial->setStyleSheet(estiloReq + "color: #b71c1c;");

    btnCrearCuenta = new QPushButton(this);
    btnCrearCuenta->setGeometry(270, 500, 260, 50);
    QPixmap pixmapBtn(":/btns/crear_cuenta_boton.png");
    btnCrearCuenta->setIcon(QIcon(pixmapBtn));
    btnCrearCuenta->setIconSize(btnCrearCuenta->size());
    btnCrearCuenta->setStyleSheet("QPushButton { border: none; background: transparent; }");
    connect(btnCrearCuenta, &QPushButton::clicked, this, &CrearCuenta::onCrearCuentaClicked);

    lblLogin = new QLabel(this);
    lblLogin->setGeometry(250, 560, 300, 25);
    lblLogin->setText("<a href='login' style='color: #d4af37; text-decoration: none;'>¿Ya tienes una cuenta? Inicia sesion</a>");
    lblLogin->setAlignment(Qt::AlignCenter);
    lblLogin->setStyleSheet("font-family: 'Georgia'; font-size: 13px; background: transparent;");

    btnRegresar = new QPushButton(this);
    btnRegresar->setGeometry(20, 20, 80, 80);
    btnRegresar->setStyleSheet(
        "QPushButton {"
        "   border-image: url(:/imagenes/btn_volver_pequeno.png);"
        "   border: none;"
        "   background: transparent;"
        "}"
        "QPushButton:hover {"
        "   filter: brightness(1.2);"
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
        MenuPrincipal *menuPrincipal = new MenuPrincipal();
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