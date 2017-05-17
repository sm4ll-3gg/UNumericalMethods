#include "voln.h"
#include "ui_voln.h"

#include "Gauss/gauss.h"

#include <cmath>
#include <QDebug>
#include <QFontMetrics>

Voln::Voln(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Voln),
    c(0), l(0), tau(0), n(0), h(0),
    currLayer(0)
{
    ui->setupUi(this);

    QTextBrowser* tb = ui->conditionText_2;
    int height = QFontMetrics(tb->font()).boundingRect(QRect(), tb->alignment(),
                                                       tb->toPlainText()).height();
    tb->setFixedHeight(height+25);

    connect(ui->graph_2, &Diagram::prevLayerRequest, this, &Voln::showPrevLayer);
    connect(ui->graph_2, &Diagram::nextLayerRequest, this, &Voln::showNextLayer);
}

Voln::~Voln()
{
    delete ui;
}

void Voln::on_calculateButton_clicked()
{
    if(!isInputDataValid()) return;

    matrix.clear();
    currLayer = 0;

    c = ui->cEdit->text().toDouble();
    l = ui->lEdit->text().toDouble();
    tau = ui->tauEdit->text().toDouble();
    n = ui->pointCount->text().toInt();

    h = l/(n-1);

    calculateNullLayer();
    calculateFirstLayer();

    ui->graph_2->showLayer(matrix[0], h, 0);
}

bool Voln::isInputDataValid()
{
    bool isValid = true;

    if(ui->cEdit->text() <= 0)
    {
        isValid = false;
        ui->cEdit->setText("");
        ui->cEdit->setPlaceholderText("Данные не корректны");
    } else ui->cEdit->setPlaceholderText("");

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

void Voln::calculateNullLayer()
{
    Layer layer(n);
    // fi(x) = 0
    //std::generate(layer.begin(), layer.end, [this, &i](){ return sin((i++)*h);} );
    for(int i = 0; i < n; ++i)
    {
        layer[i] = sin(i*h);
    }

    //std::generate(layer.begin(), layer.end(), [](){ return 0; });

    matrix.push_back(layer);
}

void Voln::calculateFirstLayer()
{
    Layer layer(n);

    for(int i = 0; i < n; ++i)
    {
        double xi = i*h;
        layer[i] = tau * sin(2*M_PI*xi) * pow( cos(M_PI*xi), 2) -
                   pow(sin(M_PI*xi), 2) * sin(2*M_PI*xi);
    }

    matrix.push_back(layer);
}

void Voln::calculateNextLayer()
{
    auto fst = *(matrix.end() - 1);
    auto null = *(matrix.end() - 2);

    double lambda = pow(c * tau / h, 2);

    QVector<double> next(n);
    next[0] = 0;
    next[n - 1] = 0;
    for(int i = 1; i < n - 1; ++i)
    {
        next[i] = 2*(1 - lambda)*fst[i] + lambda*(fst[i+1] + fst[i-1]) - null[i];
    }

    matrix.push_back(next);
}

void Voln::showPrevLayer()
{
    if(currLayer == 0)
        return;

    currLayer--;

    ui->graph_2->showLayer(matrix[currLayer], h, currLayer);
}

void Voln::showNextLayer()
{
    if(matrix.size() == ++currLayer)
        calculateNextLayer();

    ui->graph_2->showLayer(matrix[currLayer], h,currLayer);
}
