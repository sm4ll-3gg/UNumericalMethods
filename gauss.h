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

private: // Methods
    typedef QVector<QVector<double>> Matrix;

    Matrix          getMatrix();
    QVector<double> getColumn();

private:
    Ui::Gauss *ui;

    Matrix          matrix;
    QVector<double> column;
};

#endif // GAUSS_H
