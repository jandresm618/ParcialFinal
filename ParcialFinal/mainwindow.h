#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
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
    void setDeskProperty(int w,int h);

    void crearObjetos();

private:
    Ui::MainWindow *ui;

    Escena* scene;
    QGraphicsView *view;

        /// MEDIDAS DE ESCRITORIO
    int desk_widht,desk_height;
};
#endif // MAINWINDOW_H
