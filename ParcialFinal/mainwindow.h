#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QPushButton>
#include "escena.h"

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

    void addProyectilSimple(QString ruta,int x,int y,int tMove);

private:
    Ui::MainWindow *ui;

    QDesktopWidget *deskWidget;
    Escena* scene;
    QGraphicsView *view;

    QPushButton *boton;

        /// MEDIDAS DE ESCRITORIO
    int desk_widht,desk_height;
};
#endif // MAINWINDOW_H
