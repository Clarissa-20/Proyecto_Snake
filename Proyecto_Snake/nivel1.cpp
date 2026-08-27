#include "nivel1.h"
#include "ui_gamewindow.h"
Nivel1::Nivel1(QWidget *parent)
    : Nivel(parent)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);

    setFixedSize(600,600);
    setFocusPolicy(Qt::StrongFocus);

    cellsize=20;
    rows=height()/cellsize;
    cols=width()/cellsize;
    crearMapa();

    cabeza= new Nodo(10, 10);

    direction=Right;
    gameover=false;

    spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel1::gameloop);

    timer->start(150); /*aqui se modifica la rapidez del guano entre mas alto mas lento*/

    retryButton= new QPushButton("Retry", this);
    retryButton->setGeometry(width()/2-50, height()/2+40, 100, 40);
    retryButton->setStyleSheet("QPushButton{"
                               "background-color:#00aa00;"
                               "color:white;"
                               "font-size:18px;"
                               "border-raduis:10px;"
                               "}"
                               "QPushButton:hover{"
                               "background-color:#00cc00;"
                               "}"
                               );
    connect(retryButton, &QPushButton::clicked, this, &Nivel1::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}
