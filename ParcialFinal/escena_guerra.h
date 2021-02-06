#ifndef ESCENA_GUERRA_H
#define ESCENA_GUERRA_H

#include <QGraphicsScene>
#include <QPushButton>
#include "objeto_grafico.h"
#include "objeto_movil.h"

class Escena_Guerra : public QGraphicsScene
{
public:
        /// CONSTRUCTOR Y DESTRUCTOR
    Escena_Guerra();
    ~Escena_Guerra();

        /// CARACTERISTICAS DE ESCRITORIO
    void setWindowProperty(int desk_w, int desk_h);
    virtual void drawBackground(QPainter *painter, const QRectF &exposed);
    void añadirObjetosEscena();

        /// FUNCIONES AÑADIR OBJETOS GRAFICOS
    void addObjetoGrafico(QString ruta,int x,int y,int w,int h,bool estatico);
    void addObjetoMovil(QString ruta, int x, int y, int xf, int yf, float radio, int caso);
    void addObjetoMovil(QString ruta, int x, int y, int v0, int angle, bool lado);
    void addCirculo(Objeto_Movil *obj);
    void explodeObject(int _x,int _y,int _w,int _h);

    void disparoOfensivo(int caso);
    void disparoDefensivo(int caso);

    void caso1();
    void caso2();
    void caso3();
    void caso4();
    void caso5();


        /// FUNCION DE CONTROL DE JUEGO
    void pause();
    void start();
    void restart();

        /// CONTROL DE COLISIONES Y PUESTAS EN ESCENA
    bool deleteFromScene();
    void cleanScene();

    float getRadio_ofensivo() const;
    float getRadio_defensivo() const;

private:
    /// APUNTADOR A OBJETOS GRAFICOS
    Objeto_Grafico *canon;
    Objeto_Grafico *bala;
    Objeto_Movil *proyectil;

        /// CONTENEDORES DE OBJETOS
    vector<Objeto_Grafico *> objetosGraficos;
    vector<Objeto_Grafico *>::iterator it;
    vector<Objeto_Movil *> objetosMoviles;
    vector<Objeto_Movil *>::iterator itObjMov;
    vector<Objeto_Movil *>::iterator itObjMov2;

        /// CARACTERISTICAS DE ESCRITORIO
    int limit_x,limit_y;
    QPixmap *image;

        ///POSICION DE CAÑONES
    int x_canon1 = 100,y_canon1 = 500;
    int x_canon2 = 1200,y_canon2 = 600;
    float d = abs(x_canon1-x_canon2);
    float factor_impacto_ofensivo = 0.025;
    float factor_impacto_defensivo = 0.05;
    float radio_ofensivo = d*factor_impacto_ofensivo;
    float radio_defensivo = d*factor_impacto_defensivo;
    float tMensaje1 = 1, tMensaje2 = 1;

        /// RUTAS
    QString proyectil1_ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    QString circulo_ruta = ":/imagenes/Imagenes/circulo_impacto.png";
    QString canon1_ruta = ":/imagenes/Imagenes/canon1.png";
    QString canon2_ruta = ":/imagenes/Imagenes/canon2.png";

        /// ATRIBUTOS DE JUEGO
    int time_move = 60;
};

#endif // ESCENA_GUERRA_H
