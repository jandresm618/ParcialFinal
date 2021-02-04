#include "movimiento.h"

Movimiento::Movimiento()
{

}

Movimiento::Movimiento(float x,float y,bool _lado): px(x),py(y),lado(_lado)
{

}

void Movimiento::actualizar(float dt)
{
    ax = 0;  //Aceleracion en Componente x
    ay = G; //Aceleracion en Componente y

    //vx = vx;    //Velocidad en Componente x
    vy = vy - ay*dt;  //Velocidad en Componente y

    x = x + vx*dt; //Posicion x
    y = y + vy*dt-(0.5*ay*dt*dt); //Posicion y
    //cout<<x<<" "<<y<<endl;
}

bool Movimiento::nParabolicos(float xf, float yf, float d, float factorImpacto)
{
    bool impacto = false; //Bandera que indica si hubo impacto o no
    bool aux=false;       //Variable auxiliar
    int v0_,angle,cont=0; //Variables Temporales para cada iterador

    for(v0_=0;;){
        //Iteracion para diferentes valores de Velocidad
        for( angle= 30; angle< 90; angle++){
            //Iteracion para diferentes valores de Angulo
            x = px; y = py; angulo = angle, v0 = v0_; //Inicializacion de Variables para cada valor de angulo y velocidad
            aux = parabolico(xf,yf,v0_,angle,d,factorImpacto); //Retorna true si la parabola es efectiva
            if(aux){
                // Se ejecuta si y solo si hubo impacto
                cout<<endl<<"Impacto numero: "<<cont+1<<endl;
                setParametros(cont);
                imprimirValoresImpacto(); impacto = true; cont++; break;
            }
        }
        //Condicion Relativa De Fin de la Funcion
        if(lado){ //Si la Simulacion es Ofensiva
            v0_+=5;
            if(x >= 2*(xf+(factorImpacto*d))) break; // Si la Posicion Excede la Posicion Enemiga en X
        }
        else{ //Si la Simulacion es Defensiva¨
            v0_-=5;
            if(x < 2*(xf-(factorImpacto*d))) break; // Si la Posicion Excede la Posicion Enemiga en X
        }
    }
    return impacto;
}

bool Movimiento::parabolico(float xf, float yf, int _v0,int _angle,float d, float factorImpacto)
{
    bool impacto = false;
    float dt = 0.1; //Delta de tiempo
    time = 0;       //Se inicializa el tiempo de lanzamiento en cero
    vx = _v0*cos(_angle*pi/180);    //Velocidad inicial de x
    vy = abs(_v0)*sin(_angle*pi/180) - ay*dt; //Velocidad inicial de y
    while((y >= 0) ){   //Mientras el proyectil este sobre la superficie
        actualizar(dt); //Actualizar parametros de movimiento
        if(sqrt(pow((xf - x),2)+pow((yf - y),2)) <= factorImpacto*d){
            impacto=true; break; //Impacto si las posiciones estan en el area de explosion
        }
        time = time + dt;
    }

    return impacto;
}

vector<float> Movimiento::parabolico(float timeStop,float _x, float _y, int _v0, int _angle)
{
    vector<float> pos;
    float dt = 0.1; //Delta de tiempo
    time = 0;       //Se inicializa el tiempo de lanzamiento en cero
    x = _x; y = _y;
    vx = _v0*cos(_angle*pi/180);    //Velocidad inicial de x
    vy = abs(_v0)*sin(_angle*pi/180) - ay*dt; //Velocidad inicial de y
    while((y >= 0) || time >= timeStop ){   //Mientras el proyectil este sobre la superficie
        actualizar(dt); //Actualizar parametros de movimiento
        time = time + dt;
    }
    pos.push_back(x);
    pos.push_back(y);
    return pos;
}



void Movimiento::setParametros(int cont)
{
    parametrosLanzamiento.clear();
    parametrosLanzamiento.push_back(x);
    parametrosLanzamiento.push_back(y);
    parametrosLanzamiento.push_back(time);
    parametrosLanzamiento.push_back(angulo);
    parametrosLanzamiento.push_back(v0);
    lanzamientos.insert(pair<int,vector<float>>(cont,parametrosLanzamiento));
}

map<int, vector<float> > Movimiento::getParametros()
{
    return lanzamientos;
}

void Movimiento::imprimirValoresImpacto()
{
    cout<<"--------------------------"<<endl;
    cout<<"Impacto: "<<endl;
    cout<<"Tiempo: "<<time<<" sg\n";
    cout<<"Angulo: "<<angulo<<"º\n";
    cout<<"Velocidad: "<<v0<<" m/sg\n";
    cout<<"Posicion Final ("<<x<<","<<y<<")\n";
    cout<<"--------------------------"<<endl;
}
