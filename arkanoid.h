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
#include <QElapsedTimer>
#include <QIcon>
#include <QMessageBox>
#include <QTimer>
#include <QTime>

class Arkanoid : public QWidget {
    Q_OBJECT

private:
	const double M_PI = 3.14;
	const double M_PI_2 = M_PI / 2;
	const double M_PI_4 = M_PI / 4;
    QList<QScreen*> screens;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
	QElapsedTimer* gameTimer;
    Platform* platform;
    Ball* ball;
    int screenWidth;
    int screenHeight;
    int widgetWidth;
    int widgetHeight;
    int sceneWidth;
    int sceneHeight;
    int mouseX;
    int ballMoveSpeedT;
	int blocksNumber;
	int attempts;
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

public:
    Arkanoid(QWidget *parent = nullptr);
    ~Arkanoid();

private slots:
    void connectTnB();
    void removeBlock(Block*);
    void removeBall(Ball*);
	void addBlocks();
};

#endif // ARCANOID_H
