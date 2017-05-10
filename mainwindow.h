#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
    void on_matrixSizeSpin_valueChanged(int count);


private: // Methods
    typedef QVector<QVector<double>> Matrix;

    Matrix          getMatrix();
    QVector<double> getColumn();


private:
    Ui::MainWindow *ui;

    Matrix          matrix;
    QVector<double> column;
};

#endif // MAINWINDOW_H
