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

    Matrix          addColumnToMatrix();

    int             getMainColumn();
    // Меняет местами первую строку, со строкой с
    // ненулевым первым элементом
    void            setMainRow();
    void            divideCurrRowOnConst(const int k);
    void            subtractCurrRowFromRest();
    void            makeUpperTriangularMatrix();

    void            subtractRowFromRest(int row);
    void            makeEMatrixFromUT();
    void            step();

    void            reset();

private:
    Ui::Gauss *ui;

    Matrix          matrix;

    int             rowCount;

    int             currColumnIndex;
    int             currRowIndex;
};

#endif // GAUSS_H
