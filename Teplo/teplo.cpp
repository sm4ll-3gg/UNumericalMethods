#include "teplo.h"
#include "ui_teplo.h"

#include <cmath>
#include <QDebug>
#include <QFontMetrics>

Teplo::Teplo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teplo),
    a(0), l(0), tau(0), n(0), h(0),
    currLayer(0)

{
    ui->setupUi(this);

    QTextBrowser* tb = ui->conditionText;
    int height = QFontMetrics(tb->font()).boundingRect(QRect(), tb->alignment(),
                                                       tb->toPlainText()).height();
    tb->setFixedHeight(height+25);

    connect(ui->graph, &Diagram::prevLayerRequest, this, &Teplo::showPrevLayer);
    connect(ui->graph, &Diagram::nextLayerRequest, this, &Teplo::showNextLayer);
}

Teplo::~Teplo()
{
    delete ui;
}

void Teplo::on_calculateButton_clicked()
{
    if(!isInputDataValid()) return;

    matrix.clear();
    currLayer = 0;

    a = ui->aEdit->text().toDouble();
    l = ui->lEdit->text().toDouble();
    tau = ui->tauEdit->text().toDouble();
    n = ui->pointCount->text().toInt();

    h = l/(n-1);

    calculateNullLayer();
    ui->graph->showLayer(matrix[0], h, 0);
}

bool Teplo::isInputDataValid()
{
    bool isValid = true;

    if(ui->aEdit->text() <= 0)
    {
        isValid = false;
        ui->aEdit->setText("");
        ui->aEdit->setPlaceholderText("Данные не корректны");
    } else ui->aEdit->setPlaceholderText("");

    if(ui->lEdit->text().toDouble() < 3)
    {
        isValid = false;
        ui->lEdit->setText("");
        ui->lEdit->setPlaceholderText("Данные не корректны");
    } else ui->lEdit->setPlaceholderText("l");

    if(ui->tauEdit->text().toDouble() <= 0)
    {
        isValid = false;
        ui->tauEdit->setText("");
        ui->tauEdit->setPlaceholderText("Данные не корректны");
    } else ui->tauEdit->setPlaceholderText("tau");

    if(ui->pointCount->text().toInt() < 3)
    {
        isValid = false;
        ui->pointCount->setText("");
        ui->pointCount->setPlaceholderText("Данные не корректны");
    } else ui->pointCount->setPlaceholderText("n");

    return isValid;
}

void Teplo::calculateNullLayer()
{
    Layer layer;

    for(int i = 0; i < n; ++i)
    {
        double xi = h*i;
        double d = 4 * sin(2*M_PI*xi) * pow(cos(M_PI*xi), 2);
        layer.push_back(d);
    }

    matrix.push_back(layer);
}

void Teplo::calculateNextLayer()
{
    Layer next{0};
    double lambda = a * tau / pow(h, 2);

    for(int i = 1; i < n - 1; ++i)
    {
        Layer uj = *std::prev(matrix.end());
        next.push_back(lambda * uj[i + 1] + (1 - 2*lambda) * uj[i] + lambda * uj[i - 1]);
    }
    next.push_back(0);

    matrix.push_back(next);
}

void Teplo::showPrevLayer()
{
    if(currLayer == 0)
        return;

    currLayer--;

    ui->graph->showLayer(matrix[currLayer], h, currLayer);
}

void Teplo::showNextLayer()
{
    if(matrix.size() >= ++currLayer)
        calculateNextLayer();

    ui->graph->showLayer(matrix[currLayer], h,currLayer);
}
