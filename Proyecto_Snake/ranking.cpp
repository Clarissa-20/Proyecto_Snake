#include "ranking.h"
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QHeaderView>
#include <fstream>
#include <QDir>
#include <QDirIterator>
#include "usermanager.h"

Ranking::Ranking(QWidget *parent)
    : Ranking (nullptr, parent)
{

}

Ranking::Ranking(QWidget *menuPrincipal, QWidget *parent, const QString &usuario)
    : QWidget(parent),
    menuPrincipal(menuPrincipal),
    usuarioActual(usuario)
{
    setWindowTitle("Ranking");
    setFixedSize(980, 600);
    move(QGuiApplication::primaryScreen()->availableGeometry().center()-rect().center());
    fondo.load(":/imagenes/fondoRanking.png");

    listaGlobal= new QTableWidget(this);
    listaGlobal->setGeometry(108, 185, 322, 350);
    configurarListaGlobal();
    cargarDatosGlobal();

    listaNiveles= new QTableWidget(this);
    listaNiveles->setGeometry(538,185, 311, 350);
    configurarListaNiveles();
    cargarDatosNiveles();

    marcosListas= new QLabel(this);
    QPixmap marcos(":/imagenes/marcosListas.png");
    marcosListas->setPixmap(marcos);
    marcosListas->setScaledContents(true);
    marcosListas->setGeometry(50,90,860,510);
    marcosListas->setAttribute(Qt::WA_TransparentForMouseEvents);
    marcosListas->raise();

    btnVolver= new QPushButton(this);
    btnVolver->setGeometry(30,10, 180,50);
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
    connect(btnVolver, &QPushButton::clicked, this, &Ranking::volverAlMenu);
}

void Ranking::paintEvent(QPaintEvent *event)
{
    //Q_UNUSED(event);
    QPainter painter(this);
    if(!fondo.isNull())
    {
        painter.drawPixmap(rect(), fondo);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }
}

void Ranking::configurarListaGlobal()
{
    listaGlobal->setColumnCount(2);
    QStringList encabezados;

    encabezados<<"Usuario"<<"Puntos Totales";
    listaGlobal->setHorizontalHeaderLabels(encabezados);

    listaGlobal->verticalHeader()->setVisible(false);
    listaGlobal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaGlobal->setSelectionMode(QAbstractItemView::NoSelection);
    listaGlobal->horizontalHeader()->setStretchLastSection(true);
    listaGlobal->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

    listaGlobal->setStyleSheet(
        "QTableWidget {"
        "background-color: rgb(111, 78, 55);"
        "color: white;"
        "gridline-color: rgb(80, 55, 38);"
        "border: 2px solid rgb(60, 40, 25);"
        "font-size: 12px;"
        "}"
        "QHeaderView::section {"
        "background-color: rgb(80, 55, 38);"
        "color: white;"
        "padding: 4px;"
        "border: 1px solid rgb(60, 40, 25);"
        "font-weight: bold;"
        "font-size: 11px;"
        "}"
        );
}

void Ranking::configurarListaNiveles()
{
    listaNiveles->setColumnCount(3);
    QStringList encabezados;

    encabezados<<"Nivel"<<"Manzanas Rojas"<<"Manzanas Doradas";
    listaNiveles->setHorizontalHeaderLabels(encabezados);

    listaNiveles->verticalHeader()->setVisible(false);
    listaNiveles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaNiveles->setSelectionMode(QAbstractItemView::NoSelection);

    listaNiveles->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    listaNiveles->setColumnWidth(0,65);
    listaNiveles->setColumnWidth(1,110);
    listaNiveles->setColumnWidth(2,110);

    listaNiveles->setStyleSheet(
        "QTableWidget {"
        "background-color: rgb(111, 78, 55);"
        "color: white;"
        "gridline-color: rgb(80, 55, 38);"
        "border: 2px solid rgb(60, 40, 25);"
        "font-size: 12px;"
        "}"
        "QHeaderView::section {"
        "background-color: rgb(80, 55, 38);"
        "color: white;"
        "padding: 4px;"
        "border: 1px solid rgb(60, 40, 25);"
        "font-weight: bold;"
        "font-size: 11px;"
        "}"
        );
}

void Ranking::cargarDatosGlobal()
{
    listaGlobal->clearContents();
    listaGlobal->setRowCount(0);

    QString carpeta= QString::fromStdString(UserManager::obtenerCarpetaUsuarios());

    QDirIterator it(carpeta, QDir::Files);
    while(it.hasNext())
    {
        it.next();

        QFileInfo info= it.fileInfo();
        if(info.suffix()!="txt")
        {
            continue;
        }

        QString nombreUsuario= info.completeBaseName();

        Usuario usuario;
        if(UserManager::cargarDatosUsuario(nombreUsuario.toStdString(), usuario)==false)
        {
            continue;
        }

        int fila= listaGlobal->rowCount();
        listaGlobal->insertRow(fila);

        QTableWidgetItem *itemUsuario= new QTableWidgetItem(QString::fromStdString(usuario.username));
        itemUsuario->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *itemPuntos= new QTableWidgetItem();
        itemPuntos->setData(Qt::DisplayRole, usuario.puntosTotales);
        itemPuntos->setTextAlignment(Qt::AlignCenter);

        listaGlobal->setItem(fila, 0, itemUsuario);
        listaGlobal->setItem(fila, 1, itemPuntos);
    }

    int totalFilas= listaGlobal->rowCount();
    for(int i=0; i<totalFilas-1; i++)
    {
        for(int j=0; j<totalFilas-1-i; j++)
        {
            int puntosActual= listaGlobal->item(j, 1)->data(Qt::DisplayRole).toInt();
            int puntosSiguiente= listaGlobal->item(j+1, 1)->data(Qt::DisplayRole).toInt();

            if(puntosActual<puntosSiguiente)
            {
                QTableWidgetItem *tempUsuario= listaGlobal->takeItem(j, 0);
                QTableWidgetItem *tempPuntos= listaGlobal->takeItem(j, 1);

                listaGlobal->setItem(j, 0, listaGlobal->takeItem(j+1, 0));
                listaGlobal->setItem(j, 1, listaGlobal->takeItem(j+1, 1));

                listaGlobal->setItem(j+1, 0, tempUsuario);
                listaGlobal->setItem(j+1, 1, tempPuntos);
            }
        }
    }
}

void Ranking::cargarDatosNiveles()
{
    listaNiveles->clearContents();
    listaNiveles->setRowCount(0);

    if(usuarioActual.isEmpty())
    {
        return;
    }

    QString nombreArchivoQt= carpetaPartidaUsuarios()+"partidasCompletadas_"+usuarioActual+".txt";
    std::string nombreArchivo= nombreArchivoQt.toStdString();

    std::ifstream archivo(nombreArchivo);
    if(archivo.is_open()==false)
    {
        return;
    }

    int totalGanadas=0;
    int totalPerdidas=0;

    int nivelLeido;
    int rojasLeidas;
    int doradasLeidas;
    int ganoLeido;

    while(archivo>>nivelLeido>>rojasLeidas>>doradasLeidas>>ganoLeido)
    {
        if(ganoLeido!=0)
        {
            totalGanadas++;
        }
        else
        {
            totalPerdidas++;
        }
    }
    archivo.close();

    int totalFilas= 1+totalGanadas+1+totalPerdidas;
    listaNiveles->setRowCount(totalFilas);

    agregarFilaEncabezado(0, "Completadas");
    int filaEncabezadoPerdidas= 1+totalGanadas;
    agregarFilaEncabezado(filaEncabezadoPerdidas, "Perdidas");

    archivo.open(nombreArchivo);
    if(archivo.is_open()==false)
    {
        return;
    }

    int filaGanada= 1;
    int filaPerdida= filaEncabezadoPerdidas+1;

    while(archivo>>nivelLeido>>rojasLeidas>>doradasLeidas>>ganoLeido)
    {
        if(ganoLeido!=0)
        {
            agregarFilaPartida(filaGanada, nivelLeido, rojasLeidas, doradasLeidas);
            filaGanada++;
        }
        else
        {
            agregarFilaPartida(filaPerdida, nivelLeido, rojasLeidas, doradasLeidas);
            filaPerdida++;
        }
    }
    archivo.close();
}

void Ranking::volverAlMenu()
{
    if(menuPrincipal!=nullptr)
    {
        menuPrincipal->show();
    }
    this->close();
}
QString Ranking::carpetaPartidaUsuarios() const
{
    QString carpeta="PartidasUsuarios";
    QDir dir;
    if(dir.exists(carpeta)==false)
    {
        dir.mkpath(carpeta);
    }
    return carpeta+"/";
}

void Ranking::agregarFilaEncabezado(int fila, const QString &texto)
{
    QTableWidgetItem *itemEncabezado= new QTableWidgetItem(texto);
    itemEncabezado->setTextAlignment(Qt::AlignCenter);

    QFont fuente= itemEncabezado->font();
    fuente.setBold(true);
    itemEncabezado->setFont(fuente);
    itemEncabezado->setBackground(QColor(80,55,38));
    itemEncabezado->setForeground(Qt::white);

    listaNiveles->setItem(fila, 0, itemEncabezado);
    listaNiveles->setSpan(fila, 0, 1, 3);
}

void Ranking::agregarFilaPartida(int fila, int nivel, int rojas, int doradas)
{
    QTableWidgetItem *itemNivel= new QTableWidgetItem(QString("Nivel %1").arg(nivel));
    QTableWidgetItem *itemRojas= new QTableWidgetItem(QString::number(rojas));
    QTableWidgetItem *itemDoradas= new QTableWidgetItem(QString::number(doradas));

    itemNivel->setTextAlignment(Qt::AlignCenter);
    itemRojas->setTextAlignment(Qt::AlignCenter);
    itemDoradas->setTextAlignment(Qt::AlignCenter);

    listaNiveles->setItem(fila, 0, itemNivel);
    listaNiveles->setItem(fila, 1, itemRojas);
    listaNiveles->setItem(fila, 2, itemDoradas);
}
