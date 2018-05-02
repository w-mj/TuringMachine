#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QObject>

class Block : public QWidget
{
    Q_OBJECT

public:
    Block(QWidget *parent, QString code, QString* reader);
    Block(Block& another) = default;
    Block& operator =(Block& another) = default;

    void paintEvent(QPaintEvent *event);
    void changeState(char code);
    void setReaderState(QString* readerState);

    void select(bool s);


    ~Block();

private:
    QString *reader;
    QString code;

    bool selected = false;
};

#endif // BLOCK_H
