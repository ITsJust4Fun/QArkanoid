#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Block : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit Block(int health, QString color, int widthF, int heightF,QObject *parent = nullptr);
    int health;
    bool damaged;
    QString color;
    int height;
    int width;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
};

#endif // BLOCK_H
