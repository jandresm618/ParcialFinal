#include "escena.h"

///         CONSTRUCTOR         ///
Escena_Juego::Escena_Juego()
{
    //image = new QPixmap(":/personajes/imagenes/Fondo_Original1.png");
    image = new QPixmap(":/personajes/imagenes/fondo.png");
}

///         DESTRUCTOR         ///
Escena_Juego::~Escena_Juego()
{
    ///ELIMINACION DE MEMORIA
    delete personaje;
    delete muni;
}

void Escena_Juego::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    //qDebug()<<"x "<<event->scenePos().x()<<" y "<<event->scenePos().y();
}

///         PROPIEDADES DE VENTANA         ///
void Escena_Juego::setWindowProperty(int desk_w, int desk_h)
{
    limit_x = desk_w;
    limit_y = desk_h;
    setSceneRect(0,0,desk_w,desk_h);
}

void Escena_Juego::drawBackground(QPainter *painter, const QRectF &exposed)
{
    painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image,image->rect());
}

///         ESTABLECER ESCENA ARCADE         ///
void Escena_Juego::arcadeDesing()
{
    int x_1 = 100, y_1 = 500;
    int w_1 = 100, h_1 = 100;
    QString path_1 = ":/personajes/imagenes/mario.png";
    addObjetoGrafico(path_1,x_1,y_1,w_1,h_1);
}

///         AÑADIR OBJETOS GRAFICOS         ///
void Escena_Juego::addObjetoGrafico(QString ruta, int x, int y, int w, int h)
{
    ///DECLARACION DE OBJETO
    personaje = new Objeto_Grafico(ruta,x,y,w,h);
    ///ASIGNACION DE VALORES
    this->addItem(personaje);
    objetosGraficos.push_back(personaje);
}

///         AÑADIR OBJETOS GRAFICOS MOVILES         ///
void Escena_Juego::addObjetoMovil(QString ruta, int x, int y,int xf,int yf, int w, int h, int move)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    int param = 5;              //Parametro Altura Maxima
    bool minMax = true;         //Minimo Valor del Parametro

    ///CREACION DE OBJETO MOVIL
    muni = new Objeto_Movil(ruta,x,y,xf,yf,w,h,move);
    objetosMoviles.push_back(muni);     //Añadir objeto a la lista de objetos moviles

    /// ASIGNACION DE MOVIMIENTO PARABOLICO
    if(move == 1) muni->setMovParabolico(xf,yf,param,minMax);   //Calcula velocidad y angulo inicial

    //qDebug()<<"No hay problemas con la inicializacion del movimiento";

    //ASIGNACION DE MOVIMIENTO SENOIDAL
    //muni->setMovSenoidal();

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
    muni->startMove(time_move);                //Asigna valor de timeout para el movimiento
}

void Escena_Juego::addObjetoMovil(QString ruta, int x, int y, int v0, int angle, int move)
{
    ///CREACION DE OBJETO MOVIL
    muni = new Objeto_Movil(ruta,x,y,0,500,100,100,move);
    objetosMoviles.push_back(muni);     //Añadir objeto a la lista de objetos moviles
    muni->setVel(v0,angle);

    /// INICIALIZACION DE OBJETO EN ESCENA
    this->addItem(muni);                //Se añade el objeto a la escena
}

void Escena_Juego::explodeObject(int _x, int _y, int _w, int _h)
{
    muni = new Objeto_Movil(":/personajes/imagenes/explode.png",_x,_y,_w,_h);
}

///         FUNCION MOVIMIENTO DE PRUEBA         ///
void Escena_Juego::doSome()
{
    ///ASIGNACION DE VALORES
    personaje->set_Pos(personaje->getX()+50,personaje->getY());
}

int Escena_Juego::getHurt()
{
    return blood;
}

void Escena_Juego::pause()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->stop();
        }
    }
}

void Escena_Juego::start()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->startMove(time_move);
        }
    }
}

void Escena_Juego::restart()
{
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++){
            (*itObjMov)->deleteObject();
        }
        objetosMoviles.clear();
    }
    score = 0;
    blood = 100;
}

void Escena_Juego::setHurt()
{
    blood -= 10;
}


///         ELIMINA LOS OBJETOS QUE ESTEN FUERA DE ESCENA´         ///
bool Escena_Juego::deleteFromScene()
{
    cont_1++;
    bool collides = false;
    int cont = 0,cont2 = 0;
    if(!objetosMoviles.empty()){
        for(itObjMov = objetosMoviles.begin();itObjMov != objetosMoviles.end();itObjMov++,cont++){
            if((*itObjMov)->getOutOfScene()){
                collides = true;
                if(!(*itObjMov)->getLado()){
                    ///SE REDUCE LA VIDA DEL JUGADOR
                    this->setHurt();
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
                            collides = true; setScorePlus();
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

int Escena_Juego::getScore() const
{
    return score;
}

void Escena_Juego::setScore(int value)
{
    score = value;
}

void Escena_Juego::setScorePlus()
{
    score ++;
}

vector<Objeto_Movil *> Escena_Juego::getObjetosMoviles() const
{
    return objetosMoviles;
}

int Escena_Juego::getBlood() const
{
    return blood;
}

void Escena_Juego::setBlood(int value)
{
    blood = value;
}
