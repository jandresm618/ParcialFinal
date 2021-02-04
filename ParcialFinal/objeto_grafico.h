#ifndef OBJETO_GRAFICO_H
#define OBJETO_GRAFICO_H

#include <QGraphicsItem>
#include <QPainter>
#include <vector>

class Objeto_Grafico: public QGraphicsItem
{
public:
    Objeto_Grafico();
    Objeto_Grafico(QString _ruta,int _x,int _y,int _w,int _h);

    //PROPIEDADES DE VISUALIZACION
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);    

    int getX();
    int getY();
    void set_Pos(int _x,int _y);

    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    QString getRuta() const;

    int getW() const;

    int getH() const;

private:
    int x,y;
    int w,h;
    QString ruta;
    QPixmap *image;
};

#endif // OBJETO_GRAFICO_H
