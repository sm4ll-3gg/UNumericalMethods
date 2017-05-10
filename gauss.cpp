#include "gauss.h"
#include "ui_gauss.h"

#include <math.h>
#include <QVariant>

Gauss::Gauss(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gauss)
{
    ui->setupUi(this);
}

Gauss::~Gauss()
{
    delete ui;
}

QVector<QVector<double>> Gauss::getMatrix()
{
    QTableWidget* m = ui->conditionTableWidget;
    int size = m->rowCount();
    Matrix matrix(size, QVector<double>(size));

    for(int i = 0; i < m->rowCount(); ++i)
        for(int j = 0; j < m->columnCount(); ++j)
        {
            QTableWidgetItem* item = m->item(i,j);

            if(item)
                matrix[i][j] = item->data(Qt::DisplayRole).toDouble();
            else
                matrix[i][j] = 0.0;
        }

    return matrix;
}

QVector<double> Gauss::getColumn()
{
    QTableWidget* m = ui->conditionColumnWidget;
    int size = m->rowCount();
    QVector<double> column(size);

    for(int i = 0; i < size; ++i)
    {
        QTableWidgetItem* item = m->item(0, i);

        if(item)
            column[i] = item->data(Qt::DisplayRole).toDouble();
        else
            column[i] = 0;
    }

    return column;
}

double Gauss::determinant()
{
    if(matrix.isEmpty())
        return 0;

    return calculateDet(matrix);
}

double Gauss::calculateDet(const Matrix& matrix)
{
    if(matrix.size() == 2)
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

    double result = 0;
    for(int i = 0; i < matrix.size(); ++i)
    {
        if(matrix[0][i] != 0)
        {
            result += pow(-1, i+2) * matrix[0][i] * calculateDet( getSubmatrix(matrix, i) );
        }
    }

    return result;
}

Gauss::Matrix Gauss::getSubmatrix(const Gauss::Matrix &matrix, int index)
{
    int size = matrix.size();
    Matrix m(size - 1, QVector<double>(size - 1));

    for(int i = 1; i < size; ++i)
    {
        for(int j = 0, t = 0; j < size; ++j, ++t)
        {
            if(j != index)
            {
                m[i - 1][t] = matrix[i][j];
            }
            else t--;
        }
    }

    return m;
}


void Gauss::on_matrixSizeSpin_valueChanged(int count)
{
    ui->conditionTableWidget->setRowCount(count);
    ui->conditionTableWidget->setColumnCount(count);

    ui->conditionColumnWidget->setRowCount(count);
}

void Gauss::on_calculateButton_clicked()
{
    matrix = getMatrix();

    ui->answerField->setText( QString::number(determinant()) );
}
