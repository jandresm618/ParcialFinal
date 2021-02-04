#include "objeto_movil.h"

Objeto_Movil::Objeto_Movil()
{

}

Objeto_Movil::Objeto_Movil(QString _ruta, int _x, int _y, int _xE, int _yE, int _w, int _h, bool _lado)
    : Objeto_Grafico(_ruta,_x,_y,_w,_h)
{
    ///DECLARACION DE OBJETOS
    movimiento = new Movimiento(_x,_y,_lado);
    time_move = new QTimer;

    ///CONEXION DE SIGNAL & SLOT
    switch (_lado) {
    case 1:
            ///Movimiento Parabolico
        connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos);
        break;
    case 2:
            ///Movimiento Senoidal
        connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos2);
        break;
    case 3:
            ///Movimiento Rectilineo Acelerado
        connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos3);
        break;
    default:
            ///Movimiento Parabolico
        connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos);
        break;
    }



}

Objeto_Movil::Objeto_Movil(QString _ruta, int _x, int _y, int _w, int _h): Objeto_Grafico(_ruta,_x,_y,_w,_h)
{
    movimiento = new Movimiento;
    time_move = new QTimer;
    connect(time_move,&QTimer::timeout,this,&Objeto_Movil::changeSize);
    time_move->start(250);
}

Objeto_Movil::~Objeto_Movil()
{
    ///ELIMINACION DE MEMORIA
    //qDebug()<<"Destruyendo elementos de Objetos";
    delete movimiento;
    delete time_move;
    delete this->parent();
}

QRectF Objeto_Movil::boundingRect() const
{
    ///RETORNO DE OBJETO
    return QRectF(0,0,this->getW(),this->getH());
}

void Objeto_Movil::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ///ASIGNACION DE VALORES
    painter->drawPixmap(boundingRect(),*(this->getImage()),this->getImage()->rect());
}

bool Objeto_Movil::closeness(Objeto_Movil *obj,int howFar)
{
    bool close = false;
    int d = sqrt(sqrt(pow(obj->getX()-this->getX(),2)+pow(obj->getY()-this->getY(),2))); //Distancia entre Objetos)
    if(d <= howFar) close = true;
    return close;
}

void Objeto_Movil::setMovParabolico(int xf, int yf,int param,bool minMax)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    vector<float> params;                                //Vector de Parametros de Lanzamiento
    int d = sqrt(pow(xf-this->getX(),2)+pow(yf-this->getY(),2)); //Distancia entre Objetos                              //Porcentaje de Impacto

    //qDebug()<<"Distancia calculada";
    ///ASIGNACION DE VALORES
    movimiento->nParabolicos(xf,yf,d,factorImpacto);    //Se calculan las velocidades de lanzamiento
    //movimiento->imprimirVector(movimiento->getLanzamientos());
    //qDebug()<<"Calculados n parabolicos";
    ///DEBUG
    //qDebug()<<"GEtting Best...";

    ///ASIGNACION DE VALORES
    params = movimiento->getBest(param,minMax);         //Parametros para lanzamiento con altura minima
    //qDebug()<<"Se eligio el mejor";
    angle = params.at(3);
    v0 = params.at(4);
    movimiento->setParamsMove(v0,angle);
    //qDebug()<<"parametros seteados";
}

void Objeto_Movil::setVel(float _v0, float _angle)
{
    ///ASIGNACION DE VALORES
    angle = _angle;
    v0 = _v0;
    movimiento->setParamsMove(v0,angle);
}

void Objeto_Movil::setMovSenoidal()
{
    movimiento->setMovSeno();
}

void Objeto_Movil::startMove(int msec)
{
    ///ASIGNACION DE VALORES
    time_move->start(msec);
}

void Objeto_Movil::stopMove()
{
    ///ASIGNACION DE VALORES
    time_move->stop();
}

void Objeto_Movil::updatePos()
{
    ///ACTUALIZA VALORES DE MOVIMIENTO
    movimiento->actualizar();
    ///ASIGNACION DE VALORES
    this->set_Pos(movimiento->getX(),movimiento->getY());
}

void Objeto_Movil::updatePos2()
{
    if(movimiento->actualizarSeno()){outOfScene = true;}
    this->set_Pos(movimiento->getX(),movimiento->getY());
}

void Objeto_Movil::updatePos3()
{
    if(movimiento->actualizarMUA()){outOfScene = true;}
    this->set_Pos(movimiento->getX(),movimiento->getY());
}

void Objeto_Movil::stop()
{
    time_move->stop();
}

void Objeto_Movil::changeSize()
{
    switch (cont) {
    case 1:
        this->parentItem()->setScale(1.2);
        break;
    case 2:
        this->parentItem()->setScale(1.4);
        break;
    case 3:
        this->parentItem()->setScale(1.6);
        break;
    case 4:
        this->parentItem()->setScale(0.8);
        break;
    case 5:
        this->parentItem()->setScale(0.5);
        break;
    case 6:
        delete this;
        break;
    default:
        qDebug()<<"Algo anda mal";
        break;
    }
    cont++;
}

bool Objeto_Movil::getOutOfScene() const
{
    return outOfScene;
}

void Objeto_Movil::deleteObject()
{
    //time_move->stop();
    //qDebug()<<"Eliminando Objeto at .... No se";
    delete this;
}

bool Objeto_Movil::getLado()
{
    return movimiento->getLado();
}

int Objeto_Movil::getV0() const
{
    return v0;
}

int Objeto_Movil::getAngle() const
{
    return angle;
}

int Objeto_Movil::getMove() const
{
    return move;
}

