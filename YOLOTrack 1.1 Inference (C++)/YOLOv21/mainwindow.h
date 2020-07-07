#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../TF DLL/TF.h"
#include "../../YOLOv21 DLL/YOLOv21.h"


#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QElapsedTimer>
#include <qmath.h>
#include <QDebug>

#include "mygraphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectModelDialog();
    void selectImageDialog();
    void objectThreshold_slider_changed();
    void objectThreshold_doubleSpinBox_changed();
    void nmsThreshold_slider_changed();
    void nmsThreshold_doubleSpinBox_changed();
    void update();

private:
    Ui::MainWindow *ui;

    bool modelState, imageState;
    int image_w, image_h, grid_h, grid_w, boxes, classes;
    float *anchors;
    char *in_name, *out_name;

    QImage image;
    float objectThreshold, nmsThreshold;

    float *input_tensor = nullptr;
    float *output_tensor = nullptr;

    int *n_out;
    float *x_out = nullptr;
    float *y_out = nullptr;
    float *w_out = nullptr;
    float *h_out = nullptr;
    float *p_out = nullptr;
    int *c_out = nullptr;

    MyGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QGraphicsPixmapItem *item;

    bool loadModel(const QString &);
    bool loadINI(const QString &);
    void updateEnabled(bool);
    bool loadImage(const QString &);
    //void setImage(const QImage &newImage);

    QElapsedTimer timer;
};

#endif // MAINWINDOW_H
