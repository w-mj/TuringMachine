#include "block.h"
#include <QPainter>

Block::Block(QWidget *parent, QString code_, QString* reader)
    : QWidget(parent), reader(reader), code(code_)
{
    this->setFixedSize(50, 100);
}

void Block::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (selected) {
        painter.drawLine(10, 0, 40, 0);
        painter.drawLine(10, 0, 10, 30);
        painter.drawLine(40, 0, 40, 30);
        painter.drawLine(0, 30, 25, 40);
        painter.drawLine(50, 30, 25, 40);
        painter.drawLine(0, 30, 10, 30);
        painter.drawLine(40, 30, 50, 30);
        painter.drawText(19, 20, *reader);
    }
    painter.drawRect(0, 40, 49, 50);
    painter.setBrush(Qt::green);
    // painter.setPen(Qt::green);
    painter.drawRect(0, 40, 49, 49);
    painter.setBrush(QColor(0, 153, 0));
    painter.drawRect(0, 90, 49, 10);
    QFont font = painter.font();
    font.setPixelSize(33);
    painter.setFont(font);
    painter.drawText(15, 70, code);
}

void Block::changeState(char code) {
    this->code = code;
    update();
}

void Block::setReaderState(QString *readerState)
{
    reader = readerState;
}

void Block::select(bool s)
{
    if (selected != s) {
        selected = s;
        update();
    }
}


Block::~Block()
{
}


