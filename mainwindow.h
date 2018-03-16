#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QThread>

#include "ProcessingText.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void _addButtonClear();
    void _startThread();
    void _stopThread();

    Ui::MainWindow *ui;
    QPushButton *button;
    QThread *thread;
    ProcessingText *textProcessing;

};

#endif // MAINWINDOW_H
