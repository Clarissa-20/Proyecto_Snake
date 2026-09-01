/*#include "nivel1.h"
#include "ui_gamewindow.h"
#include <QDebug>

Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);


    setFixedSize(800,800);
    setFocusPolicy(Qt::StrongFocus);

    //cargamos aqui la img de fondo para el nivel 1
    fondo.load(":/imagenes/nivel1_fondo.png");

    //nuevo
    cellsize=20;
    marginX=100;
    marginY=120;
    cols=((width()-(2*marginX))/cellsize)-1;
    rows=((height()-marginY-120)/cellsize);
    crearMapa();
    cabeza=new Nodo(5, 5);

    direction=Right;
    gameover=false;

    spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel1::gameloop);

    timer->start(150); //aqui se modifica la rapidez del guano entre mas alto mas lento

    retryButton= new QPushButton("Retry", this);
    retryButton->setGeometry(width()/2-50, height()/2+40, 100, 40);
    retryButton->setStyleSheet("QPushButton{"
                               "background-color:#00aa00;"
                               "color:white;"
                               "font-size:18px;"
                               "border-radius:10px;"
                               "}"
                               "QPushButton:hover{"
                               "background-color:#00cc00;"
                               "}"
                               );
    connect(retryButton, &QPushButton::clicked, this, &Nivel1::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}
*/


#include "nivel1.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QPainter>

Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);


    setFixedSize(800,800);
    setFocusPolicy(Qt::StrongFocus);

    //cargamos aqui la img de fondo para el nivel 1
    fondo.load(":/imagenes/nivel1_fondo.png");

    //nuevo
    cellsize=20;
    marginX=100;
    marginY=120;
    cols=((width()-(2*marginX))/cellsize)-1;
    rows=((height()-marginY-120)/cellsize);
    crearMapa();
    cabeza=new Nodo(5, 5);

    direction=Right;
    gameover=false;

    spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel1::gameloop);

    timer->start(150); //aqui se modifica la rapidez del guano entre mas alto mas lento

    retryButton= new QPushButton("Retry", this);
    retryButton->setGeometry(width()/2-50, height()/2+40, 100, 40);
    retryButton->setStyleSheet("QPushButton{"
                               "background-color:#00aa00;"
                               "color:white;"
                               "font-size:18px;"
                               "border-radius:10px;"
                               "}"
                               "QPushButton:hover{"
                               "background-color:#00cc00;"
                               "}"
                               );
    connect(retryButton, &QPushButton::clicked, this, &Nivel1::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}

void Nivel1::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!fondo.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), fondo);
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    // Cuadro semitransparente para delimitar el área jugable
    painter.setBrush(QColor(0, 0, 0, 140));
    painter.setPen(QPen(QColor(120, 110, 100), 2));
    painter.drawRect(marginX, marginY, cols * cellsize, rows * cellsize);

    Nodo* actual = cabeza;
    bool esCabeza=true;
    while (actual != nullptr)
    {
        if(esCabeza==true)
        {
            painter.setBrush(QColor(0, 255, 180));
            esCabeza=false;
        }
        else
        {
            painter.setBrush(QColor(0, 180, 0));
        }
        painter.setPen(Qt::NoPen);
        int posX = marginX + (actual->x * cellsize);
        int posY = marginY + (actual->y * cellsize);
        painter.drawRoundedRect(posX, posY, cellsize, cellsize, 5, 5);
        actual= actual->siguiente;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    int foodX = marginX + (food.x() * cellsize);
    int foodY = marginY + (food.y() * cellsize);
    painter.drawEllipse(foodX, foodY, cellsize, cellsize);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1").arg(manzanasComidas));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado)
        {
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }
}