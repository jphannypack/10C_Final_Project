#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>


namespace Ui {
class Game;
}


class Game: public QGraphicsView{
    Q_OBJECT
public:
    //constructors
    Game(QWidget* parent = NULL);

    //public methods
    void displayMainMenu();
    void click_sound();

    //public attributes
    QGraphicsScene* scene;

    friend class Protagonist;
    void game_over(int character);

public slots:
      void start();
      void show_instructions();
      void play_as_taylor();
      void play_as_kanye();
      void decrement();


private:
     Ui::Game *ui;

      QWidget* openingscreen;
      QVBoxLayout * screen;
      QLabel* game_title;
      QPixmap* openingPicture;
      QLabel* picture;
      QMediaPlayer * clicked;
      QMediaPlayer * music;

      int playingAs =1;

      QGraphicsTextItem * time;
      QTimer * countdown;
      int time_left;

      bool game_still_playing =1;


};



#endif // GAME_H
