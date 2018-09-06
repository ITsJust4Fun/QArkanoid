#include "platform.h"

Platform::Platform(int fieldWidth, int fieldHeight, QObject *parent)
    : QObject(parent), QGraphicsItem() {

    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;
    platformWidth = static_cast<int>(60 * fieldWidth / 381.0);
    platformHeight = static_cast<int>(10 * fieldHeight / 481.0);
    delta = 2;
    corL = 30;
    corR = 13;
    curPosX = (fieldWidth / 2) - platformWidth / 2 + corR;
    curPosY = fieldHeight - (fieldHeight / 8);
    startFlag = true;
    keys = new QList<int>;
    moveTimer = new QTimer;
    platformSound = new QSoundEffect;
    platformSound->setSource(QUrl::fromLocalFile(":/sfx/platform_colis.wav"));

    QObject::connect(moveTimer, SIGNAL(timeout()),
                     this, SLOT(moving()));
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    setPos(curPosX, curPosY);
    painter->drawPixmap(-platformWidth / 2, -platformHeight / 2,
                        platformWidth, platformHeight,
                        QPixmap(":/textures/platform.png"));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Platform::boundingRect() const{
    return QRectF(-platformWidth / 2, -platformHeight / 2,
                  platformWidth, platformHeight);
}

void Platform::setSpeed(int delta){
    this->delta = delta;
}

void Platform::setCor(int corL, int corR){
    this->corL = corL;
    this->corR = corR;
}

int Platform::getPosX(){
    return curPosX;
}

int Platform::getPosY(){
    return curPosY;
}

void Platform::keyPressEvent(QKeyEvent *event){
    keys->removeAll(event->key());
    keys->append(event->key());
    moveTimer->start(5);
}

void Platform::keyReleaseEvent(QKeyEvent* event){
    keys->removeAll(event->key());
    if (keys->size() == 0){
        moveTimer->stop();
    }
}

void Platform::moving(){
    for (auto key: *keys){
        switch(key) {
            case Qt::Key_Left:
                if(curPosX < delta + platformWidth / 2 - corL){
                    curPosX = platformWidth / 2 - corL;
                } else {
                    curPosX -= delta;
                }
                break;
            case Qt::Key_Right:
                if((curPosX + platformWidth / 2 + corR) > fieldWidth - delta){
                    curPosX = fieldWidth - platformWidth / 2 - corR;
                } else {
                    curPosX += delta;
                }
                break;
            case Qt::Key_Space:
                if(startFlag){
                    emit startMove();
                    platformSound->play();
                }
                startFlag = false;
        }
        if (startFlag){
            emit changeBallPos(curPosX + 7);
        }
        setX(curPosX);
        update();
    }
}

void Platform::mouseMove(int mouseDelta) {
    if(mouseDelta < 0){
        if(curPosX + mouseDelta < platformWidth / 2 - corL){
            curPosX = platformWidth / 2 - corL;
        } else {
            curPosX += mouseDelta;
        }
    } else {
        if((curPosX + platformWidth / 2 + corR) > fieldWidth - mouseDelta){
            curPosX = fieldWidth - platformWidth / 2 - corR;
        } else {
            curPosX += mouseDelta;
        }
    }
    if (startFlag){
        emit changeBallPos(curPosX + 7);
    }
    setX(curPosX);
    update();
}

void Platform::startBall(){
    if(startFlag){
        emit startMove();
        platformSound->play();
    }
    startFlag = false;
}

Platform::~Platform(){
    delete keys;
    delete moveTimer;
    delete platformSound;
}
