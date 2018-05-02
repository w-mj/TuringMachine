#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "turingmachine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_init_button_clicked();

private:
    Ui::MainWindow *ui;
    void updateScrollBar();

    TuringMachine* turing_machine = nullptr;
};

#endif // MAINWINDOW_H
