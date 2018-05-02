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
    TuringMachine* t = new TuringMachine(states, signs, B, input_signs, F, q0);
    QHBoxLayout* l = t->init_tape("A B A B A");
    ui->scrollAreaWidgetContents->setLayout(l);

    connect(ui->go_left, &QPushButton::clicked, t, &TuringMachine::goLeft);
    connect(ui->go_right, &QPushButton::clicked, t, &TuringMachine::goRight);
}
MainWindow::~MainWindow()
{
    delete ui;
}
