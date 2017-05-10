#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gauss.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Gauss* gaussWidget = new Gauss;
    ui->tabWidget->addTab(gaussWidget, "Первая");
}

MainWindow::~MainWindow()
{
    delete ui;
}


