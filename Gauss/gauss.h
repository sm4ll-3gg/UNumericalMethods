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

    using Matrix = QVector<QVector<double>>;

public:
    explicit Gauss(QWidget *parent = 0);
    ~Gauss();

private slots:
    void on_matrixSizeSpin_valueChanged(int count);
    void on_calculateButton_clicked();

private: // Methods
    Matrix          getMatrix();
    QVector<double> getColumn();

    Matrix          addColumnToMatrix();
    Matrix          addColumnToMatrix(Matrix&& matrix, QVector<double>&& column);

    int             getMainColumn();
    // Меняет местами первую строку, со строкой с
    // ненулевым первым элементом
    void            setMainRow();
    void            divideCurrRowOnConst(const double k);
    void            subtractCurrRowFromRest();
    void            calculateReuslt();

    void            subtractRowFromRest(int row);
    void            step();

    QVector<double> getAnswer();

    void            reset();

    void            printStep();

private:
    Ui::Gauss *ui;

    Matrix          matrix;

    int             rowCount;

    int             currColumnIndex;
    int             currRowIndex;

    QString         message;
};

#endif // GAUSS_H
