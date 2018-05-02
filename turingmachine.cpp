#include "turingmachine.h"
#include <QDebug>

TuringMachine::TuringMachine(QSet<QString> &reader_states_set,
                             QSet<QString> &tape_sign_set,
                             QString B,
                             QSet<QString> &input_sign_set,
                             QSet<QString> &F,
                             QString q0):
    QObject(nullptr),
    reader_states(reader_states_set), tape_signs(tape_sign_set), B(B),
    input_signs(input_sign_set), F(F), q0(q0)
{
    if (reader_states.intersects(tape_signs)) {
        throw "state set can not intersects with sign set.";
    } else if (!tape_signs.contains(B)) {
        throw "B must be the element of input set.";
    } else if (input_signs.subtract(tape_signs).size() > 0) {
        throw "input sign set must be the subset of tape sign set.";
    } else if (F.subtract(reader_states).size() > 0) {
        throw "F set must be the subset of reader states set.";
    } else if (!reader_states.contains(q0)) {
        throw "initial state must be contained by reader states set.";
    }
    state = q0;
    layout = new QHBoxLayout();
}

QHBoxLayout *TuringMachine::init_tape(QString tape_s)
{
    layout->addStretch();
    QStringList tape_list = tape_s.split(' ');
    for (QStringList::iterator a = tape_list.begin(); a != tape_list.end(); a++ ) {
        if (tape_signs.find(*a) != tape_signs.end()) {
            Block* b = new Block(nullptr, *a, &state);
            layout->addWidget(b);
            tape.insert(tape.end(), b);
        }
    }
    current_pos = tape.begin();
    current_pos_i = 0;
    if (tape.begin() != tape.end())
        (*tape.begin())->select(true);
    layout->addStretch();
    return layout;
}

int TuringMachine::size()
{
    return tape.size();
}

int TuringMachine::reader_position()
{
    qDebug() << current_pos_i << '/' << size();
    return current_pos_i;
}

TuringMachine::~TuringMachine()
{
    delete layout;
    for (auto b: tape)
        delete b;
}

void TuringMachine::goLeft()
{
    if (current_pos != tape.begin()) {
        (*current_pos)->select(false);
        current_pos--;
        (*current_pos)->select(true);
        current_pos_i--;
    } else {
        (*current_pos)->select(false);
        Block* new_blank = new Block(nullptr, B, &state);
        tape.insert(tape.begin(), new_blank);
        layout->insertWidget(1, new_blank);
        current_pos = tape.begin();
        (*current_pos)->select(true);
    }
}

void TuringMachine::goRight()
{
    if ((current_pos + 1 )!= tape.end()) {
        (*current_pos)->select(false);
        current_pos++;
        (*current_pos)->select(true);
    } else {
        (*current_pos)->select(false);
        Block* new_blank = new Block(nullptr, B, &state);
        tape.insert(tape.end(), new_blank);
        layout->insertWidget(layout->count() - 1, new_blank);
        current_pos = tape.end() - 1;
        (*current_pos)->select(true);
    }
    current_pos_i++;
}
