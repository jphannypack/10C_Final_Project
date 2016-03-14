#include "antagonist.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

#include <QDebug>

Antagonist::Antagonist(int xstart, int ystart, int char_type, Protagonist* p): QObject(), QGraphicsPixmapItem(){
    //draw antagonist
    character = char_type;
    if (char_type == 1){
        setPixmap(QPixmap(":/images/kanye_west.png"));
    }
    else{
        setPixmap(QPixmap(":/images/taylor_swift.png"));

    }
    pro = p;

    ax = xstart;
    ay = ystart;
    setScale(.25);
    setPos(xstart,ystart);

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Antagonist::move(){

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
    }



    //calculate distance between protagonist and antagonist
    int dx = pro->pro_x - ax;
    int dy = pro->pro_y - ay;


    if (dx > 0){ //if protag is to the right of antagonist, move antag right
        setPos(x()+ speed, y());
        if (!facing_right){
            if(character == 0)
                setPixmap(QPixmap(":/images/taylor_swift.png"));
            else
                setPixmap(QPixmap(":/images/kanye_west.png"));
            facing_right = 1;
        }
        ax += speed;
    }
    if (dx < 0){ //if protag is to the left of antagonist, move antag left
        setPos(x() - speed, y());
        if (facing_right){
            if(character == 0)
                setPixmap(QPixmap(":/images/taylor_swiftL.png"));
            else
                setPixmap(QPixmap(":/images/kanye_westL.png"));
            facing_right = 0;
        }
        ax -= speed;
    }
    if (dy < 0){ //if protag above antagonist, move antag up
        setPos(x(), y()-speed);
        ay -= speed;
    }
    if (dy > 0){ // if protag below antagonist, move antag down
        setPos(x(), y()+speed);
        ay += speed;
    }


}
