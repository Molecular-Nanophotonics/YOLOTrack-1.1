/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *selectImage_button;
    QLabel *tensorflowVersion_label1;
    QLabel *deviceName_label0;
    QLabel *tensorflowVersion_label0;
    QLabel *deviceName_label1;
    QLineEdit *imagePath_lineEdit;
    QLabel *imagePath_label;
    QPushButton *selectModel_button;
    QLabel *modelPath_label;
    QLineEdit *modelPath_lineEdit;
    QSlider *objectThreshold_slider;
    QSlider *nmsThreshold_slider;
    QDoubleSpinBox *objectThreshold_doubleSpinBox;
    QDoubleSpinBox *nmsThreshold_doubleSpinBox;
    QLabel *objectThreshold_label;
    QLabel *nmsThreshold_label;
    QPushButton *update_button;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *timings_groupBox;
    QLabel *runTime_label;
    QLabel *decodeTime_label;
    QLabel *runTime_label_2;
    QLabel *runTime_label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(529, 790);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        selectImage_button = new QPushButton(centralWidget);
        selectImage_button->setObjectName(QString::fromUtf8("selectImage_button"));
        selectImage_button->setEnabled(true);
        selectImage_button->setGeometry(QRect(490, 130, 31, 23));
        tensorflowVersion_label1 = new QLabel(centralWidget);
        tensorflowVersion_label1->setObjectName(QString::fromUtf8("tensorflowVersion_label1"));
        tensorflowVersion_label1->setGeometry(QRect(10, 30, 71, 21));
        tensorflowVersion_label1->setFrameShape(QFrame::Panel);
        tensorflowVersion_label1->setFrameShadow(QFrame::Sunken);
        deviceName_label0 = new QLabel(centralWidget);
        deviceName_label0->setObjectName(QString::fromUtf8("deviceName_label0"));
        deviceName_label0->setGeometry(QRect(130, 10, 91, 16));
        tensorflowVersion_label0 = new QLabel(centralWidget);
        tensorflowVersion_label0->setObjectName(QString::fromUtf8("tensorflowVersion_label0"));
        tensorflowVersion_label0->setGeometry(QRect(10, 10, 101, 16));
        deviceName_label1 = new QLabel(centralWidget);
        deviceName_label1->setObjectName(QString::fromUtf8("deviceName_label1"));
        deviceName_label1->setGeometry(QRect(130, 30, 161, 21));
        deviceName_label1->setFrameShape(QFrame::Panel);
        deviceName_label1->setFrameShadow(QFrame::Sunken);
        imagePath_lineEdit = new QLineEdit(centralWidget);
        imagePath_lineEdit->setObjectName(QString::fromUtf8("imagePath_lineEdit"));
        imagePath_lineEdit->setEnabled(true);
        imagePath_lineEdit->setGeometry(QRect(9, 132, 471, 20));
        imagePath_lineEdit->setReadOnly(true);
        imagePath_label = new QLabel(centralWidget);
        imagePath_label->setObjectName(QString::fromUtf8("imagePath_label"));
        imagePath_label->setEnabled(true);
        imagePath_label->setGeometry(QRect(9, 112, 101, 16));
        selectModel_button = new QPushButton(centralWidget);
        selectModel_button->setObjectName(QString::fromUtf8("selectModel_button"));
        selectModel_button->setGeometry(QRect(490, 80, 31, 23));
        modelPath_label = new QLabel(centralWidget);
        modelPath_label->setObjectName(QString::fromUtf8("modelPath_label"));
        modelPath_label->setGeometry(QRect(9, 62, 101, 16));
        modelPath_lineEdit = new QLineEdit(centralWidget);
        modelPath_lineEdit->setObjectName(QString::fromUtf8("modelPath_lineEdit"));
        modelPath_lineEdit->setEnabled(true);
        modelPath_lineEdit->setGeometry(QRect(9, 82, 471, 20));
        modelPath_lineEdit->setReadOnly(true);
        modelPath_lineEdit->setClearButtonEnabled(false);
        objectThreshold_slider = new QSlider(centralWidget);
        objectThreshold_slider->setObjectName(QString::fromUtf8("objectThreshold_slider"));
        objectThreshold_slider->setEnabled(false);
        objectThreshold_slider->setGeometry(QRect(110, 190, 160, 19));
        objectThreshold_slider->setMaximum(100);
        objectThreshold_slider->setSingleStep(1);
        objectThreshold_slider->setValue(60);
        objectThreshold_slider->setOrientation(Qt::Horizontal);
        nmsThreshold_slider = new QSlider(centralWidget);
        nmsThreshold_slider->setObjectName(QString::fromUtf8("nmsThreshold_slider"));
        nmsThreshold_slider->setEnabled(false);
        nmsThreshold_slider->setGeometry(QRect(110, 233, 160, 19));
        nmsThreshold_slider->setValue(45);
        nmsThreshold_slider->setOrientation(Qt::Horizontal);
        objectThreshold_doubleSpinBox = new QDoubleSpinBox(centralWidget);
        objectThreshold_doubleSpinBox->setObjectName(QString::fromUtf8("objectThreshold_doubleSpinBox"));
        objectThreshold_doubleSpinBox->setEnabled(false);
        objectThreshold_doubleSpinBox->setGeometry(QRect(280, 188, 51, 22));
        objectThreshold_doubleSpinBox->setMaximum(1.000000000000000);
        objectThreshold_doubleSpinBox->setSingleStep(0.010000000000000);
        objectThreshold_doubleSpinBox->setValue(0.600000000000000);
        nmsThreshold_doubleSpinBox = new QDoubleSpinBox(centralWidget);
        nmsThreshold_doubleSpinBox->setObjectName(QString::fromUtf8("nmsThreshold_doubleSpinBox"));
        nmsThreshold_doubleSpinBox->setEnabled(false);
        nmsThreshold_doubleSpinBox->setGeometry(QRect(280, 230, 51, 22));
        nmsThreshold_doubleSpinBox->setMaximum(1.000000000000000);
        nmsThreshold_doubleSpinBox->setSingleStep(0.010000000000000);
        nmsThreshold_doubleSpinBox->setValue(0.450000000000000);
        objectThreshold_label = new QLabel(centralWidget);
        objectThreshold_label->setObjectName(QString::fromUtf8("objectThreshold_label"));
        objectThreshold_label->setEnabled(true);
        objectThreshold_label->setGeometry(QRect(110, 170, 101, 16));
        nmsThreshold_label = new QLabel(centralWidget);
        nmsThreshold_label->setObjectName(QString::fromUtf8("nmsThreshold_label"));
        nmsThreshold_label->setEnabled(true);
        nmsThreshold_label->setGeometry(QRect(110, 213, 101, 16));
        update_button = new QPushButton(centralWidget);
        update_button->setObjectName(QString::fromUtf8("update_button"));
        update_button->setEnabled(false);
        update_button->setGeometry(QRect(10, 195, 75, 31));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 270, 511, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        timings_groupBox = new QGroupBox(centralWidget);
        timings_groupBox->setObjectName(QString::fromUtf8("timings_groupBox"));
        timings_groupBox->setEnabled(true);
        timings_groupBox->setGeometry(QRect(360, 173, 161, 78));
        runTime_label = new QLabel(timings_groupBox);
        runTime_label->setObjectName(QString::fromUtf8("runTime_label"));
        runTime_label->setEnabled(true);
        runTime_label->setGeometry(QRect(90, 20, 61, 21));
        runTime_label->setFrameShape(QFrame::Panel);
        runTime_label->setFrameShadow(QFrame::Sunken);
        runTime_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        decodeTime_label = new QLabel(timings_groupBox);
        decodeTime_label->setObjectName(QString::fromUtf8("decodeTime_label"));
        decodeTime_label->setEnabled(true);
        decodeTime_label->setGeometry(QRect(90, 45, 61, 21));
        decodeTime_label->setFrameShape(QFrame::Panel);
        decodeTime_label->setFrameShadow(QFrame::Sunken);
        decodeTime_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        runTime_label_2 = new QLabel(timings_groupBox);
        runTime_label_2->setObjectName(QString::fromUtf8("runTime_label_2"));
        runTime_label_2->setEnabled(true);
        runTime_label_2->setGeometry(QRect(10, 20, 61, 16));
        runTime_label_3 = new QLabel(timings_groupBox);
        runTime_label_3->setObjectName(QString::fromUtf8("runTime_label_3"));
        runTime_label_3->setEnabled(true);
        runTime_label_3->setGeometry(QRect(10, 45, 61, 16));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "YOLOTrack 1.1", nullptr));
        selectImage_button->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tensorflowVersion_label1->setText(QString());
        deviceName_label0->setText(QCoreApplication::translate("MainWindow", "Device Name", nullptr));
        tensorflowVersion_label0->setText(QCoreApplication::translate("MainWindow", "TensorFlow Version", nullptr));
        deviceName_label1->setText(QString());
        imagePath_label->setText(QCoreApplication::translate("MainWindow", "Path to Image", nullptr));
        selectModel_button->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        modelPath_label->setText(QCoreApplication::translate("MainWindow", "Path to Model", nullptr));
        objectThreshold_label->setText(QCoreApplication::translate("MainWindow", "Object Threshold", nullptr));
        nmsThreshold_label->setText(QCoreApplication::translate("MainWindow", "NMS Threshold", nullptr));
        update_button->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        timings_groupBox->setTitle(QCoreApplication::translate("MainWindow", "Timings [ms]", nullptr));
        runTime_label->setText(QString());
        decodeTime_label->setText(QString());
        runTime_label_2->setText(QCoreApplication::translate("MainWindow", "Run:", nullptr));
        runTime_label_3->setText(QCoreApplication::translate("MainWindow", "Decode:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
