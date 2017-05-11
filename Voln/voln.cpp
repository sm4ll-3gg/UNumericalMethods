#include "voln.h"
#include "ui_voln.h"

Voln::Voln(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Voln)
{
    ui->setupUi(this);
}

Voln::~Voln()
{
    delete ui;
}
