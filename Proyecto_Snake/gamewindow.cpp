#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
    //integración de nodo prueba #1
    , cabeza(nullptr)
    //integracion de mapa prueba#1
    , mapa(nullptr)
    //nivel1
    , hayComidaDorada(false)
    , crecimientoExtra(0)
    , manzanasComidas(0)
    , puntuacion(0)
    , nivelGanado(false)

{
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

    connect(timer, &QTimer::timeout, this, &GameWindow::gameloop);

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
    connect(retryButton, &QPushButton::clicked, this, &GameWindow::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}
//destructor
GameWindow::~GameWindow()
{
    limpiarSerpiente();

    //integracion de mapa prueba#1
    destruirMapa();

    delete ui;
}

void GameWindow::gameloop()
{
    if(gameover==true)
    {
        return;
    }

    moveSnake();
    checkCollision();
    update();
}

void GameWindow::resetGame()
{
    //snake.clear();
    //snake.append(QPoint(10,10));

    //integración de nodo prueba #1
    limpiarSerpiente();
    //integración de nodo prueba #1
    cabeza = new Nodo(10, 10);

    direction=Right;
    gameover=false;

    //NIVEL 1: reiniciar todo lo relacionado al nivel 2
    manzanasComidas=0;
    puntuacion=0;
    nivelGanado=false;
    hayComidaDorada=false;
    crecimientoExtra=0; //NIVEL 1

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(150);
    update();
}

void GameWindow::moveSnake()
{
    //QPoint Head= snake.first();

    //integración de nodo prueba #1
    if(cabeza==nullptr)
    {
        return;
    }
    int newX= cabeza->x;
    int newY= cabeza->y;

    switch (direction)
    {
    case Up:
    {
        newY--;
        break;
    }
    case Down:
    {
        newY++;
        break;
    }
    case Right:
    {
        newX++;
        break;
    }
    case Left:
    {
        newX--;
        break;
    }
    }
    /*
    snake.prepend(Head);
    if(Head==food)
    {
        spawnFood();
    }
    else
    {
        snake.removeLast();
    }
    */
    //bordes infinito
    if(newX<0)
    {
        newX=cols-1;
    }
    else if(newX>=cols)
    {
        newX=0;
    }

    if(newY<0)
    {
        newY=rows-1;
    }
    else if(newY>=rows)
    {
        newY=0;
    }
    //integración de nodo prueba #1
    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;

    //NIVEL 1: bandera para saber si la serpiente comió algo en este movimiento (roja o dorada)
    bool comioAlgo=false;

    //NIVEL 1: primero se revisa la manzana dorada (si está presente)
    if(hayComidaDorada && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += 30; //NIVEL 1: puntos triples (10 x 3)
        hayComidaDorada=false; //la dorada desaparece al comerla
        crecimientoExtra += 2; //NIVEL 1: este movimiento ya crece 1 (no se borra la cola); +2 para sumar 3 en total
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y())
    {
        comioAlgo=true;
        manzanasComidas++; //NIVEL 1
        puntuacion += 10;
        //NIVEL 1: si se come la roja, la dorada (si estaba en pantalla) desaparece también
        hayComidaDorada=false;

        if(manzanasComidas >= MANZANAS_META)
        {
            //NIVEL 2: se completaron las 6 manzanas rojas -> se gana el nivel
            nivelGanado=true;
            gameover=true;
            timer->stop();
            retryButton->show();
        }
        else
        {
            spawnFood();
            intentoComidaDorada(); //NIVEL 1: probabilidad de que salga una dorada junto a la nueva roja
        }
    }
    if(comioAlgo==false)
    {
        //NIVEL 1: si queda crecimiento pendiente (de una dorada comida antes), la cola NO se recorta y ese crecimiento pendiente se va consumiendo un nodo por movimiento.
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente !=nullptr)//?
        {
            Nodo* actual=cabeza;
            while(actual->siguiente->siguiente != nullptr)
            {
                actual=actual->siguiente;
            }
            delete actual->siguiente;
            actual->siguiente=nullptr;
        }
    }
}

void GameWindow::spawnFood()
{
    int x= QRandomGenerator::global()->bounded(cols);
    int y= QRandomGenerator::global()->bounded(rows);
    food= QPoint(x,y);
}

void GameWindow::checkCollision()
{
    //QPoint Head = snake.first();

    /*if(Head.x()<0 || Head.y()<0 || Head.x()>=cols || Head.y()>=rows)
    {
        gameover=true;
        timer->stop();
        retryButton->show();
    }*/

    //integración de nodo prueba #1
    if(cabeza==nullptr)
    {
        return;
    }

    int cabezaX= cabeza->x;
    int cabezaY= cabeza->y;

    if(cabezaX<0 || cabezaY<0 || cabezaX>=cols || cabezaY>=rows)
    {
        gameover=true;
        timer->stop();
        retryButton->show();
        return;
    }
    /*
    for(int i=1; i<snake.size(); i++)
    {
        if(Head==snake[i])
        {
            gameover=true;
            timer->stop();
            retryButton->show();
        }
    }*/
    Nodo* actual = cabeza->siguiente;
    while(actual !=nullptr)
    {
        if(cabezaX==actual->x && cabezaY==actual->y)
        {
            gameover=true;
            timer->stop();
            retryButton->show();
            return;
        }
        actual=actual->siguiente;
    }
}

//integracion de mapa prueba#1
void GameWindow::crearMapa()
{
    mapa = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        mapa[i]= new int[cols];
        for (int j = 0; j < cols; j++)
        {
            mapa[i][j]=0; //0=vacía
        }
    }
}
//integracion de mapa prueba#1
void GameWindow::destruirMapa()
{
    if(mapa != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mapa[i];
        }

        delete[] mapa;
        mapa=nullptr;
    }
}
//integración de nodo prueba #1
void GameWindow::limpiarSerpiente()
{
    Nodo* actual=cabeza;
    while(actual!=nullptr)
    {
        Nodo* siguiente =actual->siguiente;
        delete actual;
        actual=siguiente;
    }
    cabeza=nullptr;
}
//integración de nodo prueba #1
int GameWindow::obtenerLongitudSerpiente()
{
    int longitud =0;
    Nodo* actual=cabeza;
    while(actual !=nullptr)
    {
        longitud++;
        actual=actual->siguiente;
    }
    return longitud;
}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    /*painter.setBrush(Qt::green);

    for (int i = 0; i < snake.size(); i++)
    {
        if(i==0)
        {
            painter.setBrush(QColor(0,255,180));
        }
        else
        {
            painter.setBrush(QColor(0,180,0));
        }

        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(snake[i].x()*cellsize, snake[i].y()*cellsize, cellsize, cellsize, 5,5);
    }*/

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
        painter.drawRoundedRect(actual->x*cellsize, actual->y*cellsize, cellsize, cellsize, 5,5);
        actual= actual->siguiente;
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawEllipse(food.x()*cellsize, food.y()*cellsize, cellsize, cellsize);

    //nivel 1
    if(hayComidaDorada)
    {
        painter.setBrush(QColor(255,215,0));
        painter.drawEllipse(comidaDorada.x()*cellsize, comidaDorada.y()*cellsize, cellsize, cellsize);
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1/%2").arg(manzanasComidas).arg(MANZANAS_META));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado)
        {
            //NIVEL 1: mensaje de victoria al completar las 6 manzanas rojas
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
    {
        if(direction!=Down)
        {
            direction=Up;
        }
        break;
    }
    case Qt::Key_Down:
    {
        if(direction!=Up)
        {
            direction=Down;
        }
        break;
    }
    case Qt::Key_Left:
    {
        if(direction!=Right)
        {
            direction=Left;
        }
        break;
    }
    case Qt::Key_Right:
    {
        if(direction!=Left)
        {
            direction=Right;
        }
        break;
    }
    }
}

void GameWindow::intentoComidaDorada()
{
    int probabilidad = QRandomGenerator::global()->bounded(100);
    if(probabilidad >= 40)
    {
        return;
    }

    int x=0;
    int y=0;
    bool posicionValida;
    int intentos=0;

    do
    {
        x= QRandomGenerator::global()->bounded(cols);
        y= QRandomGenerator::global()->bounded(rows);
        posicionValida=true;

        //no debe salir sobre un muro
        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }

        //no debe salir en la misma celda que la manzana roja
        if(posicionValida && x==food.x() && y==food.y())
        {
            posicionValida=false;
        }

        //no debe salir sobre la serpiente
        if(posicionValida==true)
        {
            Nodo* actual=cabeza;
            while(actual!=nullptr)
            {
                if(actual->x==x && actual->y==y)
                {
                    posicionValida=false;
                    break;
                }
                actual=actual->siguiente;
            }
        }

        intentos++;
    } while(!posicionValida && intentos<100); //límite de intentos por seguridad

    if(posicionValida==true)
    {
        comidaDorada= QPoint(x,y);
        hayComidaDorada=true;
    }
}