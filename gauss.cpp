#include <mainwindow.h>
#include <ui_mainwindow.h>

#include <QVariant>

QVector<QVector<double>> MainWindow::getMatrix()
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

QVector<double> MainWindow::getColumn()
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
