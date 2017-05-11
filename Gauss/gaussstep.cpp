#include "gaussstep.h"
#include "ui_gaussstep.h"

GaussStep::GaussStep(const Matrix &matrix, const QString &message, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GaussStep)
{
    ui->setupUi(this);
    ui->message->setText(message);

    setMatrix(matrix);
    setColumn(matrix);
}

GaussStep::~GaussStep()
{
    delete ui;
}

void GaussStep::setMatrix(const GaussStep::Matrix &matrix)
{
    int size = matrix.size();

    ui->tableWidget->setRowCount(size);
    ui->tableWidget->setColumnCount(size);

    ui->tableWidget->setMinimumSize( size*61, size*61 );

    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            QString data = QString::number( matrix[i][j] );
            QTableWidgetItem* item = new QTableWidgetItem(data);
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void GaussStep::setColumn(const GaussStep::Matrix &matrix)
{
    int size = matrix.size();
    ui->columnWidget->setRowCount( size );

    ui->tableWidget->setMinimumHeight(size*61);

    for(int i = 0; i < size; ++i)
    {
        QString data = QString::number(matrix[i][size]);
        QTableWidgetItem* item = new QTableWidgetItem(data);
        ui->columnWidget->setItem(i, 0, item);
    }
}
