#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QSoundEffect>

class Platform : public QObject, public QGraphicsItem {

    Q_OBJECT

private:
    int fieldWidth;
    int fieldHeight;
    int curPosX;
    int curPosY;
    int delta = 1;
    int corL = 30;
    int corR = 13;
    bool pressing;
    QList<int>* keys;
    QTimer* moveTimer;
    QSoundEffect* platformSound;

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public:
    explicit Platform(int fieldWidth, int fieldHeight, QObject *parent = nullptr);
    ~Platform();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mouseMove(int mouseDelta);
    void startBall();
    void setSpeed(int delta);
    void setCor(int corL, int corR);
    int getPosX();
    int getPosY();
    bool startFlag;
    int platformWidth;
    int platformHeight;

signals:
    void changeBallPos(int pos);
    void startMove();

public slots:
    void moving();
};

#endif // PLATFORM_H
