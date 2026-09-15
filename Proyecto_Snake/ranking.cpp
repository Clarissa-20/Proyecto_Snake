#include "ranking.h"
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QHeaderView>


Ranking::Ranking(QWidget *parent)
    : Ranking (nullptr, parent)
{

}

Ranking::Ranking(QWidget *menuPrincipal, QWidget *parent)
    : QWidget(parent),
    menuPrincipal(menuPrincipal)
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
        "border-image: url(:/imagenes/btnVolverMenu.png);"
        "border: none;"
        "}"
        "QPushButton:hover {"
        "opacity: 0.8;"
        "}"
        "QPushButton:pressed {"
        "border-image: url(:/imagenes/btnVolverMenu.png);"
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
    //datos prueba no reales
    const int TOTAL_FILAS = 30;

    listaGlobal->setRowCount(TOTAL_FILAS);
    for(int fila = 0; fila < TOTAL_FILAS; fila++)
    {
        QString nombre = QString("Jugador%1").arg(fila + 1);
        int puntos = 500 - (fila * 15); // puntaje descendente de ejemplo

        QTableWidgetItem *itemUsuario = new QTableWidgetItem(nombre);
        QTableWidgetItem *itemPuntos = new QTableWidgetItem(QString::number(puntos));

        itemUsuario->setTextAlignment(Qt::AlignCenter);
        itemPuntos->setTextAlignment(Qt::AlignCenter);

        listaGlobal->setItem(fila, 0, itemUsuario);
        listaGlobal->setItem(fila, 1, itemPuntos);
    }
}

void Ranking::cargarDatosNiveles()
{
    //datos prueba no reales
    const int TOTAL_FILAS = 30;

    listaNiveles->setRowCount(TOTAL_FILAS);
    for(int fila = 0; fila < TOTAL_FILAS; fila++)
    {
        QString nivel = QString("Nivel %1").arg(fila + 1);
        int rojas = 10 - (fila % 10);   // valores de ejemplo
        int doradas = 4 - (fila % 4);   // valores de ejemplo

        QTableWidgetItem *itemNivel = new QTableWidgetItem(nivel);
        QTableWidgetItem *itemRojas = new QTableWidgetItem(QString::number(rojas));
        QTableWidgetItem *itemDoradas = new QTableWidgetItem(QString::number(doradas));

        itemNivel->setTextAlignment(Qt::AlignCenter);
        itemRojas->setTextAlignment(Qt::AlignCenter);
        itemDoradas->setTextAlignment(Qt::AlignCenter);

        listaNiveles->setItem(fila, 0, itemNivel);
        listaNiveles->setItem(fila, 1, itemRojas);
        listaNiveles->setItem(fila, 2, itemDoradas);
    }
}

void Ranking::volverAlMenu()
{
    if(menuPrincipal!=nullptr)
    {
        menuPrincipal->show();
    }
    this->close();
}
