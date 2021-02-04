#include "escena_guerra.h"

///         CONSTRUCTOR         ///
Escena_Guerra::Escena_Guerra()
{
    //image = new QPixmap(":/personajes/imagenes/Fondo_Original1.png");
    //image = new QPixmap(":/personajes/imagenes/fondo.png");

}
///         DESTRUCTOR         ///
Escena_Guerra::~Escena_Guerra()
{
    ///ELIMINACION DE MEMORIA
    delete proyectil;
    delete canon;
}
///         PROPIEDADES DE VENTANA         ///
void Escena_Guerra::setWindowProperty(int desk_w, int desk_h)
{
    limit_x = desk_w;
    limit_y = desk_h;
    setSceneRect(0,0,desk_w,desk_h);
}

void Escena_Guerra::drawBackground(QPainter *painter, const QRectF &exposed)
{

    painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image,image->rect());
}

///         AÑADIR OBJETOS GRAFICOS         ///
void Escena_Guerra::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETO
    canon = new Objeto_Grafico(ruta,x,y,w,h);
    ///ASIGNACION DE VALORES
    this->addItem(canon);
    objetosGraficos.push_back(canon);
}

void Escena_Guerra::addObjetoMovil(QString ruta, int x, int y, int xf, int yf, int w, int h, int move)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    int param = 5;              //Parametro Altura Maxima
    bool minMax = true;         //Minimo Valor del Parametro

    ///CREACION DE OBJETO MOVIL
    proyectil = new Objeto_Movil(ruta,x,y,xf,yf,w,h,move);
    objetosMoviles.push_back(proyectil);     //Añadir objeto a la lista de objetos moviles

    /// ASIGNACION DE MOVIMIENTO PARABOLICO
    if(move == 1) proyectil->setMovParabolico(xf,yf,param,minMax);   //Calcula velocidad y angulo inicial

    //qDebug()<<"No hay problemas con la inicializacion del movimiento";

    //ASIGNACION DE MOVIMIENTO SENOIDAL
    //muni->setMovSenoidal();

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(proyectil);                //Se añade el objeto a la escena
    proyectil->startMove(time_move);                //Asigna valor de timeout para el movimiento
}

void Escena_Guerra::addObjetoMovil(QString ruta, int x, int y, int v0, int angle, bool lado)
{
    ///CREACION DE OBJETO MOVIL
    proyectil = new Objeto_Movil(ruta,x,y,100,100);
    objetosMoviles.push_back(proyectil);     //Añadir objeto a la lista de objetos moviles
    proyectil->setVel(v0,angle);

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(proyectil);                //Se añade el objeto a la escena
}

void Escena_Guerra::explodeObject(int _x, int _y, int _w, int _h)
{
    proyectil = new Objeto_Movil(":/personajes/imagenes/explode.png",_x,_y,_w,_h);
}

void Escena_Guerra::pause()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->stop();
        }
    }
}

void Escena_Guerra::start()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->startMove(time_move);
        }
    }
}

void Escena_Guerra::restart()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->deleteObject();
        }
        objetosMoviles.clear();
    }
}

bool Escena_Guerra::deleteFromScene()
{
    //cont_1++;
    bool collides = false;
    int cont = 0,cont2 = 0;
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++,cont++){
            if((*itObjMov)->getOutOfScene()){
                collides = true;
                if(!(*itObjMov)->getLado()){
                    ///SE REDUCE LA VIDA DEL JUGADOR
                    //this->setHurt();
                }
                if((*itObjMov) == objetosMoviles.at(cont)){
                    (*itObjMov)->deleteObject();
                    objetosMoviles.erase(itObjMov);
                }
                return collides;
            }
            else{
                for (itObjMov2 = objetosMoviles.begin(),cont2=0;itObjMov2 != objetosMoviles.end();itObjMov2++,cont2++) {
                    /// Si es bala ///              ///Si es Enemigo///
                    if((*itObjMov)->getLado() && !(*itObjMov2)->getLado()){
                        if((*itObjMov)->collidesWithItem((*itObjMov2))
                                && ((*itObjMov2)->collidesWithItem((*itObjMov)))
                                /*|| (*itObjMov)->closeness((*itObjMov2),10)*/){
                            collides = true; //setScorePlus();
                            //this->explodeObject((*itObjMov)->getX(),(*itObjMov)->getY(),100,100);
                            (*itObjMov)->deleteObject();
                            objetosMoviles.erase(itObjMov);
                            (*itObjMov2)->deleteObject();
                            objetosMoviles.erase(itObjMov2);


                            return collides;
                        }
                    }
                }
            }
        }
    }
    return collides;
}
