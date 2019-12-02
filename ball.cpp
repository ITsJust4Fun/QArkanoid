#include "ball.h"

Ball::Ball(int fieldWidth, int fieldHeight, QObject *parent) : QObject(parent) {
    this->fieldWidth = fieldWidth - 12;
    this->fieldHeight = fieldHeight + 12;
    curPosX = (fieldWidth / 2) - 10;
    curPosY = fieldHeight - (fieldHeight / 8) - static_cast<int>(15 * fieldHeight / 500.0);
    rad = static_cast<int>(5 * std::min(fieldHeight / 481.0, fieldWidth / 381.0));
    angular = M_PI_4;
    speed = 4;
    kol = 0;
	timer = new QElapsedTimer();
	timer->start();
    platformSound = new QSoundEffect(this);
    platformSound->setSource(QUrl::fromLocalFile(":/sfx/platform_colis.wav"));
    blockDestroySound = new QSoundEffect(this);
    blockDestroySound->setSource(QUrl::fromLocalFile(":/sfx/block_dest.wav"));
    blockDamagedSound = new QSoundEffect(this);
    blockDamagedSound->setSource(QUrl::fromLocalFile(":/sfx/block_damage.wav"));
}

Ball::~Ball() {
	delete timer;
}

QRectF Ball::boundingRect() const{
    return QRectF(-rad, -rad, rad * 2, rad * 2);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    setPos(curPosX, curPosY);
    painter->drawPixmap(-rad, -rad, rad * 2, rad * 2,
                        QPixmap(":/textures/ball.png"));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Ball::startMovement(int pos){
    curPosX = pos;
    setX(curPosX);
}

void Ball::move(){
    if (changeAngular()){
        angular += 2 * (changeAng - angular);
        if (angular > 2 * M_PI){
            angular -= 2 * M_PI;
        } else if (angular < 0){
            angular += 2 * M_PI;
        }
    }
    curPosX += speed * cos(angular);
    curPosY -= speed * sin(angular);
    setPos(curPosX, curPosY);
    if(curPosY > fieldHeight + 50){
        emit removeBall(this);
    }
}

bool Ball::changeAngular(){

	if (timer->elapsed() < collisionTime) {
		return false;
	}

	timer->restart();

    if (curPosX + rad + speed * cos(angular) >= fieldWidth){
        changeAng = M_PI_2;
        return true;
    } else if (curPosY - rad - speed * sin(angular) <= -4){
        if(fabs(changeAng - M_PI) < 0.000001 && kol < 3){
            kol++;
            return false;
        }
        kol = 0;
        changeAng = M_PI;
        return true;
    } else if (curPosX - rad + speed * cos(angular) <= - 31){
        changeAng = 3 * M_PI_2;
        return true;
    } //else if (curPosY + rad - speed * sin(angular) >= fieldHeight){
      //  if(fabs(changeAng - 2 * M_PI) < 0.000001 && kol < 3){
      //      kol++;
      //      return false;
      //  }
      //  kol = 0;
      //  changeAng = 2 * M_PI;
      //  return true;
    //}
    QList<QGraphicsItem*> items = this->collidingItems();
    for(auto x: items){
        if (x->hasFocus()){;
            platformSound->play();
            double pointX = x->pos().x();
            double pointY = x->pos().y();
            int pW = (dynamic_cast<Platform*>(x))->platformWidth;
            if (pointY > curPosY && fabs(pointX - curPosX) < (pW / 2)){
                if(fabs(changeAng - 2 * M_PI) < 0.000001){
                    return false;
                }
                if(fabs(pointX - curPosX) > (pW / 2) * 0.8){
                    if (pointX < curPosX) {
                        angular = (11 * M_PI / 6) - 0.2;
                    } else {
                        angular = (7 * M_PI / 6) - 0.2;
                    }
                } else if (fabs(pointX - curPosX) < (pW / 2) * 0.3) {
                    if (pointX < curPosX) {
                        angular = 5 * M_PI / 3;
                    } else {
                        angular = 4 * M_PI / 3;
                    }
                } else {
                    if (pointX < curPosX) {
                        angular = 7 * M_PI_4;
                    } else {
                        angular = 5 * M_PI_4;
                    }
                }
                changeAng = 2 * M_PI;
                return true;
            } else if (pointY < curPosY && fabs(pointX - curPosX) < (pW / 2)){
                if(fabs(changeAng - M_PI) < 0.000001){
                    return false;
                }
                changeAng = M_PI;
                return true;
            } else if (pointX < curPosX){
                changeAng = M_PI_2;
                return true;
            } else {
                changeAng = 3 * M_PI_2;
                return true;
            }
        } else {
            double pointX = x->pos().x();
            double pointY = x->pos().y();
            int bW = (dynamic_cast<Block*>(x))->width;
            if (pointY > curPosY && fabs(pointX - curPosX) < (bW / 2) + 2){
                if(fabs(changeAng - 2 * M_PI) < 0.000001){
                    return false;
                }
                changeAng = 2 * M_PI;
                hitBlock(dynamic_cast<Block*>(x));
                return true;
            } else if (pointY < curPosY && fabs(pointX - curPosX) < (bW / 2) + 2){
                if(fabs(changeAng - M_PI) < 0.000001){
                    return false;
                }
                changeAng = M_PI;
                hitBlock(dynamic_cast<Block*>(x));
                return true;
            } else if (pointX < curPosX){
                if(fabs(changeAng - M_PI_2) < 0.000001){
                    return false;
                }
                changeAng = M_PI_2;
                hitBlock(dynamic_cast<Block*>(x));
                return true;
            } else {
                if(fabs(changeAng - 3 * M_PI_2) < 0.000001){
                    return false;
                }
                changeAng = 3 * M_PI_2;
                hitBlock(dynamic_cast<Block*>(x));
                return true;
            }
        }
    }
    return false;
}

void Ball::hitBlock(Block* block){
    int blockHealth = block->health;
    if (blockHealth > 1){
        block->damaged = true;
        block->health--;
        block->update();
        blockDamagedSound->play();
    } else {
        emit removeBlockSig(block);
        blockDestroySound->play();
    }
}
