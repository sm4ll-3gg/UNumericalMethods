#include "gauss.h"
#include "ui_gauss.h"
#include "gaussstep.h"

#include <math.h>
#include <QVariant>
#include <QDebug>
#include <QLabel>

Gauss::Gauss(QWidget *parent)
    :QWidget(parent),
      ui(new Ui::Gauss),
      rowCount(0),
      currColumnIndex(-1),
      currRowIndex(0)
{
    ui->setupUi(this);

    ui->solutionLabel->hide();
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
    for(int j = currRowIndex + 1; j < matrix.size(); ++j)
    {
        QVector<double>& curr = matrix[j];

        int k = curr[currColumnIndex];
        for(int i = 0; i < curr.size(); ++i)
        {
            curr[i] -= matrix[currRowIndex][i] * k;
        }

        message += "Вычтем из строки " + QString::number(j+1) + " строку " +
                QString::number(currRowIndex+1) + ", умноженную на " +
                QString::number(k) + ";\n";
    }
}

void Gauss::calculate()
{
    for(int i = 0; i < matrix.size(); ++i)
    {
        step();

        currColumnIndex++;
        currRowIndex++;

        printStep();
    }

    for(int i = rowCount - 1; i > 0; --i)
    {
        subtractRowFromRest(i);

        printStep();
    }
}

void Gauss::subtractRowFromRest(int row)
{
    QVector<double> curr = matrix[row];
    int size = curr.size();

    for(int i = 0; i < row; ++i)
    {
        QVector<double>& target = matrix[i];

        double k = target[row];

        target[ size - 1 ] -= curr[size - 1] * k;
        target[row] -= curr[row] * k;

        message += "Вычтем из строки " + QString::number(i+1) + " строку " +
                QString::number(row+1) + ", умноженную на " +
                QString::number(k) + ";\n";
    }
}

void Gauss::step()
{
    int k = matrix[currRowIndex][currColumnIndex];
    divideCurrRowOnConst(k);

    message += "Разделим строку " + QString::number(currRowIndex+1) +
            " на " + QString::number(k) + ".\n";

    subtractCurrRowFromRest();
}

void Gauss::reset()
{
    matrix.clear();

    rowCount = 0;
    currColumnIndex = -1;
    currRowIndex = 0;

    while(QLayoutItem* item = ui->solutionLayout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }
}

void Gauss::printStep()
{
    GaussStep* stepWidget = new GaussStep(matrix, message);
    ui->solutionLayout->addWidget(stepWidget);

    message.clear();
}


void Gauss::on_matrixSizeSpin_valueChanged(int count)
{
    ui->conditionTableWidget->setRowCount(count);
    ui->conditionTableWidget->setColumnCount(count);
    ui->conditionTableWidget->setMinimumSize(count*61, count*61);

    ui->conditionColumnWidget->setRowCount(count);
    ui->conditionColumnWidget->setMinimumHeight(count*61);
}

void Gauss::on_calculateButton_clicked()
{
    reset();

    matrix = addColumnToMatrix();
    qDebug() << matrix;
    rowCount = matrix.size();
    currColumnIndex = getMainColumn();

    if(currColumnIndex == - 1)
    {
        QLabel* lbl = new QLabel("Решений нет!");
        ui->srcLayout->addWidget(lbl);
        return;
    }

    ui->solutionLabel->setHidden(false);

    setMainRow();
    calculate();
}
