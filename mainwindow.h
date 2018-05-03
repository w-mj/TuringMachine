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
    void on_import_button_clicked();

    void on_save_button_clicked();

    void on_run_button_clicked();

public slots:
    void wrongTape();
    void correctTape();

private:
    Ui::MainWindow *ui;
    void updateScrollBar();
    void connect_turing_machine();
    void disconnect_turing_machine();

    QList<QString> msgs = {
        "状态集和符号集不能相交",
        "空白符必须在输入字符集中",
        "输入字符集必须是符号集的子集",
        "终止符必须是状态集的子集",
        "初始状态q0必须是状态集中的元素",
        "符号串不合法",
        "合法的符号串",
        "打开文件失败"
    };


    TuringMachine* turing_machine = nullptr;
};

#endif // MAINWINDOW_H
