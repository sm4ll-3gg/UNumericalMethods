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
    ui->tabWidget->addTab(gaussWidget, "Метод Жордана-Гаусса");

    Teplo* teploWidget = new Teplo;
    ui->tabWidget->addTab(teploWidget, "Уравнение теплопроводности");

    Voln* volnWidget = new Voln;
    ui->tabWidget->addTab(volnWidget, "Волновое уравнение");

    ui->tabWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


