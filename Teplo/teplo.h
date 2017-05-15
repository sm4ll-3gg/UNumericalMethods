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
    void    on_calculateButton_clicked();

    void    showPrevLayer();
    void    showNextLayer();

private: // Methods
    bool    isInputDataValid();

    void    calculateNullLayer();
    void    calculateNextLayer();

private:
    Ui::Teplo *ui;

    // Входные значения
    double  a;
    double  l; // Длина струны
    double  tau; // Шаг по времени
    int     n; // Количество точек на отрезке

    double  h; // Шаг по длине

    int     currLayer;

    // Матрица n*m, где n - кол-во слоев, а m - кол-во участков
    Matrix  matrix;
};

#endif // TEPLO_H
