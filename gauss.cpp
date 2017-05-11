#include "gauss.h"
#include "ui_gauss.h"

#include <math.h>
#include <QVariant>
#include <QDebug>

Gauss::Gauss(QWidget *parent)
    :QWidget(parent),
      ui(new Ui::Gauss),
      rowCount(0),
      currColumnIndex(-1),
      currRowIndex(0)
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
        QTableWidgetItem* item = m->item(i, 0);

        if(item)
            column[i] = item->data(Qt::DisplayRole).toDouble();
        else
            column[i] = 0;
    }

    return column;
}

Gauss::Matrix Gauss::addColumnToMatrix()
{
    Matrix m = getMatrix();
    QVector<double> c = getColumn();

    for(int i = 0; i < m.size(); ++i)
    {
        m[i].push_back( c[i] );
    }

    return m;
}

int Gauss::getMainColumn()
{
    // Столбец свободных членов не учитывается
    for(int i = 0; i < rowCount; ++i)
    {
        bool isNullColumn = true;
        for(int j = 0; j < rowCount; ++j)
        {
            if(matrix[j][i] != 0)
            {
                isNullColumn = false;
                break;
            }
        }

        if(!isNullColumn) return i;
    }

    return -1;
}

void Gauss::setMainRow()
{
    for(int i = 0; i < rowCount; ++i)
    {
        if(matrix[i][currColumnIndex] != 0)
        {
            if(i == 0) return;

            std::swap(matrix[0], matrix[i]);
            return;
        }
    }
}

void Gauss::divideCurrRowOnConst(const int k)
{
    std::for_each(matrix[currRowIndex].begin(), matrix[currRowIndex].end(),
                  [ k ](double& elm) { elm /= k; } );
}

void Gauss::subtractCurrRowFromRest()
{
    std::for_each(matrix.begin() + currRowIndex + 1, matrix.end(),
                  [ this ](QVector<double>& curr)
    {
        int k = curr[currColumnIndex];
        for(int i = 0; i < curr.size(); ++i)
        {
            curr[i] -= matrix[currRowIndex][i] * k;
        }
    });

}

void Gauss::makeUpperTriangularMatrix()
{
    for(int i = 0; i < matrix.size() - 1; ++i)
    {
        step();

        currColumnIndex++;
        currRowIndex++;
    }
}

void Gauss::subtractRowFromRest(int row)
{
    QVector<double> curr = matrix[row];
    int size = curr.size();

    int koef = 0;
    for(int i = 0; i < row; ++i)
    {
        QVector<double>& target = matrix[i];

        qDebug() << i << " " << row << " " << target[row] << " " << matrix[i][row];
        koef = target[row];
        qDebug() << koef;

        target[ size - 1 ] -= curr[size - 1] * target[row];
        target[row] -= curr[row] * target[row];
    }
}

void Gauss::makeEMatrixFromUT()
{
    for(int i = rowCount - 1; i > 0; --i)
    {
        subtractRowFromRest(i);
    }
}

void Gauss::step()
{
    int k = matrix[currRowIndex][currColumnIndex];
    divideCurrRowOnConst(k);

    subtractCurrRowFromRest();
    qDebug() << matrix;
}

void Gauss::reset()
{
    matrix.clear();

    currColumnIndex = -1;
}


void Gauss::on_matrixSizeSpin_valueChanged(int count)
{
    ui->conditionTableWidget->setRowCount(count);
    ui->conditionTableWidget->setColumnCount(count);

    ui->conditionColumnWidget->setRowCount(count);
}

void Gauss::on_calculateButton_clicked()
{
    matrix = addColumnToMatrix();
    rowCount = matrix.size();
    currColumnIndex = getMainColumn();

    if(currColumnIndex == - 1)
    {
        ui->answerField->setText("Решений нет!");
        return;
    }

    setMainRow();

    makeUpperTriangularMatrix();
    makeEMatrixFromUT();

    qDebug() << matrix;

    reset();
}
