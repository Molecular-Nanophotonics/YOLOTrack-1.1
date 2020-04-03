#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    graphicsView = new MyGraphicsView();
    ui->verticalLayout->addWidget(graphicsView);
    graphicsScene = new QGraphicsScene();
    graphicsView->setScene(graphicsScene);

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->selectModel_button, &QPushButton::clicked, this,  &MainWindow::selectModelDialog);
    connect(ui->selectImage_button, &QPushButton::clicked, this,  &MainWindow::selectImageDialog);
    connect(ui->update_button, &QPushButton::clicked, this,  &MainWindow::update);
    connect(ui->objectThreshold_slider, &QSlider::valueChanged, this,  &MainWindow::objectThreshold_slider_changed);
    connect(ui->objectThreshold_doubleSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::objectThreshold_doubleSpinBox_changed);
    connect(ui->nmsThreshold_slider, &QSlider::valueChanged, this,  &MainWindow::nmsThreshold_slider_changed);
    connect(ui->nmsThreshold_doubleSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::nmsThreshold_doubleSpinBox_changed);

    n_out = new int(0);

    char tensorflow_version[32];
    if (!getVersion(tensorflow_version))
        ui->tensorflowVersion_label1->setText(QString(tensorflow_version));
        char device_name[32];
        if (!getDeviceName(device_name))
            ui->deviceName_label1->setText(QString(device_name));

    objectThreshold = ui->objectThreshold_doubleSpinBox->value();
    nmsThreshold = ui->nmsThreshold_doubleSpinBox->value();

    modelState = false;
    imageState = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::selectModelDialog()
{
    QString modelFileName = QFileDialog::getOpenFileName(this, "Open Model", "../../Samples", "Protocol Buffer File (*.pb)");
    QDir dir;
    if (!modelFileName.isEmpty()) {
        modelState = loadModel(modelFileName);
        if (modelState) {
            ui->modelPath_lineEdit->setText(dir.relativeFilePath(modelFileName));
            ui->imagePath_lineEdit->setEnabled(true);
            ui->selectImage_button->setEnabled(true);
            if (imageState) {
                ui->imagePath_lineEdit->clear();
                ui->runTime_label->clear();
                ui->decodeTime_label->clear();
                graphicsScene->clear();
                updateEnabled(false);
            }
        }
    }
}


void MainWindow::selectImageDialog()
{
    QString imageFileName = QFileDialog::getOpenFileName(this, "Open Image", "../../Samples", "JPG Files (*.jpg)");
    QDir dir;
    if (!imageFileName.isEmpty()) {
        imageState = loadImage(imageFileName);
        if (imageState) {
            ui->imagePath_lineEdit->setText(dir.relativeFilePath(imageFileName));
            if (modelState) {
                updateEnabled(true);
                update();
            }
        }
    }
}


void MainWindow::updateEnabled(bool state)
{
    ui->update_button->setEnabled(state);
    ui->objectThreshold_slider->setEnabled(state);
    ui->objectThreshold_doubleSpinBox->setEnabled(state);
    ui->nmsThreshold_slider->setEnabled(state);
    ui->nmsThreshold_doubleSpinBox->setEnabled(state);
}


void MainWindow::update()
{
    timer.start();
    runTF(input_tensor, output_tensor);
    ui->runTime_label->setText(QString::number(1e-6*timer.nsecsElapsed(), 'f', 3));

    timer.start();
    decodeYOLO(output_tensor, objectThreshold, nmsThreshold, n_out, x_out, y_out, w_out, h_out, p_out, c_out);
    ui->decodeTime_label->setText(QString::number(1e-6*timer.nsecsElapsed(), 'f', 3));

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    pixmapItem->setFlags(QGraphicsItem::ItemIsMovable);

    graphicsScene->clear();

    QVector<QColor> colors = {Qt::green}; //{Qt::cyan, Qt::yellow, Qt::green, Qt::blue, Qt::red};

    QGraphicsItemGroup *itemGroup = new QGraphicsItemGroup();
    itemGroup->addToGroup(pixmapItem);

    QPen(Qt::red, 1);
    for (int i = 0; i < *n_out; i++)
    {
        int x = x_out[i]*image_w;
        int y = y_out[i]*image_h;
        int w = w_out[i]*image_w;
        int h = h_out[i]*image_h;
        int p = p_out[i]*(-360);
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(x-0.5*w, y-0.5*w, w, h);
        rectItem->setTransformOriginPoint(x, y);
        rectItem->setRotation(p);
        rectItem->setPen(QPen(colors[c_out[i] % colors.length()], 1));
        itemGroup->addToGroup(rectItem);
        QGraphicsLineItem *lineItem = new QGraphicsLineItem(x, y, x + 0.5*w*qCos(p/57.3), y + 0.5*h*qSin(p/57.3));
        lineItem->setPen(QPen(colors[c_out[i] % colors.length()], 1));
        itemGroup->addToGroup(lineItem);
    }

    itemGroup->setFlags(QGraphicsItem::ItemIsMovable);
    graphicsScene->addItem(itemGroup);
}


void MainWindow::objectThreshold_slider_changed()
{
    objectThreshold = 0.01*ui->objectThreshold_slider->value();
    ui->objectThreshold_doubleSpinBox->setValue(objectThreshold);
    update();
}

void MainWindow::objectThreshold_doubleSpinBox_changed()
{
    objectThreshold = ui->objectThreshold_doubleSpinBox->value();
    ui->objectThreshold_slider->setValue(objectThreshold*100);
    update();
}

void MainWindow::nmsThreshold_slider_changed()
{
    nmsThreshold = 0.01*ui->nmsThreshold_slider->value();
    ui->nmsThreshold_doubleSpinBox->setValue(nmsThreshold);
    update();
}

void MainWindow::nmsThreshold_doubleSpinBox_changed()
{
    nmsThreshold = ui->nmsThreshold_doubleSpinBox->value();
    ui->nmsThreshold_slider->setValue(nmsThreshold*100);
    update();
}


bool MainWindow::loadImage(const QString &imageFileName)
{
    image = QImageReader(imageFileName).read().convertToFormat(QImage::Format_RGB888);

    if (image.isNull()) {
        //QMessageBox::information(this, QGuiApplication::applicationDisplayName(), "...");
        return false;
    }

    uint8_t *bits = image.bits();

    for (int i = 0; i < (image.width()*image.height()*3); i++)
    {
        input_tensor[i] = (float)(bits[i]/255.);
    }

    return true;
}


bool MainWindow::loadModel(const QString &modelFileName)
{
    char* model_file_name = _strdup(modelFileName.toStdString().c_str());

    QFileInfo info(modelFileName);
    QString iniFileName = info.path() + "/" + info.baseName() + ".ini";
    loadINI(iniFileName);

    int64_t in_shape[] = {1, image_w, image_h, 3};

    int in_dim = 4;
    int input_size = 1;
    for (int i = 0; i < in_dim; i++)
        input_size *= in_shape[i];

    free(input_tensor);
    input_tensor = (float *) calloc(input_size, sizeof(float));

    int64_t out_shape[] = {1, grid_w, grid_h, boxes, 5 + 1 + classes};
    int out_dim = 5;
    int output_size = 1;
    for (int i = 0; i < out_dim; i++)
        output_size *= out_shape[i];
    free(output_tensor);
    output_tensor = (float *) calloc(output_size, sizeof(float));

    x_out = (float *)realloc(x_out, 100*sizeof(float));
    y_out = (float *)realloc(y_out, 100*sizeof(float));
    w_out = (float *)realloc(w_out, 100*sizeof(float));
    h_out = (float *)realloc(h_out, 100*sizeof(float));
    p_out = (float *)realloc(p_out, 100*sizeof(float));
    c_out = (int *)realloc(c_out, 100*sizeof(int));

    setupTF(model_file_name, in_shape, in_dim, in_name, out_shape, out_dim, out_name);
    setupYOLO(image_w, image_h, grid_w, grid_h, boxes, classes, anchors, 100);

    return true;
}

bool MainWindow::loadINI(const QString &iniFileName)
{
    QSettings settings(iniFileName, QSettings::IniFormat);

    image_h = settings.value("IMAGE_H").toInt();
    image_w = settings.value("IMAGE_W").toInt();
    grid_h = settings.value("GRID_H").toInt();
    grid_w = settings.value("GRID_W").toInt();
    boxes = settings.value("BOXES").toInt();
    classes = settings.value("CLASSES").toInt();

    QString INPUT_NODE_NAME = settings.value("INPUT_NODE_NAME").toString();
    in_name = _strdup(INPUT_NODE_NAME.toStdString().c_str());

    QString OUTPUT_NODE_NAME = settings.value("OUTPUT_NODE_NAME").toString();
    out_name = _strdup(OUTPUT_NODE_NAME.toStdString().c_str());

    QStringList ANCHORS = settings.value("ANCHORS").toStringList();
    anchors = (float *)malloc(sizeof(float)*ANCHORS.size());
    for (int i = 0; i < ANCHORS.size(); i++)
        anchors[i] = ANCHORS[i].toFloat();

    return true;
}
