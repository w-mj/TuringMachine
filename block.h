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

    void select(bool s);

    ~Block();


    QString getContent() const;
    void setContent(const QString &value);

private:
    QString *reader;
    QString content;

    bool selected = false;
};

#endif // BLOCK_H
