#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "machinedebugparam.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ProductConfig::writeFile("./test.json");
    ProductConfig machine;
    machine.readFile("./test.json");
    machine.printInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
