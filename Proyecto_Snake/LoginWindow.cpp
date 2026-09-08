/*include "loginwindow.h"
#include <QPixmap>
#include <QIcon>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {

    this->setFixedSize(800, 600);
    this->setWindowTitle("Snake - Acceso de Explorador");

    labelFondo = new QLabel(this);
    labelFondo->setGeometry(0, 0, 800, 600);
    QPixmap pixmapFondo(":/recursos/login_fondo.jpg");
    labelFondo->setPixmap(pixmapFondo.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    labelCampoUsuario = new QLabel(this);
    labelCampoUsuario->setGeometry(200, 390, 400, 50);
    QPixmap pixmapCajaUsr(":/recursos/campo_datos1.png");
    labelCampoUsuario->setPixmap(pixmapCajaUsr.scaled(labelCampoUsuario->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    txtUsuario = new QLineEdit(this);
    txtUsuario->setGeometry(220, 398, 360, 35);
    txtUsuario->setPlaceholderText("Nombre de Usuario");
    txtUsuario->setStyleSheet(
        "QLineEdit {"
        "   background: transparent;"
        "   border: none;"
        "   color: #e6c687;"
        "   font-family: 'Georgia', serif;"
        "   font-size: 14px;"
        "}"
        );

    labelCampoPassword = new QLabel(this);
    labelCampoPassword->setGeometry(200, 470, 400, 50);
    labelCampoPassword->setPixmap(pixmapCajaUsr.scaled(labelCampoPassword->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    txtPassword = new QLineEdit(this);
    txtPassword->setGeometry(220, 478, 360, 35);
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setPlaceholderText("Contraseña");
    txtPassword->setStyleSheet(
        "QLineEdit {"
        "   background: transparent;"
        "   border: none;"
        "   color: #e6c687;"
        "   font-family: 'Georgia', serif;"
        "   font-size: 14px;"
        "}"
        );

    btnEntrar = new QPushButton(this);
    btnEntrar->setGeometry(250, 540, 300, 55);
    QPixmap pixmapBtnEntrar(":/recursos/boton_entrar.png");
    btnEntrar->setIcon(QIcon(pixmapBtnEntrar));
    btnEntrar->setIconSize(btnEntrar->size());
    btnEntrar->setStyleSheet("QPushButton { border: none; background: transparent; }");

    lblRegistrarse = new QLabel(this);
    lblRegistrarse->setGeometry(250, 610, 300, 25);
    lblRegistrarse->setText("<a href='registrar' style='color: #c29b38; text-decoration: none;'>¿No tienes cuenta? Regístrate aquí</a>");
    lblRegistrarse->setAlignment(Qt::AlignCenter);
    lblRegistrarse->setOpenExternalLinks(false);

    connect(btnEntrar, &QPushButton::clicked, this, &LoginWindow::onEntrarClicked);
    connect(lblRegistrarse, &QLabel::linkActivated, this, [=](){
        // Lógica para abrir la ventana de registro
    });
}

LoginWindow::~LoginWindow() {
}

void LoginWindow::onEntrarClicked() {
    // Validar credenciales y buscar en archivo de persistencia (requisito del proyecto)
}*/