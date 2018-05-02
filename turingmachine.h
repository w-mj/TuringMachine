#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QHBoxLayout>
#include <QSet>
#include <QLinkedList>
#include "block.h"

class TuringMachine
{
public:
    explicit TuringMachine(QSet<QString> &reader_states_set,
                  QSet<QString> &tape_sign_set,
                  QString B,
                  QSet<QString> &input_sign_set,
                  QSet<QString> &F,
                  QString q0);

    QHBoxLayout* init_tape(QString tape_s);

    ~TuringMachine();

private:
    QHBoxLayout* layout = nullptr;
    QSet<QString> reader_states;
    QSet<QString> tape_signs;
    QString B;
    QSet<QString> input_signs;
    QSet<QString> F;
    QString q0;  // init state

    QString state;
    int reader_pos = -1;
    QLinkedList<Block*> tape;
};

#endif // TURINGMACHINE_H
