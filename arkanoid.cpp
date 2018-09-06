#include "arkanoid.h"


Arkanoid::Arkanoid(QWidget *parent) : QWidget(parent) {
    screens = QGuiApplication::screens();
    screenHeight = screens[0]->size().height();
    screenWidth = screens[0]->size().width();
    //widgetHeight = screenHeight;
    //widgetWidth = screenWidth;
    widgetHeight = 500;
    widgetWidth = 400;
    ballMoveSpeedT = 10;
    setGeometry((screenWidth / 2) - (widgetWidth / 2),
                (screenHeight / 2) - (widgetHeight / 2),
                widgetWidth, widgetHeight);
    setWindowTitle("Arkanoid");
    setFixedSize(widgetWidth, widgetHeight);
    setWindowIcon(QIcon(":/Arkanoid_icon.png"));

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    sceneWidth = widgetWidth - 19;
    sceneHeight = widgetHeight - 19;
    scene->setSceneRect(-30, -5, sceneWidth, sceneHeight);
    view = new QGraphicsView(scene, this);
    view->resize(widgetWidth, widgetHeight);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    platform = new Platform(sceneWidth, sceneHeight);
    ball = new Ball(sceneWidth, sceneHeight);
    scene->addItem(ball);
    scene->addItem(platform);
    platform->setFlag( QGraphicsItem::ItemIsFocusable, true );
    platform->grabKeyboard();
    setCursor(Qt::BlankCursor);
    platform->setFocus();
    view->setBackgroundBrush(Qt::black);
    timer = new QTimer;
    timer->setTimerType(Qt::PreciseTimer);
    blocks = new QList<Block*>;
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            Block* block;
            if (i == 0){
                block = new Block(2, "gray", widgetWidth, widgetHeight);
            } else if (i == 1){
                block = new Block(1, "blue", widgetWidth, widgetHeight);
            } else if (i == 2){
                block = new Block(1, "green", widgetWidth, widgetHeight);
            } else if (i == 3){
                block = new Block(1, "orange", widgetWidth, widgetHeight);
            } else if (i == 4){
                block = new Block(1, "purple", widgetWidth, widgetHeight);
            } else if (i == 5){
                block = new Block(1, "red", widgetWidth, widgetHeight);
            } else if (i == 6){
                block = new Block(1, "yellow", widgetWidth, widgetHeight);
            } else {
                block = new Block(2, "gray", widgetWidth, widgetHeight);
            }
            block->setPos(block->width * j - static_cast<int>(6 * widgetWidth / 400.0), 50 + block->height * i);
            blocks->append(block);
            scene->addItem(block);
        }
    };
    grabMouse();
    setMouseTracking(true);

    QObject::connect(platform, SIGNAL(changeBallPos(int)),
                     ball, SLOT(startMovement(int)));
    QObject::connect(platform, SIGNAL(startMove()),
                     this, SLOT(connectTnB()));
    QObject::connect(ball, SIGNAL(removeBlockSig(Block*)),
                     this, SLOT(removeBlock(Block*)));
    QObject::connect(ball, SIGNAL(removeBall(Ball*)),
                     this, SLOT(removeBall(Ball*)));
    QObject::connect(timer, SIGNAL(timeout()),
                     ball, SLOT(move()));

}

Arkanoid::~Arkanoid() {
    delete scene;
    delete view;
    delete timer;
    delete blocks;
}

void Arkanoid::connectTnB(){
    timer->start(ballMoveSpeedT);
}

void Arkanoid::removeBlock(Block* block){
    scene->removeItem(block);
}

void Arkanoid::mouseMoveEvent(QMouseEvent* event){
    mouseX = event->x() - platform->getPosX() - platform->platformWidth / 2;
    platform->mouseMove(mouseX);
}

void Arkanoid::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton){
        platform->startBall();
    }
}

void Arkanoid::removeBall(Ball* ball) {
    timer->stop();
    ball->curPosX = platform->getPosX() + static_cast<int>(7 * widgetWidth / 400.0);
    ball->curPosY = platform->getPosY() - static_cast<int>(15 * widgetHeight / 500.0);
    ball->angular = M_PI_4;
    ball->setPos(ball->curPosX, ball->curPosY);
    ball->update();
    platform->startFlag = true;
}
