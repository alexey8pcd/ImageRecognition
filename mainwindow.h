#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtGui"
#include "QFileDialog"
#include "pyramid.h"
#include "interestpointsdetector.h"
#include "datatypes.h"
#include <algorithm>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_bLoadImage_clicked();
        void on_bSobelX_clicked();
        void on_bSobelY_clicked();
        void on_bSobelXY_clicked();
        void on_sliderRadius_valueChanged(int value);
        void on_bGauss_clicked();
        void on_bOctaves_clicked();

        void on_bMoravec_clicked();

        void on_sliderThreshold_valueChanged(int value);

        void on_bHarris_clicked();

        void on_chbFilter_clicked();

    private:
        QImage original;
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
