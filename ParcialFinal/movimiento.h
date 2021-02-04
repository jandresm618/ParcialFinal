#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include <iostream>
#include <math.h>
#include <vector>
#include <map>

#define G 9.81
#define pi 3.141617

using namespace std;

class Movimiento
{
public:
    Movimiento();
    Movimiento(float x,float y,bool _lado);
    void actualizar(float dt);
    bool nParabolicos(float xf,float yf, float d, float factorImpacto);
    bool parabolico(float xf,float yf,int _v0,int _angle,float d, float factorImpacto);
    vector<float> parabolico(float timeStop,float x, float y,int _v0,int _angle);

    float tiempoParabolico(float xf,float yf,float _angle,float _v0,float d, float factorImpacto);
    void setParametros(int cont);
    map<int,vector<float>> getParametros();
    void imprimirValoresImpacto();

private:
    bool lado; //Indicador de bando
                //false = Defensivo
                //true = Ofensivo
    float x = 0,y = 0;
    float px= 0,py= 0;
    float vx= 0,vy= 0;
    float ax= 0,ay= 0;
    float v0= 0;
    float v0x= 0,v0y= 0;
    float angulo= 0;
    float time= 0;
    float aux_v= 0,aux_sin= 0;
    vector<float> parametrosLanzamiento;
    map<int,vector<float>> lanzamientos;

};

#endif // MOVIMIENTO_H
