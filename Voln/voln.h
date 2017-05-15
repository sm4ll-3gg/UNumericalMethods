#ifndef VOLN_H
#define VOLN_H

#include <QWidget>

namespace Ui {
class Voln;
}

class Voln : public QWidget
{
    using Matrix = QVector<QVector<double>>;
    using Layer = QVector<double>;

    Q_OBJECT

public:
    explicit Voln(QWidget *parent = 0);
    ~Voln();

private slots:
    void    on_calculateButton_clicked();

    void    showPrevLayer();
    void    showNextLayer();

private: // Methods
    bool    isInputDataValid();

    void    calculateNullLayer();
    void    calculateFirstLayer();
    void    calculateNextLayer();

private:
    Ui::Voln *ui;

    // Входные значения
    double  c;
    double  l; // Длина струны
    double  tau; // Шаг по времени
    int     n; // Количество точек на отрезке

    double  h; // Шаг по длине

    int     currLayer;

    // Матрица n*m, где n - кол-во слоев, а m - кол-во участков
    Matrix  matrix;
};

#endif // VOLN_H
