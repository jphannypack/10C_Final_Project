#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "protagonist.h"
#include "antagonist.h"

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int xstart, int ystart, int char_type, Protagonist *p);
public slots:
    void move();

private:
    int speed = 10;
    int xstart = 0;
    int ystart = 0;
    int ex;
    int ey;
    int destiny;
    int character;
    bool facing_right;
    Protagonist *pro;
};




#endif // ENEMY_H
