#include "menuniveles.h"
#include <QPainter>
#include "instruccionesnivel.h"
#include "usermanager.h"
menuNiveles::menuNiveles(QWidget *parent)
    : QWidget(parent),
    sonidoActivado(true),
    ventanaNivel1(nullptr),
    ventanaNivel2(nullptr),
    ventanaNivel3(nullptr),
    menuPrincipal(nullptr)
{
    setWindowTitle("Mapa de niveles");
    fondoMenu.load(":/imagenes/mapaNiveles.png");

    QScreen *pantalla= QGuiApplication::primaryScreen();
    QRect geometriaPantalla= pantalla->geometry();
    this->setGeometry(geometriaPantalla);


    btnNivel3= new QPushButton(this);
    btnNivel1= new QPushButton(this);
    btnNivel2= new QPushButton(this);
    btnVolver= new QPushButton(this);
    btnSonido= new QPushButton(this);

    btnNivel1->setGeometry(410,565, 240,270);
    btnNivel2->setGeometry(875,450, 220,250);
    btnNivel3->setGeometry(468,358, 200,230);
    btnVolver->setGeometry(30,10, 180,50);
    btnSonido->setGeometry(1325,10, 180,50);

    btnNivel1->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/monoNivel1.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/monoNivel1.png);"
        "}"
        );
    btnNivel2->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/monoNivel2.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/monoNivel2.png);"
        "}"
        );
    btnNivel3->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/monoNivel3.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/monoNivel3.png);"
        "}"
        );
    btnVolver->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/btnVolverMenu.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/btns/btnVolverMenu.png);"
        "}"
        );

    btnSonido->setStyleSheet(
        "QPushButton {"
        "border-image: url(:/btns/btnConMusica.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
        );
    connect(btnNivel1, &QPushButton::clicked, this, [this](){mostrarInstrucciones(1);});
    connect(btnNivel2, &QPushButton::clicked, this, [this](){mostrarInstrucciones(2);});
    connect(btnNivel3, &QPushButton::clicked, this, [this](){mostrarInstrucciones(3);});

    connect(btnSonido, &QPushButton::clicked, this, &menuNiveles::alternarSonido);
    connect(btnVolver, &QPushButton::clicked, this, &menuNiveles::volverAlMenu);

}

menuNiveles::menuNiveles(QWidget *menu, bool desdeMenuPrincipal, const QString &usuario)
    :menuNiveles(nullptr)
{
    menuPrincipal= menu;
    usuarioActual=usuario;
    Usuario datosUsuario;
    if(UserManager::cargarDatosUsuario(usuario.toStdString(), datosUsuario)==true)
    {
        actualizarBotonesNiveles(datosUsuario.nivelActual);
    }
    else
    {
        actualizarBotonesNiveles(1);
    }
}

void menuNiveles::paintEvent(QPaintEvent *event)
{
    if(usuarioActual.isEmpty()==false)
    {
        Usuario datosUsuarioActual;
        if(UserManager::cargarDatosUsuario(usuarioActual.toStdString(), datosUsuarioActual)==true)
        {
            actualizarBotonesNiveles(datosUsuarioActual.nivelActual);
        }
    }
    QPainter painter(this);

    if(!fondoMenu.isNull())
    {
        painter.drawPixmap(rect(), fondoMenu);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }
}

void menuNiveles::mostrarInstrucciones(int nivel)
{
    InstruccionesNivel *ventanaInstrucciones= new InstruccionesNivel(nivel, this);
    ventanaInstrucciones->setAttribute(Qt::WA_DeleteOnClose);
    ventanaInstrucciones->show();
    this->hide();
}

void menuNiveles::abrirNivel1()
{
    if(ventanaNivel1==nullptr)
    {
        ventanaNivel1= new Nivel1();
        ventanaNivel1->setMenuNiveles(this);
        ventanaNivel1->setUsuarioActual(usuarioActual);
        ventanaNivel1->iniciarPartida();
        ventanaNivel1->setAttribute(Qt::WA_DeleteOnClose);
        connect(ventanaNivel1, &QObject::destroyed, this, [this]() {ventanaNivel1=nullptr;});
    }
    ventanaNivel1->show();
    this->hide();
}

void menuNiveles::abrirNivel2()
{
    if(ventanaNivel2==nullptr)
    {
        ventanaNivel2= new Nivel2();
        ventanaNivel2->setMenuNiveles(this);
        ventanaNivel2->setUsuarioActual(usuarioActual);
        ventanaNivel2->iniciarPartida();
        ventanaNivel2->setAttribute(Qt::WA_DeleteOnClose);
        connect(ventanaNivel2, &QObject::destroyed, this, [this]() {ventanaNivel2=nullptr;});

    }
    ventanaNivel2->show();
    this->hide();
}

void menuNiveles::abrirNivel3()
{
    if(ventanaNivel3==nullptr)
    {
        ventanaNivel3= new Nivel3();
        ventanaNivel3->setMenuNiveles(this);
        ventanaNivel3->setUsuarioActual(usuarioActual);
        ventanaNivel3->iniciarPartida();
        ventanaNivel3->setAttribute(Qt::WA_DeleteOnClose);
        connect(ventanaNivel3, &QObject::destroyed, this, [this]() {ventanaNivel3=nullptr;});

    }
    ventanaNivel3->show();
    this->hide();
}

void menuNiveles::alternarSonido()
{
    if(sonidoActivado==true)
    {
        btnSonido->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/btnSinMusica.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        sonidoActivado=false;
    }
    else
    {
        btnSonido->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/btnConMusica.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            /*"QPushButton:pressed {"
        "border-image: url(:/imagenes/btnConSonido.png);"
        "}"*/
            );
        sonidoActivado=true;

    }
}

void menuNiveles::volverAlMenu()
{
    if(menuPrincipal!=nullptr)
    {
        menuPrincipal->show();
    }
    this->close();
}

void menuNiveles::actualizarBotonesNiveles(int nivelActual)
{
    btnNivel1->setEnabled(true);

    bool nivel2Desbloqueado=(nivelActual>=2);
    bool nivel3Desbloqueado=(nivelActual>=3);

    btnNivel2->setEnabled(nivel2Desbloqueado);
    if(nivel2Desbloqueado==true)
    {
        btnNivel2->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/monoNivel2.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            "QPushButton:pressed {"
            "border-image: url(:/btns/monoNivel2.png);"
            "}"
            );
    }
    else
    {
        btnNivel2->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/monoNivel2Desactivado.png);"
            "border: none;"
            "}"
            );
    }

    btnNivel3->setEnabled(nivel3Desbloqueado);
    if(nivel3Desbloqueado==true)
    {
        btnNivel3->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/monoNivel3.png);"
            "border: none;"
            "}"
            "QPushButton:hover {"
            "opacity: 0.8;"
            "}"
            "QPushButton:pressed {"
            "border-image: url(:/btns/monoNivel3.png);"
            "}"
            );
    }
    else
    {
        btnNivel3->setStyleSheet(
            "QPushButton {"
            "border-image: url(:/btns/monoNivel3Desactivado.png);"
            "border: none;"
            "}"
            );
    }
}

