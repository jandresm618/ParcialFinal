#ifndef OBJETO_MOVIL_H
#define OBJETO_MOVIL_H

#include <QObject>
#include <QTimer>
#include <objeto_grafico.h>
#include "movimiento.h"

class Objeto_Movil:public QObject, public Objeto_Grafico
{
    Q_OBJECT
public:
    Objeto_Movil();
    Objeto_Movil(QString _ruta, int _x, int _y, int _xE, float _radio);
    Objeto_Movil(QString _ruta, int _x, int _y, int _w, int _h);
    ~Objeto_Movil();

    //PROPIEDADES DE VISUALIZACION
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool closeness(Objeto_Movil *obj,int howFar);

    void setMovParabolico(int xf,int yf,int param,bool minMax);
    void getMovParabolico(int pos);
    void setVel(float _v0,float _angle);

    bool outScene();
    bool able();

    void calcularParametrosImpactoEstatico(int _xE, int _yE,float factorImpacto);
    void calcularParametrosImpactoDinamico(vector<float> paramsE, float tMensaje, float tFinal);


    void startMove(int msec);
    void stopMove();
    void updatePos();
    void updatePos2();
    void updatePos3();
    void stop();
    void changeSize();


    bool getOutOfScene() const;
    void deleteObject();

    bool getLado();
    void setLado(bool value);

    int getV0() const;

    int getAngle() const;

    int getMove() const;

    float getRadio() const;

    void setCaso(int value);

    int getCaso() const;

private:
    Movimiento *movimiento;

    QTimer *time_move;


    int v0 = 0, angle = 0; //Variables de Movimiento
    float factorImpacto = 0.05; //Porcentaje de Error en el impacto
    bool outOfScene = false;
    bool draw = true;
    int move = 0;
    int cont = 0;
    int t_move = 60;
    float radio = 0;
    int caso = 0;

};

#endif // OBJETO_MOVIL_H
