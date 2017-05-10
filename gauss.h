#ifndef GAUSS_H
#define GAUSS_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Gauss;
}

class Gauss : public QWidget
{
    Q_OBJECT

public:
    explicit Gauss(QWidget *parent = 0);
    ~Gauss();

private slots:
    void on_matrixSizeSpin_valueChanged(int count);

    void on_calculateButton_clicked();

private: // Methods
    typedef QVector<QVector<double>> Matrix;

    Matrix          getMatrix();
    QVector<double> getColumn();

    double          determinant();
    double          calculateDet(const Matrix &matrix);
    Matrix          getSubmatrix(const Matrix &matrix, int index);

private:
    Ui::Gauss *ui;

    Matrix          matrix;
    QVector<double> column;
};

#endif // GAUSS_H
