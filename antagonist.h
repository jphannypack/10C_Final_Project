#ifndef ANTAGONIST_H
#define ANTAGONIST_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "protagonist.h"

class Antagonist: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Antagonist(int xstart, int ystart, int char_type, Protagonist *p);
public slots:
    void move();
private:
    int speed = 5;
    int xstart = 0;
    int ystart = 0;
    int ax;
    int ay;
    int character;
    bool facing_right = 1;
    Protagonist *pro;
};




#endif // ANTAGONIST_H
