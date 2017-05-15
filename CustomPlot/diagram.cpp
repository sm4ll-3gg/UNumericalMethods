#include "diagram.h"
#include "ui_diagram.h"

#include "qcustomplot.h"

Diagram::Diagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diagram)
{
    ui->setupUi(this);

    ui->diagram->setInteraction(QCP::iRangeZoom);
}

Diagram::~Diagram()
{
    delete ui;
}

void Diagram::showLayer(const Layer& layer, double h, int index)
{
    ui->diagram->clearGraphs();

    QVector<double> keys;
    for(int i = 0; i < layer.size(); ++i)
        keys.push_back(i*h);

    ui->currLayer->setText("Текущий слой: " + QString::number(index));

    ui->diagram->addGraph()->addData(keys, layer);

    ui->diagram->rescaleAxes();
    ui->diagram->replot();
}

void Diagram::on_prevButton_clicked()
{
    emit prevLayerRequest();
}

void Diagram::on_nextButton_clicked()
{
    emit nextLayerRequest();
}
