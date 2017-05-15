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
    std::generate(layer.begin(), layer.end(), [](){ return 0; });

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
    Matrix m;
    QVector<double> column(n);

    auto fst = *(matrix.end() - 1);
    auto null = *(matrix.end() - 2);

    double lambda = pow(c * tau / h, 2);

    column.first() = 0;
    column.last() = 0;
    for(int i = 1; i < n - 1; ++i)
    {
        QVector<double> v(n);

        v[i - 1] = lambda;
        v[i] = -(1 + 2*lambda);
        v[i + 1] = lambda;

        m.push_back(v);

        column[i] = (1 + 2*lambda) * null[i] - lambda *
                    (null[i + 1] + null[i - 1]) - 2*fst[i];
    }

    Gauss gauss;
    Layer answer = gauss.calculate(std::move(m), std::move(column));

    std::for_each(answer.begin(), answer.end(), [](double d){qDebug() << d;});

    matrix.push_back(answer);
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
