#include "protagonist.h"
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include "enemy.h"
#include "antagonist.h"





Protagonist::Protagonist(int char_type, Game *g)
{
    //initialize the character as either Taylor or Kanye so that when spawning enemies the right enemies spawn
    character = char_type;

    //initialize the starting position of the Protagonist based on their character type
    if (char_type == 1){
        pro_x = 400;
        pro_y = 250;
    }
    else{
        pro_x = 400;
        pro_y = 525;
    }
    //set the game so that the game over function can be called
    game = g;

}




void Protagonist::keyPressEvent(QKeyEvent *event)
{
    /* 1) check to see if the protagonist is going out of bounds, if yes then return function
     * 2) change the position of the protagonist
     * 3) if changing direction, flip the image of the character
     * 4) update the private variable pro_x/pro_y so that the Antagonist and Enemy class know where the Protagonist is
     */
     if (event->key()== Qt::Key_Left){
         if (pro_x < -10)
             return;
         setPos(x()-speed,y());
         if (facing_right){
             if(character == 1)
                 setPixmap(QPixmap(":/images/taylor_swiftL.png"));
             else
                 setPixmap(QPixmap(":/images/kanye_westL.png"));
             facing_right = 0;
         }
         pro_x -= speed;
     }
     else if (event->key() == Qt::Key_Right){
         if (pro_x > 930)
             return;
         setPos(x()+speed,y());
         if (!facing_right){
             if(character == 1)
                 setPixmap(QPixmap(":/images/taylor_swift.png"));
             else
                 setPixmap(QPixmap(":/images/kanye_west.png"));
             facing_right = 1;
         }
         pro_x += speed;
     }
     else if (event->key() == Qt::Key_Up){
         if (pro_y < -10)
             return;
         setPos(x(),y()-speed);
         pro_y -=speed;
     }
     else if (event->key() == Qt::Key_Down){
         if (pro_y > 540)
             return;
         setPos(x(),y()+speed);
         pro_y +=speed;
     }

}


//although there are no pointers to delete, I implement a delete function because when I delete the
//protagonist after hitting an enemy this function is the one to call the game_over function
Protagonist::~Protagonist()
{
   game->game_over(character);
}



void Protagonist::spawn(int char_type)
{
    //spawn status if protagonist is Taylor
    if(char_type == 1){
        Enemy * enemy1 = new Enemy(325,450,char_type, this);
        scene()->addItem(enemy1);
        Enemy * enemy2 = new Enemy(400,450,char_type, this);
        scene()->addItem(enemy2);
        Enemy * enemy3 = new Enemy(475,450,char_type, this);
        scene()->addItem(enemy3);
        Antagonist * antagonist = new Antagonist (400,525, char_type, this);
        scene()->addItem(antagonist);
    }
    //spawn status if protagonist is Kanye
    else{
        Enemy * enemy1 = new Enemy(600,250,char_type, this);
        scene()->addItem(enemy1);
        Enemy * enemy2 = new Enemy(100,250,char_type, this);
        scene()->addItem(enemy2);
        Enemy * enemy3 = new Enemy(400,400,char_type, this);
        scene()->addItem(enemy3);
        Antagonist * antagonist = new Antagonist (400,250, char_type, this);
        scene()->addItem(antagonist);
    }


}


