#include "teplo.h"
#include "ui_teplo.h"

Teplo::Teplo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teplo)
{
    ui->setupUi(this);
}

Teplo::~Teplo()
{
    delete ui;
}
