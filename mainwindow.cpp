#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _addButtonClear();
    thread = new QThread(this);
    textProcessing = new ProcessingText(this);
    _startThread();
}

void MainWindow::_addButtonClear()
{
    button = new QPushButton(this);
    button->setText("Clear");
    ui->horizontalLayout_2->insertWidget(1, button);
    connect(button, SIGNAL(clicked()), ui->textBar, SLOT(clear()));
    connect(button, SIGNAL(clicked()), ui->textBrowser, SLOT(clear()));
}

void MainWindow::_startThread()
{
    textProcessing->moveToThread(thread);
    connect(ui->textBar, SIGNAL(textChanged(QString)), textProcessing, SLOT(textChanged(QString)));
    connect(textProcessing, SIGNAL(dataReady(QString)), ui->textBrowser, SLOT(setText(QString)));
    connect(thread, SIGNAL(started()), textProcessing, SLOT(process()));
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete button;
    _stopThread();
    delete textProcessing;
}


void MainWindow::_stopThread()
{
    textProcessing->stopProcessing();
    thread->quit();
}
