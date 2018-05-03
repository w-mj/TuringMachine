#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QObject>
#include <QHBoxLayout>
#include <QSet>
#include <QMap>
#include <QLinkedList>
#include "block.h"

class TuringMachine: public QObject
{
    Q_OBJECT
public:
    explicit TuringMachine(QSet<QString> &reader_states_set,
                  QSet<QString> &tape_sign_set,
                  QString B,
                  QSet<QString> &input_sign_set,
                  QSet<QString> &F,
                  QString q0,
                  QStringList functions);

    QHBoxLayout* init_tape(QString tape_s);


    int size();
    int reader_position();

    ~TuringMachine();

private:
    QHBoxLayout* layout = nullptr;
    QSet<QString> reader_states;
    QSet<QString> tape_signs;
    QString B;
    QSet<QString> input_signs;
    QSet<QString> F;
    QString q0;  // state

    QString state;
    QLinkedList<Block*>::iterator current_pos;
    int current_pos_i = 0;
    QLinkedList<Block*> tape;

    QMap<QString, QString > function;

    QStringList maximumMatching(QString s);
    void __run(int step);




public slots:
    void goLeft();
    void goRight();
    void step();
    void run();

signals:
    void wrongTape();
    void correctTape();
    void illegal(QString tip);
};

#endif // TURINGMACHINE_H
