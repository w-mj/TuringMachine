#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "block.h"
#include "turingmachine.h"
#include <QHBoxLayout>
#include <QScrollBar>
#include <QSet>
#include <QDebug>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scroll->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scroll->setWidgetResizable(true);
    QSet<QString> states;
    QSet<QString> signs;
    QString B = "B";
    QSet<QString> input_signs;
    QSet<QString> F;
    QString q0 = "q0";
    states << "q1" << "q0";
    signs << "A" << "B";
    input_signs << "A";
    F << "q1";
    turing_machine = new TuringMachine(states, signs, B, input_signs, F, q0);
    QHBoxLayout* l = turing_machine ->init_tape("A B A B A A A A A A A A A A A A A A");
    ui->scrollAreaWidgetContents->setLayout(l);
    connect(ui->go_left, &QPushButton::clicked, [&](){
        turing_machine->goLeft();
        this->updateScrollBar();
    });
    connect(ui->go_right, &QPushButton::clicked, [&](){
        turing_machine->goRight();
        this->updateScrollBar();
    });

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScrollBar()
{
    QScrollBar* bar = ui->scroll->horizontalScrollBar();
    int p = turing_machine->reader_position();
    int s = turing_machine->size();
    float k = p == s - 1? 1: 1.0 * p / s;
    int minn = bar->minimum();
    int maxx = bar->maximum();
    int v = !k?0:k * (maxx - minn) + minn;
    bar->setValue(v);
}
