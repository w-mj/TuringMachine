#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "block.h"
#include "turingmachine.h"
#include <QHBoxLayout>
#include <QSet>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scroll->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scroll->setWidgetResizable(true);
    // ui->layout->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    QSet<QString> states;
    QSet<QString> signs;
    QString B = "B";
    QSet<QString> input_signs;
    QSet<QString> F;
    QString q0 = "q0";
    states << "q1" << "q0";
    signs << "A" << "B";
    input_signs << "A" << "C";
    F << "q1";
    TuringMachine* t = new TuringMachine(states, signs, B, input_signs, F, q0);
    QHBoxLayout* l = t->init_tape("A B A B");
    ui->scrollAreaWidgetContents->setLayout(l);
//    QString* reader = new QString("#");
//    for(int i = 0; i < 100; i++) {
//        Block *b = new Block(nullptr, "A", reader);
//        ui->layout->addWidget(b);
//    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
