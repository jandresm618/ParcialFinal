#include "movimiento.h"

Movimiento::Movimiento()
{

}

Movimiento::Movimiento(float _x,float _y)
    : px(_x),py(_y)
{
    x = _x; y = _y;


}

void Movimiento::actualizar(float dt)
{
    ax = 0;  //Aceleracion en Componente x
    ay = G; //Aceleracion en Componente y

    //vx = vx;    //Velocidad en Componente x
    vy = vy - ay*dt;  //Velocidad en Componente y
    //qDebug()<<"vx: "<<vx<<" vy: "<<vy;


    //qDebug()<<"x: "<<x<<" y: "<<y;
    x = x + vx*dt; //Posicion x
    y = y + vy*dt-(0.5*ay*dt*dt); //Posicion y
}

void Movimiento::actualizar()
{
    ax = 0;  //Aceleracion en Componente x
    ay = G; //Aceleracion en Componente y

    //vx = vx;    //Velocidad en Componente x
    vy = vy - ay*DT;  //Velocidad en Componente y

    x = x + vx*DT; //Posicion x
    y = y + vy*DT-(0.5*ay*DT*DT); //Posicion y

}

QPoint Movimiento::actualizar(QPoint pE, QPoint velE, QPoint acelE)
{
    ax = acelE.x();  //Aceleracion en Componente x
    ay = acelE.y(); //Aceleracion en Componente y

    vx = velE.x();    //Velocidad en Componente x
    vy = velE.y() - ay*DT;  //Velocidad en Componente y

    pE.setX(pE.x() + vx*DT); //Posicion x
    pE.setY(pE.y() + vy*DT-(0.5*ay*DT*DT)); //Posicion y

    return pE;
}

QPoint Movimiento::actualizar(QPoint pE, float vx, float vy, float ay)
{
    vy = vy - ay*DT;  //Velocidad en Componente y

    pE.setX(pE.x() + vx*DT); //Posicion x
    pE.setY(pE.y() + vy*DT-(0.5*ay*DT*DT)); //Posicion y

    return pE;
}

vector<float> Movimiento::actualizar(vector<float> params)
{
    float p_x,p_y,v_x,v_y,a_x,a_y;
    p_x = params[0]; p_y = params[1];
    v_x = params[2]; v_y = params[3];
    a_x = params[4]; a_y = params[5];

    params[3] = v_y - a_y*DT;

    params[0] =  p_x + v_x*DT; //Posicion x
    params[1] = p_y + v_y*DT-(0.5*a_y*DT*DT); //Posicion y

    return params;
}

void Movimiento::actualizar2()
{
    ax = 0;  //Aceleracion en Componente x
    ay = -G; //Aceleracion en Componente y

    //vx = vx;    //Velocidad en Componente x
    v2y = v2y - ay*DT;  //Velocidad en Componente y

    x = x + v2x*DT; //Posicion x
    y = y + v2y*DT-(0.5*ay*DT*DT); //Posicion y
}

bool Movimiento::nParabolicosEstatico(float xf, float yf, float d, float factorImpacto)
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
                qDebug()<<"Impacto numero: "<<cont+1;
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

QPoint Movimiento::detectPosicion(float timeStop, float _x, float _y, int _v0, int _angle)
{
    QPoint pos;
    float dt = 0.1; //Delta de tiempo
    time = 0;       //Se inicializa el tiempo de lanzamiento en cero
    x = _x; y = _y;
    vx = _v0*cos(_angle*pi/180);    //Velocidad inicial de x
    vy = abs(_v0)*sin(_angle*pi/180) - ay*dt; //Velocidad inicial de y
    while(time >= timeStop ){   //Mientras el proyectil este sobre la superficie
        actualizar(dt); //Actualizar parametros de movimiento
        time = time + dt;
    }
    pos.setX(x);
    pos.setY(y);
    return pos;
}

short Movimiento::dobleParabolico(vector<float> paramsE, vector<float> paramsP, float tMensaje, float tFinal)
{
    short int caso = 0;
    float t = 0;
    QPoint auxE;
    float dA = distanciaEntreObjetos(paramsE,paramsP);
    float v0E = paramsE.at(2),angleE = paramsE.at(3);
    float v0P = paramsP.at(2),angleP = paramsP.at(3);
    /// DEFINICION DE POSICIONES INICIALES
    auxE = detectPosicion(tMensaje,paramsE.at(0),paramsE.at(1),paramsE.at(2),paramsE.at(3));

    /// DEFINICION DE VELOCIDADES INICIALES
    paramsE.at(2) = v0E*cos(angleE*pi/180);    //Velocidad inicial de x
    paramsE.at(3) = abs(v0E)*sin(angleE*pi/180) - paramsE.at(5)*DT; //Velocidad inicial de y

    paramsP.at(2) = v0P*cos(angleP*pi/180);    //Velocidad inicial de x
    paramsP.at(3) = abs(v0P)*sin(angleP*pi/180) - paramsE.at(5)*DT; //Velocidad inicial de y

    while(t<tFinal){
        paramsE = actualizar(paramsE);
        paramsP = actualizar(paramsP);

        caso = choque(paramsE,paramsP,dA);
        if(caso != 0) return caso;
        dA = distanciaEntreObjetos(paramsE,paramsP);
        t++;
    }
    return caso;

}

bool Movimiento::nParabolicosDinamico(vector<float> paramsE, float tMensaje,float tFinal)
{
    short int caso = 0;
    bool impacto = false;   //Bandera que indica si hubo impacto o no
    int v0_,angle,cont=0;   //Variables Temporales para cada iterador
    lanzamientos.clear();
    vector<float> paramsP;
    paramsP.at(0) = px;
    paramsP.at(1) = py;
    paramsP.at(2) = 0;
    paramsP.at(3) = 0;
    paramsP.at(4) = 0;
    paramsP.at(5) = G;
    paramsP.at(6) = radio;

    for(v0_=0;;){
        //Iteracion para diferentes valores de Velocidad
        for( angle= 20; angle< 90; angle++){
            paramsP.at(3) = v0_;
            paramsP.at(4) = angle;
            caso = dobleParabolico(paramsE,paramsP,tMensaje,tFinal);
            if(caso != 0) break;
        }
        //Condicion Relativa De Fin de la Funcion
        if(lado){ //Si la Simulacion es Ofensiva
            v0_+=5;
            if(caso == 1 || caso == 2) {
                impacto = true; setParametros(cont,paramsP); cont++;}
        }
        else{ //Si la Simulacion es Defensiva¨
            v0_-=5;
            if(caso == 1 || caso == 2) {
                impacto = true; setParametros(cont,paramsP); cont++;}
        }
    }
    return impacto;
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



void Movimiento::setParametros(int cont, vector<float> paramsP)
{
    parametrosLanzamiento.clear();
    parametrosLanzamiento.push_back(paramsP.at(2));
    parametrosLanzamiento.push_back(paramsP.at(3));
    lanzamientos.insert(pair<int,vector<float>>(cont,parametrosLanzamiento));
}

map<int, vector<float> > Movimiento::getParametros()
{
    return lanzamientos;
}

void Movimiento::imprimirValoresImpacto()
{
    qDebug()<<"--------------------------";
    qDebug()<<"Impacto: ";
    qDebug()<<"Tiempo: "<<time<<" sg\n";
    qDebug()<<"Angulo: "<<angulo<<"º\n";
    qDebug()<<"Velocidad: "<<v0<<" m/sg\n";
    qDebug()<<"Posicion Final ("<<x<<","<<y<<")\n";
    qDebug()<<"--------------------------";
}

void Movimiento::setLanzamiento(int _v0, int _angle)
{
    v0 = _v0;
    angulo = _angle;
    calcularVelocidades(_v0,_angle);
    actualizar2();
}

void Movimiento::calcularVelocidades(int _v0, int _angle)
{
    vx = _v0*cos(_angle*pi/180);    //Velocidad inicial de x
    vy = abs(_v0)*sin(_angle*pi/180) - ay*DT; //Velocidad inicial de y
    v2y = -1*vy;                //Velocidad en Y con eje invertido
    v2x = vx;                   //Velocidad en X con eje invertido
    x = px;
    y = py;
    qDebug()<<"vx: "<<vx<<" vy: "<<vy;
}

short Movimiento::choque(Movimiento *enemigo, float dAnterior)
{
    short int choque = 0; //0-> NO CHOCAN,
                          // 1-> Destruyo a enemigo
                          // 2-> Enemigo me destruye
                          // 3-> No estaremos ni cerca
    float d = distanciaEntreObjetos(enemigo);
    if(d > dAnterior) {qDebug()<<"Se estan alejando"; choque = 3;}
    else{
        if(d <= getRadio()){qDebug()<<"Impacta al enemigo,"; choque = 1;}
        else if(d <= enemigo->getRadio()) {qDebug()<<"El enemigo impacta conmigo";choque = 2;}
    }

    return choque;
}

short Movimiento::choque(vector<float> objeto1, vector<float> objeto, float dAnterior)
{
    short int choque = 0; //0-> NO CHOCAN,
                          // 1-> Destruyo a enemigo
                          // 2-> Enemigo me destruye
                          // 3-> No estaremos ni cerca
    float d = distanciaEntreObjetos(objeto1,objeto);
    if(d > dAnterior) {qDebug()<<"Se estan alejando"; choque = 3;}
    else{
        if(d <= objeto.at(6)){qDebug()<<"Impacta al enemigo,"; choque = 1;}
        else if(d <= objeto1.at(6)) {qDebug()<<"El enemigo impacta conmigo";choque = 2;}
    }

    return choque;
}

float Movimiento::distanciaEntreObjetos(Movimiento *enemigo)
{
    float d = sqrt(pow(this->x-enemigo->getX(),2) + pow(this->y-enemigo->getY(),2));
    return d;
}

float Movimiento::distanciaEntreObjetos(vector<float> objeto1,vector<float> objeto)
{
    float d = sqrt(pow(objeto1.at(0)-objeto.at(0),2) + pow(objeto1.at(1)-objeto.at(0),2));
    return d;
}

float Movimiento::getX() const
{
    return x;
}

float Movimiento::getY() const
{
    return y;
}

bool Movimiento::getLado() const
{
    return lado;
}

float Movimiento::getRadio() const
{
    return radio;
}

void Movimiento::setRadio(float value)
{
    radio = value;
}

float Movimiento::getFactorImpacto() const
{
    return factorImpacto;
}

void Movimiento::setFactorImpacto(float value)
{
    factorImpacto = value;
}

void Movimiento::setLado(bool value)
{
    lado = value;
}

map<int, vector<float> > Movimiento::getLanzamientos() const
{
    return lanzamientos;
}


