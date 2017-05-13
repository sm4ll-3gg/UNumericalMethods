#include "teplo.h"
#include "ui_teplo.h"

#include <cmath>
#include <QDebug>

Teplo::Teplo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teplo),
    l(0),
    n(0),
    tau(0),
    h(0)
{
    ui->setupUi(this);
}

Teplo::~Teplo()
{
    delete ui;
}

void Teplo::on_calculateButton_clicked()
{
    if(!isInputDataValid()) return;

    l = 3; //ui->l->text().toDouble();
    n = ui->plotCount->text().toInt();
    tau = ui->tau->text().toDouble();

    h = l/n;

    qDebug() << "l = " << l
             << "; n = " << n
             << "; tau = " << tau
             << "; h = " << h << ";";

    calculateNullLayer();


}

bool Teplo::isInputDataValid()
{
    bool isValid = true;

    //    if(ui->l->text().toDouble() < 3)
    //    {
    //        isValid = false;
    //        ui->l->setText("");
    //        ui->l->setPlaceholderText("Данные не корректны");
    //    } else ui->l->setPlaceholderText("l");

    if(ui->plotCount->text().toInt() < 3)
    {
        isValid = false;
        ui->plotCount->setText("");
        ui->plotCount->setPlaceholderText("Данные не корректны");
    } else ui->plotCount->setPlaceholderText("n");

    if(ui->tau->text().toDouble() <= 0)
    {
        isValid = false;
        ui->tau->setText("");
        ui->tau->setPlaceholderText("Данные не корректны");
    } else ui->tau->setPlaceholderText("tau");

    return isValid;
}

void Teplo::calculateNullLayer()
{
    Layer layer;

    for(int i = 0; i < n; ++i)
    {
        float xi = h*i;
        float d = 4 * sin(2*M_PI*xi) * pow(cos(M_PI*xi), 2);
        layer.push_back(d);
    }

    matrix.push_back(layer);
}

void Teplo::calculateNextLayer()
{
    Layer next{0};
    float lambda = sqrt(6) * tau / pow(h, 2);

    for(int i = 1; i < n - 1; ++i)
    {
        Layer uj = matrix.last();
        next.push_back(lambda * uj[i + 1] + (1 - 2*lambda) * uj[i] + lambda * uj[i - 1]);
    }
    next.push_back(0);

    matrix.push_back(next);
    //    std::generate_n(next.begin(), n, [this, lambda]()
    //    {
    //        return;
    //    });
}

void Teplo::on_pushButton_clicked()
{
    calculateNextLayer();
}

void Teplo::on_pushButton_2_clicked()
{
    for(int j = 0; j < matrix.size(); ++j)
    {
        QString layer = "";
        for(int i = 0; i < n; ++i)
        {
            layer += QString::number(matrix[j][i], 'f', 2) + "; ";
        }
        qDebug() << layer;
    }
}
