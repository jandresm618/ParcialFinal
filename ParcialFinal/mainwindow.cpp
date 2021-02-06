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
    connect(boton1,&QPushButton::clicked,this,&MainWindow::caso1);
    connect(boton2,&QPushButton::clicked,this,&MainWindow::caso2);
    connect(boton3,&QPushButton::clicked,this,&MainWindow::caso3);
    connect(boton4,&QPushButton::clicked,this,&MainWindow::caso4);
    connect(boton5,&QPushButton::clicked,this,&MainWindow::caso5);

    connect(time1,&QTimer::timeout,this,&MainWindow::generarDisparos1);
    connect(time2,&QTimer::timeout,this,&MainWindow::generarDisparos2);
    connect(time3,&QTimer::timeout,this,&MainWindow::generarDisparos3);
    connect(time4,&QTimer::timeout,this,&MainWindow::generarDisparos4);
    connect(time5,&QTimer::timeout,this,&MainWindow::generarDisparos5);


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
    boton->setGeometry(400,200,100,100);
    scene->addWidget(boton);
    boton1 = new QPushButton("CASO 1");
    boton1->setGeometry(200,100,100,100);
    scene->addWidget(boton1);
    boton2 = new QPushButton("CASO 2");
    boton2->setGeometry(400,100,100,100);
    scene->addWidget(boton2);
    boton3 = new QPushButton("CASO 3");
    boton3->setGeometry(600,100,100,100);
    scene->addWidget(boton3);
    boton4 = new QPushButton("CASO 4");
    boton4->setGeometry(800,100,100,100);
    scene->addWidget(boton4);
    boton5 = new QPushButton("CASO 5");
    boton5->setGeometry(1000,100,100,100);
    scene->addWidget(boton5);

    time1 = new QTimer;
    time2 = new QTimer;
    time3 = new QTimer;
    time4 = new QTimer;
    time5 = new QTimer;
}


void MainWindow::addProyectilSimple()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    int _x = 100, _y=500;
    scene->addObjetoMovil(_ruta,_x,_y,80,30,false);
    scene->disparoOfensivo(1);
}

void MainWindow::generarDisparos1()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    if(cont1 == 5) scene->disparoOfensivo(1);
    if(cont1 == 15) scene->disparoOfensivo(2);
    if(cont1 == 25) {scene->disparoOfensivo(3);cont1 =0;time1->stop();}
    cont1++;
}

void MainWindow::generarDisparos2()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    if(cont2 == 5) scene->disparoDefensivo(1);
    if(cont2 == 15) scene->disparoDefensivo(2);
    if(cont2 == 25) {scene->disparoDefensivo(3);cont2 =0;time2->stop();}
    cont2++;
}

void MainWindow::generarDisparos3()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    if(cont3 == 1) scene->disparoOfensivo(1);
    if(cont3 == 2) scene->disparoDefensivo(1);
    if(cont3 == 12) scene->disparoDefensivo(2);
    if(cont3 == 24) {scene->disparoDefensivo(3);cont3 =0;time3->stop();}
    cont3++;
}

void MainWindow::generarDisparos4()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    if(cont4 == 1) scene->disparoOfensivo(1);
    if(cont4 == 2) scene->disparoDefensivo(1);
    if(cont4 == 12) scene->disparoDefensivo(2);
    if(cont4 == 24) {scene->disparoDefensivo(3);cont4 =0;time4->stop();}
    cont4++;
}

void MainWindow::generarDisparos5()
{
    QString _ruta = ":/imagenes/Imagenes/bola_artilleria.png";
    if(cont5 == 1) scene->disparoOfensivo(1);
    if(cont5 == 2) scene->disparoDefensivo(1);
    if(cont5 == 2) scene->disparoOfensivo(1);
    if(cont5 == 12) scene->disparoOfensivo(2);
    if(cont5 == 24) {scene->disparoOfensivo(3);cont5 =0;time5->stop();}
    cont5++;
}

void MainWindow::caso1()
{
    time1->start(m_sec);
    /// PREPARAR LOS ELEMENTOS EN ESCENA
        /// 3 DISPAROS OFENSIVOS
}

void MainWindow::caso2()
{
    time2->start(m_sec);
    /// PREPARAR LOS ELEMENTOS EN ESCENA
        /// 3 DISPAROS DEFENSIVOS
}

void MainWindow::caso3()
{
    time3->start(m_sec);
    /// PREPARAR LOS ELEMENTOS EN ESCENA
        /// 1 DISPAROS OFENSIVO Y 3 DEFENSIVOS SIN RESTRICCION
}

void MainWindow::caso4()
{
    time4->start(m_sec);
    /// PREPARAR LOS ELEMENTOS EN ESCENA
        /// 1 DISPAROS OFENSIVO Y 3 DEFENSIVOS CON RESTRICCION
}

void MainWindow::caso5()
{
    time5->start(m_sec);
    /// PREPARAR LOS ELEMENTOS EN ESCENA
        /// 1 DISPAROS OFENSIVO Y 1 DEFENSIVOS SIN RESTRICCION
        /// 3 OFENSIVOS AL DEFENSIVO
}

