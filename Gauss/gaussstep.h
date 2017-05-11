#ifndef GAUSSSTEP_H
#define GAUSSSTEP_H

#include <QWidget>
#include <QVector>

namespace Ui {
class GaussStep;
}

class GaussStep : public QWidget
{
    typedef QVector<QVector<double>> Matrix;

    Q_OBJECT

public:
    explicit GaussStep(const Matrix& matrix,
                       const QString& message, QWidget *parent = 0);
    ~GaussStep();

private: // Methods
    void    setMatrix(const Matrix& matrix);
    void    setColumn(const Matrix& matrix);

private:
    Ui::GaussStep *ui;
};

#endif // GAUSSSTEP_H
