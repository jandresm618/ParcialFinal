#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    crearObjetos();

    connect(boton,&QPushButton::clicked,this,&MainWindow::addProyectilSimple);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///     FUNCION SET PROPIEDADES ESCRITORIO      ///
void MainWindow::setDeskProperty()
{
    ///ASIGNACION DE VALORES
   desk_widht = deskWidget->width();   desk_height = deskWidget->height();
   view->setGeometry(0,0,desk_widht,deskWidget->height());
   scene->setWindowProperty(desk_widht,deskWidget->height());
}

void MainWindow::crearObjetos()
{
    scene = Escena;
    view = new QGraphicsView(scene,this);
    deskWidget = new QDesktopWidget;
    setDeskProperty();
    boton = new QPushButton;

}

void MainWindow::addProyectilSimple(QString ruta, int x, int y, int tMove)
{
    QString _ruta = ":/imagenes/Imagenes/Bomba.png";
    int _x = 100, _y=500;
    scene->addObjetoMovil(ruta,_x,_y,50,30,false);
}

