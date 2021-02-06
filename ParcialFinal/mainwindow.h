#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QPushButton>
#include "escena_guerra.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

        /// CARACTERISTICAS DE PANTALLA
    void setDeskProperty();

    void crearObjetos();

    void checkScene();
    void addProyectilSimple();
    void generarDisparos1();
    void generarDisparos2();
    void generarDisparos3();
    void generarDisparos4();
    void generarDisparos5();


    void caso1();
    void caso2();
    void caso3();
    void caso4();
    void caso5();
private:
    Ui::MainWindow *ui;

    QDesktopWidget *deskWidget;    
    QGraphicsView *view;
    Escena_Guerra *scene;
    QPushButton *boton;
    QPushButton *boton1;
    QPushButton *boton2;
    QPushButton *boton3;
    QPushButton *boton4;
    QPushButton *boton5;

    QTimer *timeCheck;
    QTimer *time1;
    QTimer *time2;
    QTimer *time3;
    QTimer *time4;
    QTimer *time5;

    int cont1 = 0;
    int cont2 = 0;
    int cont3 = 0;
    int cont4 = 0;
    int cont5 = 0;

    int m_sec = 100;
        /// MEDIDAS DE ESCRITORIO
    int desk_widht,desk_height;
};
#endif // MAINWINDOW_H
