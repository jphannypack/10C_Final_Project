#include "enemy.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <chrono>
#include <random>

#include <QDebug>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

Enemy::Enemy(int xstart, int ystart, int char_type, Protagonist *p): QObject(), QGraphicsPixmapItem(){
    //draw enemy
    character = char_type;
    if (char_type == 1){
        setPixmap(QPixmap(":/images/entourage.png"));
    }
    else{
        setPixmap(QPixmap(":/images/bodyguard.png"));

    }
    setScale(.25);
    setPos(xstart,ystart);

    pro = p;

    ex = xstart;
    ey = ystart;

    destiny = 0;


    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(200);
}

void Enemy::move(){

    //check to see if protagonist is hit before moving
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Protagonist)){
            //play hit sound
            QMediaPlayer * hit = new QMediaPlayer();
            hit->setMedia(QUrl("qrc:/sounds/hit.wav"));
            hit->play();

            //remove them
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            //delete them
            delete colliding_items[i];
            delete this;

            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(Antagonist)){
            return;
        }
    }

    std::uniform_int_distribution<int> rand(0,4);
    int temp = rand(generator);

    if(temp == 0){
        //calculate distance between protagonist and antagonist
            int dx = pro->pro_x - ex;
            int dy = pro->pro_y - ey;


            if (dx > 0){ //if protag is to the right of enemy, move right
                setPos(x()+ speed, y());
                if (!facing_right){
                    if(character == 0)
                        setPixmap(QPixmap(":/images/bodyguard.png"));
                    else
                        setPixmap(QPixmap(":/images/entourage.png"));
                    facing_right = 1;
                }
                ex += speed;
            }
            if (dx < 0){ //if protag is to the left of enemy, move left
                setPos(x() - speed, y());
                if (facing_right){
                    if(character == 0)
                        setPixmap(QPixmap(":/images/bodyguardL.png"));
                    else
                        setPixmap(QPixmap(":/images/entourageL.png"));
                    facing_right = 0;
                }
                ex -= speed;
            }
            if (dy < 0){ //if protag above enemy, move up
                setPos(x(), y()-speed);
                ey -= speed;
            }
            if (dy > 0){ // if protag below enemy, move down
                setPos(x(), y()+speed);
                ey += speed;
            }
    }
    else{
        if (temp == 1){ //if protag is to the right of enemy, move right
            setPos(x()+ speed, y());
            if (!facing_right){
                if(character == 0)
                    setPixmap(QPixmap(":/images/bodyguard.png"));
                else
                    setPixmap(QPixmap(":/images/entourage.png"));
                facing_right = 1;
            }
            ex += speed;
        }
        else if (temp == 2){ //if protag is to the left of enemy, move left
            setPos(x() - speed, y());
            if (facing_right){
                if(character == 0)
                    setPixmap(QPixmap(":/images/bodyguardL.png"));
                else
                    setPixmap(QPixmap(":/images/entourageL.png"));
                facing_right = 0;
            }
            ex -= speed;
        }
        else if (temp == 3){ //if protag above enemy, move up
            setPos(x(), y()-speed);
            ey -= speed;
        }
        if (temp == 4){ // if protag below enemy, move down
            setPos(x(), y()+speed);
            ey += speed;
        }
    }






}

