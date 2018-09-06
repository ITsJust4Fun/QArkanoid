#ifndef ARKANOID_H
#define ARKANOID_H

#include "platform.h"
#include "ball.h"
#include "block.h"
#include <QWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QList>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QIcon>

class Arkanoid : public QWidget {
    Q_OBJECT

private:
    QList<QScreen*> screens;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
    Platform* platform;
    Ball* ball;
    QList<Block*>* blocks;
    int screenWidth;
    int screenHeight;
    int widgetWidth;
    int widgetHeight;
    int sceneWidth;
    int sceneHeight;
    int mouseX;
    int ballMoveSpeedT;
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

public:
    Arkanoid(QWidget *parent = nullptr);
    ~Arkanoid();
private slots:
    void connectTnB();
    void removeBlock(Block*);
    void removeBall(Ball*);
};

#endif // ARCANOID_H
