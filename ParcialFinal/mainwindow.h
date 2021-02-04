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

    void addProyectilSimple();

private:
    Ui::MainWindow *ui;

    QDesktopWidget *deskWidget;    
    QGraphicsView *view;
    Escena_Guerra *scene;
    QPushButton *boton;

        /// MEDIDAS DE ESCRITORIO
    int desk_widht,desk_height;
};
#endif // MAINWINDOW_H
