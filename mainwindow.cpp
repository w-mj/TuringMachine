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

    ui->state_set_input->setText("q1 q0");
    ui->sign_set_input->setText("A B");
    ui->B_input->setText("B");
    ui->input_set_input->setText("A");
    ui->F_set_input->setText("q1");
    ui->q0_input->setText("q0");

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

void MainWindow::on_init_button_clicked()
{
    QString state_str = ui->state_set_input->text();
    QString sign_str = ui->sign_set_input->text();
    QString B_str = ui->B_input->text();
    QString input_str = ui->input_set_input->text();
    QString F_str = ui->F_set_input->text();
    QString q0_str = ui->q0_input->text();

    QSet<QString> state_set = state_str.split(' ').toSet();
    QSet<QString> sign_set = sign_str.split(' ').toSet();
    QSet<QString> input_set = input_str.split(' ').toSet();
    QSet<QString> F_set = F_str.split(' ').toSet();

    if (turing_machine != nullptr)
        delete turing_machine;
    turing_machine = new TuringMachine(state_set, sign_set, B_str, input_set, F_set, q0_str);
    QLayout* layout = turing_machine->init_tape(ui->tape_input->text());
    ui->scrollAreaWidgetContents->setLayout(layout);
}
