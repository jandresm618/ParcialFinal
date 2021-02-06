#include "objeto_grafico.h"

Objeto_Grafico::Objeto_Grafico()
{

}

Objeto_Grafico::Objeto_Grafico(QString _ruta, int _x, int _y, int _w, int _h)
    :x(_x),y(_y),w(_w),h(_h),ruta(_ruta)
{
    ///ASIGNACION DE VALORES
    this->setPos(_x,_y);
    ///DECLARACION DE OBJETO
    image=new QPixmap(_ruta);
}

QRectF Objeto_Grafico::boundingRect() const
{
    ///RETORNO DE OBJETO
    return QRectF(-(w*escala)/2,-(h*escala)/2,w*escala,h*escala);
    //return QRectF(x,y,w,h);
}

void Objeto_Grafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ///ASIGNACION DE VALORES
    painter->drawPixmap(boundingRect(),*image,image->rect());
}

int Objeto_Grafico::getX()
{
    ///RETORNO DE VALOR
    return x;
}

int Objeto_Grafico::getY()
{
    ///RETORNO DE VALOR
    return y;
}

void Objeto_Grafico::set_Pos(int _x,int _y)
{
    ///ASIGNACION DE VALORES
    x = _x; y = _y;
    this->setPos(_x,_y);
}

QPixmap *Objeto_Grafico::getImage() const
{
    ///RETORNO DE OBJETO
    return image;
}

void Objeto_Grafico::setImage(QPixmap *value)
{
    ///RETORNO DE VALOR
    image = value;
}

QString Objeto_Grafico::getRuta() const
{
    ///RETORNO DE VALOR
    return ruta;
}

int Objeto_Grafico::getW() const
{
    ///RETORNO DE VALOR
    return w;
}

int Objeto_Grafico::getH() const
{
    ///RETORNO DE VALOR
    return h;
}

void Objeto_Grafico::setId(int value)
{
    id = value;
}



