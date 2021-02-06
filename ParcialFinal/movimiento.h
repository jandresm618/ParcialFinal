#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <QPoint>
#include <QDebug>

#define G 9.81
#define pi 3.141617
#define DT 0.1

using namespace std;

class Movimiento
{
public:
    Movimiento();
    Movimiento(float _x, float _y);

    void actualizar(float dt);
    void actualizar();
    QPoint actualizar(QPoint pE,QPoint velE,QPoint acelE);
    QPoint actualizar(QPoint pE, float vx, float vy, float ay);
    vector<float> actualizar(vector<float> params);
    void actualizar2();        

        /// FUNCION DE SELECCION DE MOVIMIENTOS HACIA OBJETIVO ESTATICO
    bool nParabolicosEstatico(float xf,float yf, float d, float factorImpacto);

        /// FUNCION DE DETECCION DE CHOQUE HACIA OBJETIVO ESTATICO
    bool parabolico(float xf,float yf,int _v0,int _angle,float d, float factorImpacto);

        /// FUNCION QUE DEVUELVE POSICION DE UN OBJETO EN DETERMINADO TIEMPO
    QPoint detectPosicion(float timeStop, float _x, float _y, int _v0, int _angle);

        /// FUNCION DE DETECCION DE CHOQUE HACIA OBJETIVO DINAMICO
    short int dobleParabolico(vector<float> paramsE, vector<float> paramsP, float tMensaje, float tFinal);

        /// FUNCION DE SELECCION DE MOVIMIENTOS HACIA OBJETIVO DINAMICO
    bool nParabolicosDinamico(vector<float> paramsE, float tMensaje, float tFinal);

    void calcularMovimientoEnemigo(int _xE,int _yE,int _v0,int _angle, int t_);
    float tiempoParabolico(float xf,float yf,float _angle,float _v0,float d, float factorImpacto);


    void setParametros(int cont);
    void setParametros(int cont,vector<float> paramsP);
    map<int,vector<float>> getParametros();
    void imprimirValoresImpacto();

    void setLanzamiento(int _v0,int _angle);
    void calcularVelocidades(int _v0,int _angle);

    short int choque(Movimiento *enemigo,float dAnterior);
    short int choque(vector<float > objeto1 ,vector<float > objeto ,float dAnterior);
    float distanciaEntreObjetos(Movimiento *enemigo);
    float distanciaEntreObjetos(vector<float> objeto1, vector<float> objeto);

    float getX() const;

    float getY() const;

    bool getLado() const;

    float getRadio() const;
    void setRadio(float value);

    float getFactorImpacto() const;
    void setFactorImpacto(float value);

    void setLado(bool value);

    map<int, vector<float> > getLanzamientos() const;

private:
    bool lado;  //Indicador de bando
    //false = Defensivo
                    //true = Ofensivo
    float x = 0,y = 0;
    float px= 0,py= 0;
    float vx= 0,vy= 0;
    float ax= 0,ay= 0;
    float radio = 0;
    float factorImpacto = 0;
    float v0= 0;
    float v2x= 0,v2y= 0;
    float angulo= 0;
    float time= 0;
    float aux_v= 0,aux_sin= 0;
    vector<float> parametrosLanzamiento;
    map<int,vector<float>> lanzamientos;

};

#endif // MOVIMIENTO_H
