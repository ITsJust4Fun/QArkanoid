#include "block.h"

Block::Block(int health, QString color, int widthF, int heightF, QObject *parent) : QObject(parent) {
    this->health = health;
    this->color = color;
    height = static_cast<int> (20 * heightF / 500.0);
    width = static_cast<int> (50 * widthF / 400.0);
    damaged = false;
}

QRectF Block::boundingRect() const{
    return QRectF(-width / 2, -height / 2, width, height);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(!damaged){
        painter->drawPixmap(-width / 2, -height / 2, width, height,
                            QPixmap(":/textures/block_" + color + ".png"));
    } else {
        painter->drawPixmap(-width / 2, -height / 2, width, height,
                            QPixmap(":/textures/block_gray_damaged.png"));
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
