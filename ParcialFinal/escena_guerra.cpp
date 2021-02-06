#include "escena_guerra.h"

///         CONSTRUCTOR         ///
Escena_Guerra::Escena_Guerra()
{
    //image = new QPixmap(":/personajes/imagenes/Fondo_Original1.png");
    image = new QPixmap(":/personajes/imagenes/fondo.png");
    añadirObjetosEscena();

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

void Escena_Guerra::añadirObjetosEscena()
{
    int dif = y_canon1 - y_canon2;
    addObjetoGrafico(canon1_ruta,x_canon1,y_canon1,radio_ofensivo/2,radio_ofensivo/2,true);
    addObjetoGrafico(circulo_ruta,x_canon1,y_canon1,radio_ofensivo,radio_ofensivo,true);
    addObjetoGrafico(canon2_ruta,x_canon2,y_canon2+dif,radio_defensivo/2,radio_defensivo/2,true);
    addObjetoGrafico(circulo_ruta,x_canon2,y_canon2+dif,radio_defensivo,radio_defensivo,true);
}

void Escena_Guerra::drawBackground(QPainter *painter, const QRectF &exposed)
{

    painter->drawPixmap(QRectF(0,0,limit_x,limit_y),*image,image->rect());
}

///         AÑADIR OBJETOS GRAFICOS         ///
void Escena_Guerra::addObjetoGrafico(QString ruta, int x, int y, int w, int h, bool estatico)
{
    ///DECLARACION DE OBJETO
    canon = new Objeto_Grafico(ruta,x,y,w,h);
    ///ASIGNACION DE VALORES
    this->addItem(canon);
    if(!estatico) objetosGraficos.push_back(canon);

}

void Escena_Guerra::addObjetoMovil(QString ruta, int x, int y, int xf, int yf, float radio,int caso)
{
    ///DECLARACION DE VARIABLES AUXILIARES LOCALES
    float factorImpacto = radio/(abs(x-xf));
    float dif = y-yf;

    ///CREACION DE OBJETO MOVIL
    if(x-xf < 0 ) proyectil = new Objeto_Movil(ruta,x,y,xf,radio);
    else proyectil = new Objeto_Movil(ruta,x,y-dif,xf,radio);
    proyectil->setCaso(caso);
    objetosMoviles.push_back(proyectil);     //Añadir objeto a la lista de objetos moviles

    if(caso == 1 || caso == 2 || caso == 3){
        proyectil->calcularParametrosImpactoEstatico(xf,yf,factorImpacto);
    }

    /// ASIGNACION DE MOVIMIENTO PARABOLICO
    proyectil->getMovParabolico(caso-1);

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

void Escena_Guerra::addCirculo(Objeto_Movil *obj)
{

    addObjetoGrafico(circulo_ruta,obj->getX(),obj->getY(),obj->getRadio(),obj->getRadio(),false);
}

void Escena_Guerra::explodeObject(int _x, int _y, int _w, int _h)
{
    proyectil = new Objeto_Movil(":/personajes/imagenes/explode.png",_x,_y,_w,_h);
}

void Escena_Guerra::disparoDefensivo(int caso)
{
    addObjetoMovil(proyectil1_ruta,x_canon2,y_canon2,x_canon1,y_canon1,radio_defensivo/2,caso);
}

void Escena_Guerra::disparoOfensivo(int caso)
{
    addObjetoMovil(proyectil1_ruta,x_canon1,y_canon1,x_canon2,y_canon2,radio_ofensivo/2,caso);
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
                (*itObjMov)->deleteObject();
                objetosMoviles.erase(itObjMov);
                collides = true;
                return collides;
            }
            else if((*itObjMov)->able()){
                    addCirculo((*itObjMov));
                }

        }
    }
    return collides;
}

void Escena_Guerra::cleanScene()
{
    if(!objetosGraficos.empty()){
        for(it = objetosGraficos.begin();it!= objetosGraficos.end();it++){
            delete (*it);
        }
        objetosGraficos.clear();
    }
}

float Escena_Guerra::getRadio_ofensivo() const
{
    return radio_ofensivo;
}

float Escena_Guerra::getRadio_defensivo() const
{
    return radio_defensivo;
}
