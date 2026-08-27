#include "nivel3.h"
#include "ui_gamewindow.h"

Nivel3::Nivel3(QWidget *parent)
    : Nivel(parent)
    , hayFrutaVelocidad(false)
    , velocidadBase(VELOCIDAD_INICIAL)
    , efectoDoradaActivo(false)
    , generacionPartida(0)
    , desplazamientoBloques(0)
    , direccionBloques(1)  //1 se aleja del centro y -1 se acerca al centro
    , contadorMovimientoBloques(0)
{
    ui= new Ui::GameWindow();
    ui->setupUi(this);

    setFixedSize(600,600);
    setFocusPolicy(Qt::StrongFocus);

    cellsize=20;
    rows=height()/cellsize;
    cols=width()/cellsize;
    crearMapa();
    inicializarBloquesMovibles(); //se agrega la cruz de muros en el mapa

    cabeza= new Nodo(10, 10);

    direction=Right;
    gameover=false;

    spawnFood();
    timer= new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Nivel3::gameloop);

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
    connect(retryButton, &QPushButton::clicked, this, &Nivel3::resetGame);
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
}

void Nivel3::aumentarVelocidad()
{
    if(velocidadBase > VELOCIDAD_MINIMA)
    {
        velocidadBase -= 10;

        if(efectoDoradaActivo==false)
        {
            timer->setInterval(velocidadBase);
        }
    }
}

void Nivel3::activarReduccionVelocidad()
{
    efectoDoradaActivo=true;
    timer->setInterval(velocidadBase + 80); //el juego se vuelve más lento temporalmente

    int generacionActual = generacionPartida;
    QTimer::singleShot(5000, this, [this, generacionActual]()
                       {
                           if(generacionActual == generacionPartida)
                           {
                               restaurarVelocidadNormal();
                           }
                       });
}

void Nivel3::intentoFrutaVelocidad()
{
    int probabilidad = QRandomGenerator::global()->bounded(100);
    if(probabilidad >= 30)
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
        if(puntoEnBloqueMovil(x,y))
        {
            posicionValida=false;
        }

        //no debe salir en la misma celda que la manzana roja
        if(posicionValida==true && hayComidaDorada==true && x==food.x() && y==food.y())
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
    } while(posicionValida==false && intentos<100); //límite de intentos por seguridad

    if(posicionValida==true)
    {
        frutaVelocidad= QPoint(x,y);
        hayFrutaVelocidad=true;
        frutaVelocidadBlanca=(QRandomGenerator::global()->bounded(100)<50);
    }
}

void Nivel3::inicializarBloquesMovibles()
{
    centroFilaBloques=rows/2;
    centroColumnaBloques=cols/2;
    grosorBoqueMovil=2;
    altoBloqueMovil=8;
    maxDesplazamientoBloques=centroFilaBloques-altoBloqueMovil-1;
    if(maxDesplazamientoBloques<0)
    {
        maxDesplazamientoBloques=0;
    }
    desplazamientoBloques=0;
    direccionBloques=1;
    contadorMovimientoBloques=0;
}

void Nivel3::actualizarBloquesMovibles()
{
    contadorMovimientoBloques++;
    if(contadorMovimientoBloques<INTERVALO_MOVIMIENTO_BLOQUES)
    {
        return;
    }
    contadorMovimientoBloques=0;
    desplazamientoBloques+=direccionBloques;
    if(desplazamientoBloques>=maxDesplazamientoBloques)
    {
        desplazamientoBloques= maxDesplazamientoBloques;
        direccionBloques=-1;
    }
    else if (desplazamientoBloques<=0)
    {
        desplazamientoBloques=0;
        direccionBloques=1;
    }
}

bool Nivel3::puntoEnBloqueMovil(int x, int y) const
{
    int columnaIzq= centroColumnaBloques-grosorBoqueMovil;
    int columnaDer= centroColumnaBloques+grosorBoqueMovil;

    if(x<columnaIzq || x>columnaDer)
    {
        return false;
    }
    int filaInfSup=centroFilaBloques-1-desplazamientoBloques;//bloque superior: su borde inferior toca el centro y se aleja hacia arriba
    int filaSupInf=filaInfSup-(altoBloqueMovil-1);
    if (y>=filaSupInf && y<=filaInfSup)
    {
        return true;
    }

    int filaSupInferior=centroFilaBloques+desplazamientoBloques;//bloque superior: su borde inferior toca el centro y se aleja hacia arriba
    int filaInfInferior=filaSupInferior+(altoBloqueMovil-1);
    if (y>=filaSupInferior && y<=filaInfInferior)
    {
        return true;
    }
    return false;
}

void Nivel3::moveSnake()
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

    //integración de nodo prueba #1

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;

    //NIVEL 2: bandera para saber si la serpiente comió algo en este movimiento (roja o dorada)
    bool comioAlgo=false;
    //NIVEL 2: primero se revisa la manzana dorada (si está presente)
    if(hayComidaDorada && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += 30; //NIVEL 2: puntos triples (10 x 3)
        hayComidaDorada=false; //la dorada desaparece al comerla
        activarReduccionVelocidad(); //NIVEL 2: efecto temporal de velocidad reducida
        crecimientoExtra += 2; //NIVEL 2: este movimiento ya crece 1 (no se borra la cola); +2 para sumar 3 en total
        comioAlgo=true;
    }

    //nivel 3 fruta especial ver si acelera o disminuye
    if(hayFrutaVelocidad==true && newX==frutaVelocidad.x() && newY==frutaVelocidad.y())
    {
        hayFrutaVelocidad=false;
        if(frutaVelocidadBlanca==true)
        {
            if((velocidadBase-CAMBIO_VELOCIDAD_FRUTA)>=VELOCIDAD_MINIMA)
            {
                velocidadBase-= CAMBIO_VELOCIDAD_FRUTA; //aumenta la velocidad
            }
        }
        else
        {
            if((velocidadBase + CAMBIO_VELOCIDAD_FRUTA)<=VELOCIDAD_MAXIMA)
            {
                velocidadBase +=CAMBIO_VELOCIDAD_FRUTA; //disminuye la velocidad
            }
        }

        if(efectoDoradaActivo==false)
        {
            timer->setInterval(velocidadBase);
        }
    }
    //nivel 2
    if(newX==food.x() && newY==food.y())
    {
        comioAlgo=true;
        manzanasComidas++; //NIVEL 2
        puntuacion += 10;
        //nivel 3 crece el doble
        crecimientoExtra+=1;

        //NIVEL 2: si se come la roja, la dorada (si estaba en pantalla) desaparece también
        hayComidaDorada=false;

        //nivel 3 fruta especial se reinicia con cada fruta roja comida
        hayFrutaVelocidad=false;

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
            //NIVEL 2: cada 2 manzanas rojas comidas, aumenta la velocidad
            if(manzanasComidas % 2 == 0)
            {
                aumentarVelocidad();
            }

            spawnFood();
            intentoComidaDorada(); //NIVEL 2: fruta dorada
            intentoFrutaVelocidad(); //nivel 3 fruta especial
        }
    }

    if(!comioAlgo)
    {
        //NIVEL 2: si queda crecimiento pendiente (de una dorada comida antes), la cola NO se recorta y ese crecimiento pendiente se va consumiendo un nodo por movimiento.
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

void Nivel3::spawnFood()
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

        if(puntoEnBloqueMovil(x, y) ==true)
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

    } while(!posicionValida);

    food= QPoint(x,y);
}

void Nivel3::checkCollision()
{
    //integración de nodo prueba #1
    if(cabeza==nullptr)
    {
        return;
    }

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
    if(puntoEnBloqueMovil(cabezaX, cabezaY)==true)
    {
        gameover=true;
        timer->stop();
        retryButton->show();
        return;
    }

    //nivel 3 colision nodo del gusano con bloque
    Nodo* nodoCuerpo = cabeza->siguiente;
    while(nodoCuerpo !=nullptr)
    {
        if(puntoEnBloqueMovil(nodoCuerpo->x, nodoCuerpo->y))
        {
            gameover=true;
            timer->stop();
            retryButton->show();
            return;
        }
        nodoCuerpo=nodoCuerpo->siguiente;
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

void Nivel3::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    //NIVEL 3: dibujar los bloques movibles
    painter.setBrush(QColor(120,110,100));
    painter.setPen(QPen(QColor(60,55,50), 2));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(puntoEnBloqueMovil(j,i))
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

    //nivel 3: frutas especial
    if(hayFrutaVelocidad==true)
    {
        painter.setPen(Qt::NoPen);
        int frutax=frutaVelocidad.x()*cellsize;
        int frutay=frutaVelocidad.y()*cellsize;
        if(frutaVelocidadBlanca==true)
        {
            painter.setBrush(Qt::white);
            painter.drawEllipse(frutax, frutay, cellsize, cellsize);
        }
        else
        {
            painter.setBrush(QColor(150,120,80));
            painter.drawEllipse(frutax, frutay, cellsize, cellsize);
            painter.setBrush(QColor(85,65,40));
            painter.drawEllipse(frutax+3, frutay+3, cellsize, cellsize);
            painter.drawEllipse(frutax+cellsize-9, frutay+cellsize-8, 4, 4);


        }
    }
    //NIVEL 2: HUD con puntuación y progreso de manzanas rojas
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
            //NIVEL 2: mensaje de victoria al completar las 6 manzanas rojas
            painter.drawText(rect(), Qt::AlignCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        }
    }
}

void Nivel3::gameloop()
{
    if(gameover==true)
    {
        return;
    }
    //nivel 3 bloques movibles
    actualizarBloquesMovibles();

    moveSnake();
    checkCollision();
    update();
}

void Nivel3::resetGame()
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

    //nivel 3 frutas especiales
    hayFrutaVelocidad=false;
    frutaVelocidadBlanca=true;
    //nivel 3 reinicia bloques movibles
    inicializarBloquesMovibles();

    spawnFood();
    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(velocidadBase); //NIVEL 2: se reinicia con la velocidad base
    update();
}

void Nivel3::restaurarVelocidadNormal()
{
    efectoDoradaActivo=false;
    timer->setInterval(velocidadBase);
}