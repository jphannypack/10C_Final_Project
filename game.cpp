#include "game.h"

#include "protagonist.h"

#include <QDebug>
#include <QTimer>


extern const int screen_width = 1024;
extern const int screen_height = 700;


Game::Game(QWidget *parent)
{
    //set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screen_width,screen_height);

    //set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,screen_width,screen_height);
    setScene(scene);
}

void Game::displayMainMenu(){

    //play background music
    QMediaPlayer * background_music = new QMediaPlayer;
    background_music->setMedia(QUrl("qrc:/sounds/blank_space.mp3"));
    background_music->setVolume(80);
    background_music->play();
    music = background_music;

    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Famous"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    openingscreen = new QWidget;
    QVBoxLayout *screen = new QVBoxLayout(openingscreen);

    //add in pictures here
    QImage image(":/images/intropic_default.png");
    QGraphicsPixmapItem* openingPicture = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    int pxPos = this->width()/2 - openingPicture->boundingRect().width()/2;
    int pyPos = this->height()/2 - openingPicture->boundingRect().height()/2;
    openingPicture->setPos(pxPos,pyPos);
    scene->addItem(openingPicture);


    QSpacerItem* vertical_space = new QSpacerItem(100,1000);
    screen->addSpacerItem(vertical_space);

    QHBoxLayout *players = new QHBoxLayout;
    QSpacerItem* horizontal_space = new QSpacerItem(70,0);
    players->addSpacerItem(horizontal_space);

    QPushButton* taylor = new QPushButton("Play as Taylor Swift");
    players->addWidget(taylor);
    QObject::connect(taylor,SIGNAL(clicked(bool)),this, SLOT(play_as_taylor()));

    players->addSpacerItem(horizontal_space);

    QPushButton* kanye = new QPushButton("Play as Kanye West");
    players->addWidget(kanye);
    QObject::connect(kanye,SIGNAL(clicked(bool)),this, SLOT(play_as_kanye()));
    players->addSpacerItem(horizontal_space);


    screen->addLayout(players,Qt::AlignCenter);
    QHBoxLayout * buttons = new QHBoxLayout;
    screen->addLayout(buttons,Qt::AlignCenter);


    //Instructions Button
    QPushButton* instructions= new QPushButton("Instructions");
    QObject::connect(instructions,SIGNAL(clicked()),this, SLOT(show_instructions()));
    buttons->addWidget(instructions);

    //Game Start Button
    QPushButton* play = new QPushButton("Start Game");
    QObject::connect(play,SIGNAL(clicked()),this, SLOT(start()));
    buttons->addWidget(play);

    //Quit Button
    QPushButton* quit = new QPushButton("Quit");
    QObject::connect(quit,SIGNAL(clicked()),this, SLOT(close()));
    buttons->addWidget(quit);

    this->setLayout(screen);


}

void Game::click_sound()
{
    //play click sound
    QMediaPlayer * click = new QMediaPlayer();
    click->setMedia(QUrl("qrc:/sounds/click.wav"));
    click->play();
}

void Game::game_over(int winner)
{
    game_still_playing = 0;
    //scene->clear();
    music->stop();

    if(winner == 1){
        QImage image(":/images/kanye_win.png");
        QGraphicsPixmapItem* kanye_winner = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(kanye_winner);

    }
    else{
        QImage image(":/images/taylor_win.png");
        QGraphicsPixmapItem* taylor_winner = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(taylor_winner);
    }
}




void Game::start()
{
    scene->clear();
    //restart the music if it's been stopped
    music->play();
    game_still_playing = 1;

    //play click sound
    click_sound();

    QImage image(":/images/stage.png");
    QGraphicsPixmapItem* background_image = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(background_image);

    //create item to insert inter scene
    Protagonist *protagonist = new Protagonist(playingAs, this);
    if (playingAs == 1){
        protagonist->setPixmap(QPixmap(":/images/taylor_swift.png"));
        protagonist->setScale(.25);
        protagonist->setPos(400,250);

    }
    else{
        protagonist->setPixmap(QPixmap(":/images/kanye_west.png"));
        protagonist->setScale(.25);
        protagonist->setPos(400,525);
    }



    //add item to scene
    scene->addItem(protagonist);

    //set protagonist as the focused item
    protagonist->setFlag(QGraphicsItem::ItemIsFocusable);
    protagonist->setFocus();

    //spawn enemies
    protagonist->spawn(playingAs);

    //creater the timer
    time_left = 30;
    time = new QGraphicsTextItem;
    time->setPlainText(QString("Time: ") + QString::number(time_left)); // Score: 60
    QFont timeFont("Helvetica", 16);
    time->setDefaultTextColor("blue");
    time->setFont(timeFont);
    scene->addItem(time);

    countdown = new QTimer(this);
    connect(countdown,SIGNAL(timeout()),this,SLOT(decrement()));
    countdown->start(1000);





}

void Game::show_instructions()
{
    //clear scene
    //scene->clear();

    //play click sound
    click_sound();

    QImage image(":/images/instruction_screen.png");
    QGraphicsPixmapItem* instructionPicture = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(instructionPicture);

}

void Game::play_as_taylor()
{
    //clear scene
    scene->clear();

    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Famous"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //set player to taylor
    playingAs = 1;

    //play click sound
    click_sound();

    //change the picture
    QImage image(":/images/intropic_taylor.png");
    QGraphicsPixmapItem* openingPicture = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    int pxPos = this->width()/2 - openingPicture->boundingRect().width()/2;
    int pyPos = this->height()/2 - openingPicture->boundingRect().height()/2;
    openingPicture->setPos(pxPos,pyPos);
    scene->addItem(openingPicture);

}

void Game::play_as_kanye()
{
    //clear scene
    scene->clear();

    //create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Famous"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //set player to kanye
    playingAs = 0;

    //play click sound
    click_sound();

    //change the picture
    QImage image(":/images/intropic_kanye.png");
    QGraphicsPixmapItem* openingPicture = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    int pxPos = this->width()/2 - openingPicture->boundingRect().width()/2;
    int pyPos = this->height()/2 - openingPicture->boundingRect().height()/2;
    openingPicture->setPos(pxPos,pyPos);
    scene->addItem(openingPicture);
}

void Game::decrement()
{
    if (time_left <= 0){
        if(game_still_playing == 1){
            game_still_playing = 0;
            countdown->stop();

            game_over(playingAs);

        }
        return;
    }
    else if(game_still_playing){
        delete time;
        time_left--;
        time = new QGraphicsTextItem;
        time->setPlainText(QString("Time: ") + QString::number(time_left)); // Score: 60
        QFont timeFont("Helvetica", 16);
        time->setDefaultTextColor("blue");
        time->setFont(timeFont);
        scene->addItem(time);

        if(time_left <= 10)
            click_sound();





    }



}



