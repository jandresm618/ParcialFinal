#include "objeto_movil.h"

Objeto_Movil::Objeto_Movil()
{

}

Objeto_Movil::Objeto_Movil(QString _ruta, int _x, int _y, int _xE, float _radio)
    : Objeto_Grafico(_ruta,_x,_y,_radio,_radio)
{
    ///DECLARACION DE OBJETOS
    movimiento = new Movimiento(_x,_y);
    time_move = new QTimer;
    radio = _radio;
    if(_x<= _xE) setLado(true); ///IZQUIERDA A DERECHA
    else setLado(false); ///DERECHA A IZQUIERDA

    connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos);
}

Objeto_Movil::Objeto_Movil(QString _ruta, int _x, int _y, int _w, int _h): Objeto_Grafico(_ruta,_x,_y,_w,_h)
{
    movimiento = new Movimiento(_x,_y);
    time_move = new QTimer;
    connect(time_move,&QTimer::timeout,this,&Objeto_Movil::updatePos);
    time_move->start(t_move);
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
    //int d = sqrt(pow(xf-this->getX(),2)+pow(yf-this->getY(),2)); //Distancia entre Objetos                              //Porcentaje de Impacto

    ///ASIGNACION DE VALORES
    //movimiento->nParabolicosEstatico(xf,yf,d,factorImpacto);    //Se calculan las velocidades de lanzamiento
    params = movimiento->getParametros().at(0);
    angle = params.at(3);
    v0 = params.at(4);
    movimiento->calcularVelocidades(v0,angle);

    ///ASIGNACION DE VALORES
    //params = movimiento->getBest(param,minMax);         //Parametros para lanzamiento con altura minima
    //movimiento->setParamsMove(v0,angle);
    //qDebug()<<"parametros seteados";
}

void Objeto_Movil::getMovParabolico(int pos)
{
    //DECLARACION DE VARIABLES AUXILIARES LOCALES
        vector<float> params;                                //Vector de Parametros de Lanzamiento

        params = movimiento->getParametros().at(pos);
        angle = params.at(3);
        v0 = params.at(4);
        movimiento->calcularVelocidades(v0,angle);
}

void Objeto_Movil::setVel(float _v0, float _angle)
{
    movimiento->setLanzamiento(_v0,_angle);
}

bool Objeto_Movil::outScene()
{
    if(movimiento->getX()>1400 || movimiento->getX()<-radio
       || movimiento->getY() > 1000 ||  movimiento->getY() < -radio){
        return true;
    }
    else return false;
}

bool Objeto_Movil::able()
{
    if(cont % 10 == 0) return true;
    else return false;
}

void Objeto_Movil::calcularParametrosImpactoEstatico(int _xE, int _yE, float factorImpacto)
{
    movimiento->nParabolicosEstatico(_xE,_yE,abs(movimiento->getX()-_xE),factorImpacto);
}

void Objeto_Movil::calcularParametrosImpactoDinamico(vector<float> paramsE,float tMensaje,float tFinal)
{
    movimiento->nParabolicosDinamico(paramsE,tMensaje,tFinal);
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
    cont++;
    ///ACTUALIZA VALORES DE MOVIMIENTO
    movimiento->actualizar2();
    ///ASIGNACION DE VALORES
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

void Objeto_Movil::setLado(bool value)
{
    movimiento->setLado(value);
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

float Objeto_Movil::getRadio() const
{
    return radio;
}

void Objeto_Movil::setCaso(int value)
{
    caso = value;
}

int Objeto_Movil::getCaso() const
{
    return caso;
}

