#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "block.h"
#include "turingmachine.h"
#include <QHBoxLayout>
#include <QScrollBar>
#include <QSet>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMessageBox>
#include <QFileDialog>

QString parseJsonStringList(const QJsonObject& json, const QString& name, char join = '\0') {
    QJsonArray a = json[name].toArray();
    QStringList result;
    for (QJsonValue v: a) {
        result.append(v.toString());
    }
    return result.join(join);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scroll->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scroll->setWidgetResizable(true);
    //connect(ui->go_left, &QPushButton::clicked, this, &MainWindow::updateScrollBar);
    //connect(ui->go_right, &QPushButton::clicked, this, &MainWindow::updateScrollBar);
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

void MainWindow::connect_turing_machine()
{
    //connect(ui->go_left, &QPushButton::clicked, turing_machine, &TuringMachine::goLeft);
    //connect(ui->go_right, &QPushButton::clicked, turing_machine, &TuringMachine::goRight);
    connect(ui->step_button, &QPushButton::clicked, turing_machine, &TuringMachine::step);
    connect(turing_machine, &TuringMachine::wrongTape, this, &MainWindow::wrongTape);
    connect(turing_machine, &TuringMachine::correctTape, this, &MainWindow::correctTape);
}

void MainWindow::disconnect_turing_machine()
{
    //disconnect(ui->go_left, &QPushButton::clicked, turing_machine, &TuringMachine::goLeft);
    //disconnect(ui->go_right, &QPushButton::clicked, turing_machine, &TuringMachine::goRight);
    disconnect(ui->step_button, &QPushButton::clicked, turing_machine, &TuringMachine::step);
    disconnect(turing_machine, &TuringMachine::wrongTape, this, &MainWindow::wrongTape);
    disconnect(turing_machine, &TuringMachine::correctTape, this, &MainWindow::correctTape);

}

void MainWindow::on_init_button_clicked()
{
    QString state_str = ui->state_set_input->text();
    QString sign_str = ui->sign_set_input->text();
    QString B_str = ui->B_input->text();
    QString input_str = ui->input_set_input->text();
    QString F_str = ui->F_set_input->text();
    QString q0_str = ui->q0_input->text();
    QString function_str = ui->function_box->toPlainText();

    QSet<QString> state_set = state_str.split(',').toSet();
    QSet<QString> sign_set = sign_str.split(',').toSet();
    QSet<QString> input_set = input_str.split(',').toSet();
    QSet<QString> F_set = F_str.split(',').toSet();
    QStringList function_set = function_str.split('\n');

    if (turing_machine != nullptr)
        delete turing_machine;
    try {
        turing_machine = new TuringMachine(state_set, sign_set, B_str, input_set, F_set, q0_str, function_set);
        connect_turing_machine();
        QLayout* layout = turing_machine->init_tape(ui->tape_input->text());
        ui->scrollAreaWidgetContents->setLayout(layout);
    } catch (int code) {
        QMessageBox::critical(this, "ERROR", msgs[code]);
        turing_machine = nullptr;
        disconnect_turing_machine();
    }

}

void MainWindow::on_import_button_clicked()
{
    QString path = QFileDialog::getOpenFileName(this);
    qDebug() << path;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "fail to open file";
    QByteArray data = file.readAll();
    file.close();

    QJsonObject json = QJsonDocument::fromJson(data).object();
    ui->state_set_input->setText(parseJsonStringList(json, "K", ','));
    ui->sign_set_input->setText(parseJsonStringList(json, "Gamma", ','));
    ui->B_input->setText(json["B"].toString());
    ui->input_set_input->setText(parseJsonStringList(json, "Sigma", ','));
    ui->F_set_input->setText(parseJsonStringList(json, "F", ','));
    ui->q0_input->setText(json["q0"].toString());
    ui->function_box->setText(parseJsonStringList(json, "function", '\n'));
    ui->tape_input->setText(json["test_tape"].toString());
}

void MainWindow::on_save_button_clicked()
{
    QString state_str = ui->state_set_input->text();
    QString sign_str = ui->sign_set_input->text();
    QString B_str = ui->B_input->text();
    QString input_str = ui->input_set_input->text();
    QString F_str = ui->F_set_input->text();
    QString q0_str = ui->q0_input->text();
    QString function_str = ui->function_box->toPlainText();

    QJsonObject obj;
    QJsonArray state = QJsonArray::fromStringList(state_str.split(','));
    QJsonArray sign = QJsonArray::fromStringList(sign_str.split(','));
    QJsonArray input = QJsonArray::fromStringList(input_str.split(','));
    QJsonArray F = QJsonArray::fromStringList(F_str.split(','));
    QJsonArray function = QJsonArray::fromStringList(function_str.split('\n'));
    obj.insert("K", state);
    obj.insert("Gamma", sign);
    obj.insert("B", B_str);
    obj.insert("Sigma", input);
    obj.insert("F", F);
    obj.insert("q0", q0_str);
    obj.insert("function", function);
    obj.insert("test_tape", ui->tape_input->text());

    QString name = QFileDialog::getSaveFileName(this);
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
        QMessageBox::critical(this, "Fail", msgs[7]);
    else
        file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
}

void MainWindow::wrongTape()
{
    QMessageBox::warning(this, "Wrong", msgs[5]);
}

void MainWindow::correctTape()
{
    QMessageBox::information(this, "Congratulations", msgs[6]);
}

void MainWindow::on_run_button_clicked()
{
    if (!turing_machine)
        return;
    QString text = ui->run_button->text();
    if (!text.compare("&run"))
        ui->run_button->setText("&stop");
    else
        ui->run_button->setText("&run");
    turing_machine->run();
}
