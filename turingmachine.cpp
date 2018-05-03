#include "turingmachine.h"
#include <QDebug>
#include "block.h"

TuringMachine::TuringMachine(QSet<QString> &reader_states_set,
                             QSet<QString> &tape_sign_set,
                             QString B,
                             QSet<QString> &input_sign_set,
                             QSet<QString> &F,
                             QString q0,
                             QStringList functions):
    QObject(nullptr),
    reader_states(reader_states_set), tape_signs(tape_sign_set), B(B),
    input_signs(input_sign_set), F(F), q0(q0)
{
    if (reader_states.intersects(tape_signs)) {
        throw 0;
    } else if (!tape_signs.contains(B)) {
        throw 1;
    } else if (input_signs.subtract(tape_signs).size() > 0) {
        throw 2;
    } else if (F.subtract(reader_states).size() > 0) {
        throw 3;
    } else if (!reader_states.contains(q0)) {
        throw 4;
    }
    state = q0;
    layout = new QHBoxLayout();
    for (QString f: functions) {
        QStringList l = f.split('=');
        function.insert(l[0], l[1]);
    }
}

QHBoxLayout *TuringMachine::init_tape(QString tape_s)
{
    layout->addStretch();
    QStringList tape_list = maximumMatching(tape_s);
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

void TuringMachine::__run(int step)
{
    while(step--) {
        QString tape_content = (*current_pos)->getContent();
        QString func_index = state + "," + tape_content;
        if (! function.contains(func_index)) {
            if (F.contains(state))
                emit correctTape();
            else
                emit wrongTape();
            break;
        }
        const QStringList& transform = function.find(func_index)->split(",");
        (*current_pos)->setContent(transform[1]);
        state = transform[0];
        if(transform[2] == "R")
            goRight();
        else if (transform[2] == "L")
            goLeft();
    }
}

void TuringMachine::step()
{
    __run(1);
}

void TuringMachine::run()
{
    __run(-1);
}

int TuringMachine::size()
{
    return tape.size();
}

int TuringMachine::reader_position()
{
    // qDebug() << current_pos_i << '/' << size();
    return current_pos_i;
}

TuringMachine::~TuringMachine()
{
    delete layout;
    for (auto b: tape)
        delete b;
}

QStringList TuringMachine::maximumMatching(QString str)
{
    int max_l = 0;
    for (QString s: tape_signs) max_l = std::max(max_l, s.size());
    QStringList ret;
    for (int i = 0; i < str.size();){
        int c = max_l;
        for (; c > 0; c--) {
            if (tape_signs.contains(str.mid(i, c))) {
                ret.append(str.mid(i, c));
                i += c;
                break;
            }
        }
        if (c == 0)
            i++;
    }
    return ret;
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
