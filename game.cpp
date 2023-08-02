#include "game.h"
#include "button.h"


Game::Game(QWidget *parent) {
    //set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    //set up scene
    m_gScene = new QGraphicsScene();
    m_gScene->setSceneRect(0, 0, 1024, 768);
    setScene(m_gScene);

}

void Game::start()  {
    //clear screen
    m_gScene->clear();

    m_gHexBoard  = new HexBoard();
    m_gHexBoard->placeHexes(100, 100, 5, 5);

}

void Game::DisplayMainMenu()    {
    //Create the title Text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("HEXTY"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);

    int xpos = this->width() / 2 - titleText->boundingRect().width() / 2;
    int ypos = this->height() / 2 - titleText->boundingRect().height() / 2;

    titleText->setPos(xpos, ypos);
    m_gScene->addItem(titleText);

    //Create the play button
    Button* playButton = new Button(QString("Play"));
    xpos = this->width() / 2 - titleText->boundingRect().width() / 2;
    ypos = this->height() / 2 + titleText->boundingRect().height() / 2;

    playButton->setPos(xpos, ypos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    m_gScene->addItem(playButton);

    //create quit button
    Button* quitButton = new Button(QString("Quit"));
    ypos = ypos + 3 * quitButton->boundingRect().height() / 2;

    quitButton->setPos(xpos, ypos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    m_gScene->addItem(quitButton);


}
