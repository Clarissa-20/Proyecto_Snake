#include "nivel2.h"
#include "ui_gamewindow.h"

Nivel2::Nivel2(QWidget *parent)
    : Nivel(parent)
    , velocidadBase(VELOCIDAD_INICIAL)
    , efectoDoradaActivo(false)
    , generacionPartida(0)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);

    setFixedSize(600,600);
    setFocusPolicy(Qt::StrongFocus);

    cellsize=20;
    rows=height()/cellsize;
    cols=width()/cellsize;
    crearMapa();
    generarMuros(); //se agrega la cruz de muros en el mapa

    cabeza= new Nodo(10, 10);

    direction=Right;
    gameover=false;

    spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel2::gameloop);

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
    connect(retryButton, &QPushButton::clicked, this, &Nivel2::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}

void Nivel2::generarMuros()
{
    int centroFila = rows/2;
    int centroColumna = cols/2;
    int grosor = 2;     //la mitad del ancho de cada brazo (ancho total = 2*2 + 1)
    int largoBrazo = 8; //cuántas celdas se extiende cada brazo desde el centro. Largo total = 8*2+1

    //linea vertical de la cruz |
    for(int i = centroFila-largoBrazo; i <= centroFila+largoBrazo; i++)
    {
        for(int j = centroColumna-grosor; j <= centroColumna+grosor; j++)
        {
            if(i>=0 && i<rows && j>=0 && j<cols)
            {
                mapa[i][j]=1;
            }
        }
    }
    //linea horizontal de la cruz -
    for(int i = centroFila-grosor; i <= centroFila+grosor; i++)
    {
        for(int j = centroColumna-largoBrazo; j <= centroColumna+largoBrazo; j++)
        {
            if(i>=0 && i<rows && j>=0 && j<cols)
            {
                mapa[i][j]=1;
            }
        }
    }
}

void Nivel2::aumentarVelocidad()
{
    if(velocidadBase > VELOCIDAD_MINIMA)
    {
        velocidadBase -= 10;
        //si el efecto de la dorada está activo, no se toca el timer ahora mismo; restaurarVelocidadNormal() usará el velocidadBase ya actualizado cuando termine el efecto
        if(efectoDoradaActivo==false)
        {
            timer->setInterval(velocidadBase);
        }
    }
}

void Nivel2::activarReduccionVelocidad() //el juego se vuelve un poquito mas lento cuando come una dorada
{
    efectoDoradaActivo=true;
    timer->setInterval(velocidadBase + 80);

    int generacionActual = generacionPartida;
    QTimer::singleShot(5000, this, [this, generacionActual]()
                       {
                           //evita aplicar el efecto si la partida ya fue reiniciada mientras tanto
                           if(generacionActual == generacionPartida)
                           {
                               restaurarVelocidadNormal();
                           }
                       });
}

void Nivel2::moveSnake()
{
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

    //integración de nodo prueba #1

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;
    bool comioAlgo=false;
    if(hayComidaDorada==true && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += 30;
        hayComidaDorada=false;
        activarReduccionVelocidad();
        crecimientoExtra += 2;
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y())
    {
        comioAlgo=true;
        manzanasComidas++;
        puntuacion += 10;

        hayComidaDorada=false;

        if(manzanasComidas >= MANZANAS_META)
        {
            nivelGanado=true;
            gameover=true;
            timer->stop();
            retryButton->show();
        }
        else
        {
            if(manzanasComidas % 2 == 0)
            {
                aumentarVelocidad();
            }

            spawnFood();
            intentoComidaDorada();
        }
    }

    if(!comioAlgo)
    {
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente !=nullptr)
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

void Nivel2::spawnFood()
{
    int x=0;
    int y=0;
    bool posicionValida;

    //NIVEL 2: ahora se evita que la manzana roja aparezca sobre un muro o sobre la serpiente
    do
    {
        x= QRandomGenerator::global()->bounded(cols);
        y= QRandomGenerator::global()->bounded(rows);
        posicionValida=true;

        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }

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

    } while(posicionValida==false);

    food= QPoint(x,y);
}

void Nivel2::checkCollision()
{
    if(cabeza==nullptr)
    {
        return;
    }
    //integración de nodo prueba #1
    int cabezaX= cabeza->x;
    int cabezaY= cabeza->y;

    //NIVEL 2: los muros periféricos son mortales (colisión con el borde del mapa)
    if(cabezaX<0 || cabezaY<0 || cabezaX>=cols || cabezaY>=rows)
    {
        gameover=true;
        timer->stop();
        retryButton->show();
        return;
    }

    //NIVEL 2: colisión con los muros centrales (la cruz), leídos desde la matriz "mapa"
    if(mapa!=nullptr && mapa[cabezaY][cabezaX]==1)
    {
        gameover=true;
        timer->stop();
        retryButton->show();
        return;
    }
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

void Nivel2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    //NIVEL 2: dibujar los muros +
    painter.setBrush(QColor(120,110,100));
    painter.setPen(QPen(QColor(60,55,50), 2));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(mapa!=nullptr && mapa[i][j]==1)
            {
                painter.drawRect(j*cellsize, i*cellsize, cellsize, cellsize);
            }
        }
    }
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

    //NIVEL 2: dibujar la manzana dorada, si está en pantalla
    if(hayComidaDorada==true)
    {
        painter.setBrush(QColor(255,215,0));
        painter.drawEllipse(comidaDorada.x()*cellsize, comidaDorada.y()*cellsize, cellsize, cellsize);
    }

    //NIVEL 2:  MOSTRAR puntuación y CAnt de manzanas rojas ganadas/ cant total a ganar
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 20, QString("Puntos: %1").arg(puntuacion));
    painter.drawText(10, 40, QString("Manzanas: %1/%2").arg(manzanasComidas).arg(MANZANAS_META));

    if(gameover==true)
    {
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24));
        if(nivelGanado==true)
        {
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }
}

void Nivel2::resetGame()
{
    //integración de nodo prueba #1
    limpiarSerpiente();
    //integración de nodo prueba #1
    cabeza = new Nodo(10, 10);

    direction=Right;
    gameover=false;

    //NIVEL 2: reiniciar todo lo relacionado al nivel 2
    manzanasComidas=0;
    puntuacion=0;
    nivelGanado=false;
    hayComidaDorada=false;
    crecimientoExtra=0; //NIVEL 2
    velocidadBase=VELOCIDAD_INICIAL;
    efectoDoradaActivo=false;
    generacionPartida++; //invalida cualquier efecto temporal de la dorada que estuviera pendiente

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(velocidadBase); //NIVEL 2: se reinicia con la velocidad base
    update();
}

void Nivel2::restaurarVelocidadNormal() //termina el efectoDorada y vuelve a normalizarse la velocidad
{
    efectoDoradaActivo=false;
    timer->setInterval(velocidadBase);
}
