#ifndef TEPLO_H
#define TEPLO_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Teplo;
}

class Teplo : public QWidget
{
    using Matrix = QVector<QVector<double>>;
    using Layer = QVector<double>;

    Q_OBJECT

public:
    explicit Teplo(QWidget *parent = 0);
    ~Teplo();

private slots:
    void on_calculateButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private: // Methods
    bool    isInputDataValid();

    void    calculateNullLayer();
    void    calculateNextLayer();

private:
    Ui::Teplo *ui;

    // Входные значения
    double  l; // Длина струны
    int     n; // Количество точек на отрезке
    double  tau; // Шаг по времени

    double  h; // Шаг длине

    // Матрица n*m, где n - кол-во слоев, а m - кол-во участков
    Matrix  matrix;
};

#endif // TEPLO_H
