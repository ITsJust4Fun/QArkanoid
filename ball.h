#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "platform.h"
#include "block.h"

#include <QSoundEffect>

class Ball : public QObject, public QGraphicsItem {
    Q_OBJECT

private:
    int fieldWidth;
    int fieldHeight;
    double changeAng;
    int ballWidth;
    int ballHeight;
    int rad;
    int speed;
    int kol;
    QSoundEffect* platformSound;
    QSoundEffect* blockDestroySound;
    QSoundEffect* blockDamagedSound;

public:
    explicit Ball(int fieldWidth, int fieldHeight, QObject *parent = nullptr);
    ~Ball();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool changeAngular();
    void hitBlock(Block* block);
    int curPosX;
    int curPosY;
    double angular;

signals:
    void removeBlockSig(Block*);
    void removeBall(Ball*);

public slots:
    void startMovement(int pos);
    void move();
};

#endif // BALL_H
