#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "game.h"

class Protagonist: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Protagonist(int char_type, Game* g);
    ~Protagonist();

    void keyPressEvent(QKeyEvent *event);

    friend class Enemy;
    friend class Antagonist;
    friend class Game;

public slots:
    void spawn(int char_type);
private:
    int speed = 10;
    bool facing_right = 1;
    int character = 1;
    int pro_x;
    int pro_y;
    Game* game;

};


#endif // PROTAGONIST_H
