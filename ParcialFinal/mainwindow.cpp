#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    crearObjetos();
    this->showMaximized();

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
   view->setGeometry(0,0,desk_widht,desk_height);
   scene->setWindowProperty(desk_widht,desk_height);
}

void MainWindow::crearObjetos()
{
    scene = new Escena_Guerra;
    view = new QGraphicsView(this);
    deskWidget = new QDesktopWidget;
    setDeskProperty();
    view->setScene(scene);
    boton = new QPushButton("AÑADIR MISIL");
    boton->setGeometry(400,100,100,100);
    scene->addWidget(boton);

}


void MainWindow::addProyectilSimple()
{
    QString _ruta = ":/imagenes/Imagenes/Bomba.png";
    int _x = 100, _y=500;
    scene->addObjetoMovil(_ruta,_x,_y,50,30,false);
}

