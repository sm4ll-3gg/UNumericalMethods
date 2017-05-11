#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Gauss/gauss.h"
#include "Teplo/teplo.h"
#include "Voln/voln.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Gauss* gaussWidget = new Gauss;
    ui->tabWidget->addTab(gaussWidget, "Первая");

    Teplo* teploWidget = new Teplo;
    ui->tabWidget->addTab(teploWidget, "Вторая");

    Voln* volnWidget = new Voln;
    ui->tabWidget->addTab(volnWidget, "Третья");
}

MainWindow::~MainWindow()
{
    delete ui;
}


