#include "gauss.h"
#include "ui_gauss.h"

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
