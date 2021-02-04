#ifndef ESCENA_JUEGO_H
#define ESCENA_JUEGO_H

#include <QGraphicsScene>
#include <QPushButton>
#include "objeto_grafico.h"
#include "objeto_movil.h"


class Escena_Juego : public QGraphicsScene
{

public:    
        /// CONSTRUCTOR Y DESTRUCTOR
    Escena_Juego();
    ~Escena_Juego();


        /// CARACTERISTICAS DE ESCRITORIO
    void setWindowProperty(int desk_w, int desk_h);
    virtual void drawBackground(QPainter *painter, const QRectF &exposed);

        /// FUNCIONES AÑADIR OBJETOS GRAFICOS
    void addObjetoGrafico(QString ruta,int x,int y,int w,int h);
    void addObjetoMovil(QString ruta,int x,int y,int xf,int yf,int w,int h,int move);
    void addObjetoMovil(QString ruta,int x,int y,int v0,int angle,int move);
    void explodeObject(int _x,int _y,int _w,int _h);


        /// FUNCION DE CONTROL DE JUEGO
    void pause();
    void start();
    void restart();

        /// CONTROL DE COLISIONES Y PUESTAS EN ESCENA
    bool deleteFromScene();



private:
    /// APUNTADOR A OBJETOS GRAFICOS
    Objeto_Grafico *canon;
    Objeto_Movil *proyectil;

        /// CONTENEDORES DE OBJETOS
    vector<Objeto_Grafico *> objetosGraficos;
    vector<Objeto_Movil *> objetosMoviles;
    vector<Objeto_Movil *>::iterator itObjMov;
    vector<Objeto_Movil *>::iterator itObjMov2;

        /// CARACTERISTICAS DE ESCRITORIO
    int limit_x,limit_y;
    QPixmap *image;

        /// ATRIBUTOS DE JUEGO
    int time_move = 60;
};

#endif // ESCENA_JUEGO_H
