#include "nivel4.h"
#include "ui_gamewindow.h"
#include <QRandomGenerator>
#include <QPainter>

Nivel4::Nivel4(bool murosInfinitos, bool bloquesEstaticos, int cantidadBloques, int skinSeleccionada, QWidget *parent)
    : Nivel(parent),
    murosInfinitos(murosInfinitos),
    bloquesEstaticos(bloquesEstaticos),
    cantidadBloquesConfigurada(cantidadBloques),
    bloques(nullptr),
    cantidadBloquesActual(0),
    hayFrutaBlanca(false),
    blancasGeneradasNivel4(0)
{
    fondo.load(":/imagenes/nivel1_fondo.png");

    cols = ((width() - (2 * marginX)) / cellsize) - 1;
    rows = ((height() - marginY - 120) / cellsize);

    crearMapa();

    if(cantidadBloquesConfigurada>0)
    {
        bloques = new QPoint[cantidadBloquesConfigurada];
    }
    cargarSpritesGusano(skinSeleccionada);
}

Nivel4::~Nivel4()
{
    if(bloques!=nullptr)
    {
        delete[] bloques;
        bloques=nullptr;
    }
}

void Nivel4::generarBloques()
{
    if(mapa!=nullptr)
    {
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                mapa[i][j]=0;
            }
        }
    }

    cantidadBloquesActual=0;

    if(bloques==nullptr)
    {
        return;
    }

    for(int n=0; n<cantidadBloquesConfigurada; n++)
    {
        int x=0;
        int y=0;
        bool posicionValida;
        int intentos=0;

        do
        {
            x= QRandomGenerator::global()->bounded(cols);
            y= QRandomGenerator::global()->bounded(rows);
            posicionValida=true;

            if(x==food.x() && y==food.y())
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

            if(posicionValida==true)
            {
                for(int k=0; k<cantidadBloquesActual; k++)
                {
                    if(bloques[k].x()==x && bloques[k].y()==y)
                    {
                        posicionValida=false;
                        break;
                    }
                }
            }

            intentos++;
        } while(posicionValida==false && intentos<100);

        if(posicionValida==true)
        {
            bloques[cantidadBloquesActual]=QPoint(x,y);
            cantidadBloquesActual++;
        }
    }

    marcarBloquesEnMapa();
}

void Nivel4::marcarBloquesEnMapa()
{
    if(mapa==nullptr || bloques==nullptr)
    {
        return;
    }
    for(int k=0; k<cantidadBloquesActual; k++)
    {
        int x=bloques[k].x();
        int y=bloques[k].y();
        if(x>=0 && x<cols && y>=0 && y<rows)
        {
            mapa[y][x]=1;
        }
    }
}

void Nivel4::intentarFrutaBlanca()
{
    if(blancasGeneradasNivel4>=BLANCAS_MAX_NIVEL4)
    {
        return;
    }
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

        if(mapa!=nullptr && mapa[y][x]==1)
        {
            posicionValida=false;
        }
        if(posicionValida==true && x==food.x() && y==food.y())
        {
            posicionValida=false;
        }
        if(posicionValida==true && hayComidaDorada==true && x==comidaDorada.x() && y==comidaDorada.y())
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
        intentos++;
    } while(posicionValida==false && intentos<100);

    if(posicionValida==true)
    {
        frutaBlanca= QPoint(x,y);
        hayFrutaBlanca=true;
        blancasGeneradasNivel4++;
    }
}

bool Nivel4::ejecutarCicloGeneracion()
{
    bool resultado = Nivel::ejecutarCicloGeneracion();
    intentarFrutaBlanca();

    if(bloquesEstaticos==false)
    {
        generarBloques();
    }

    return resultado;
}

void Nivel4::moveSnake()
{
    if(cabeza==nullptr)
    {
        return;
    }

    int newX= cabeza->x;
    int newY= cabeza->y;

    switch(direction)
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
    case Left:
    {
        newX--;
        break;
    }
    case Right:
    {
        newX++;
        break;
    }
    }
    if(murosInfinitos==true)
    {
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
    }
    else
    {
        if(newX<0 || newY<0 || newX>=cols || newY>=rows)
        {
            gameover=true;
            timer->stop();
            if(sonidoActivado==true)
            {
                sonidoPerdio->stop();
                sonidoPerdio->play();
            }
            retryButton->show();
            btnVolver->setGeometry(330, 490, 150, 50);
            btnVolver->show();
            return;
        }
    }

    if(mapa!=nullptr && mapa[newY][newX]==1)
    {
        gameover=true;
        timer->stop();
        if(sonidoActivado==true)
        {
            sonidoPerdio->stop();
            sonidoPerdio->play();
        }
        retryButton->show();
        btnVolver->setGeometry(330, 490, 150, 50);
        btnVolver->show();
        return;
    }

    Nodo* nuevoNodo= new Nodo(newX, newY);
    nuevoNodo->siguiente=cabeza;
    cabeza= nuevoNodo;

    bool comioAlgo=false;

    if(hayComidaDorada==true && doradaActualComida==false && newX==comidaDorada.x() && newY==comidaDorada.y())
    {
        puntuacion += VALOR_DORADA;
        doradasComidas++;
        doradaActualComida=true;
        hayComidaDorada=false;
        crecimientoExtra += 2;
        comioAlgo=true;
    }

    if(hayFrutaBlanca==true && newX==frutaBlanca.x() && newY==frutaBlanca.y())
    {
        hayFrutaBlanca=false;
        puntuacion += VALOR_ROJA;
        crecimientoExtra += 1;
        comioAlgo=true;
    }

    if(newX==food.x() && newY==food.y() && rojaActualComida==false)
    {
        comioAlgo=true;
        rojasComidas++;
        rojaActualComida=true;
        manzanasComidas= rojasComidas;
        puntuacion += VALOR_ROJA;
        avanzarCicloPorRojaComida();
    }

    if(comioAlgo==true && sonidoActivado==true)
    {
        sonidoComio->stop();
        sonidoComio->play();
    }

    if(comioAlgo==false)
    {
        if(crecimientoExtra>0)
        {
            crecimientoExtra--;
        }
        else if(cabeza->siguiente != nullptr)
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

void Nivel4::spawnFood()
{
    int x=0;
    int y=0;
    bool posicionValida;
    int intentos=0;

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
        intentos++;
    } while(posicionValida==false && intentos<100);

    food= QPoint(x,y);
}

void Nivel4::checkCollision()
{
    if(cabeza==nullptr)
    {
        return;
    }

    int cabezaX= cabeza->x;
    int cabezaY= cabeza->y;

    if(murosInfinitos==false)
    {
        if(cabezaX<0 || cabezaY<0 || cabezaX>=cols || cabezaY>=rows)
        {
            gameover=true;
            timer->stop();
            if(sonidoActivado==true)
            {
                sonidoPerdio->stop();
                sonidoPerdio->play();
            }
            retryButton->show();
            btnVolver->setGeometry(330, 490, 150, 50);
            btnVolver->show();
            return;
        }
    }

    if(mapa!=nullptr && mapa[cabezaY][cabezaX]==1)
    {
        gameover=true;
        timer->stop();
        if(sonidoActivado==true)
        {
            sonidoPerdio->stop();
            sonidoPerdio->play();
        }
        retryButton->show();
        btnVolver->setGeometry(330, 490, 150, 50);
        btnVolver->show();
        return;
    }

    Nodo* actual = cabeza->siguiente;
    while(actual !=nullptr)
    {
        if(cabezaX==actual->x && cabezaY==actual->y)
        {
            gameover=true;
            timer->stop();
            if(sonidoActivado==true)
            {
                sonidoPerdio->stop();
                sonidoPerdio->play();
            }
            retryButton->show();
            btnVolver->setGeometry(330, 490, 150, 50);
            btnVolver->show();
            return;
        }
        actual=actual->siguiente;
    }
}

void Nivel4::resetGame()
{
    limpiarSerpiente();
    crearSerpienteInicial(2,2,Right);

    direction=Right;
    gameover=false;
    puntuacion=0;
    nivelGanado=false;
    crecimientoExtra=0;
    hayFrutaBlanca=false;
    blancasGeneradasNivel4=0;

    btnReaunudar->hide();
    btnVolver->setGeometry(330, 550, 150, 50);
    btnVolver->hide();
    btnSonido->hide();
    btnMusica->hide();
    pausaBtn->show();
    juegoPausado=false;

    generarBloques();
    iniciarSistemaDeManzanas();

    retryButton->hide();
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    timer->start(150);
    update();
}

void Nivel4::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(fondo.isNull()==false)
    {
        painter.drawPixmap(0, 0, width(), height(), fondo);
    }
    else
    {
        painter.fillRect(rect(), Qt::black);
    }

    painter.setBrush(QColor(0, 0, 0, 140));
    painter.setPen(QPen(QColor(120, 110, 100), 2));
    painter.drawRect(marginX, marginY, cols * cellsize, rows * cellsize);

    for(int k=0; k<cantidadBloquesActual; k++)
    {
        int bloqueX = marginX + (bloques[k].x() * cellsize);
        int bloqueY = marginY + (bloques[k].y() * cellsize);
        painter.drawPixmap(bloqueX, bloqueY, cellsize, cellsize, imgBloque);
    }

    dibujarGusano(painter);
    painter.setPen(Qt::NoPen);

    int foodX = marginX + (food.x() * cellsize);
    int foodY = marginY + (food.y() * cellsize);
    painter.drawPixmap(foodX, foodY, cellsize, cellsize, imgManzanaRoja);

    if(hayComidaDorada==true)
    {
        int doradaX = marginX + (comidaDorada.x() * cellsize);
        int doradaY = marginY + (comidaDorada.y() * cellsize);
        painter.drawPixmap(doradaX, doradaY, cellsize, cellsize, imgManzanaDorada);
    }

    if(hayFrutaBlanca==true)
    {
        int blancaX = marginX + (frutaBlanca.x() * cellsize);
        int blancaY = marginY + (frutaBlanca.y() * cellsize);
        painter.drawPixmap(blancaX, blancaY, cellsize, cellsize, imgManzanaBlanca);
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    QRect rectPuntos(185, 24, 140, 36);
    painter.drawText(rectPuntos, Qt::AlignCenter, QString("Puntos: %1").arg(puntuacion));

    QRect rectManzanas(335, 24, 140, 36);
    painter.drawText(rectManzanas, Qt::AlignCenter, QString("Rojas: %1  Doradas: %2").arg(manzanasComidas).arg(doradasComidas));

    QRect rectTiempo(484, 24, 140, 36);
    painter.drawText(rectTiempo, Qt::AlignCenter, QString("Tiempo: %1").arg(formatearTiempo(tiempoRestanteSegundos)));

    if(juegoPausado==true)
    {
        painter.fillRect(rect(), QColor(0,0,0,150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        painter.drawText(QRect(0,330, width(), 60), Qt::AlignCenter, "PARTIDA PAUSADA");
    }

    if(gameover==true)
    {
        painter.fillRect(rect(), QColor(0,0,0,150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Trebuchet MS", 24, QFont::Bold));
        if(nivelGanado==true)
        {
            painter.drawText(QRect(0, height()/2-40, width(), 50), Qt::AlignHCenter, "¡NIVEL COMPLETADO!");
        }
        else
        {
            painter.drawText(QRect(0, height()/2-40, width(), 50), Qt::AlignHCenter, "¡GAME OVER!");
        }
        painter.setFont(QFont("Trebuchet MS", 14, QFont::Bold));
        painter.drawText(QRect(0, height()/2+15, width(), 30), Qt::AlignCenter, QString("Puntaje: %1").arg(puntuacion));
    }
}