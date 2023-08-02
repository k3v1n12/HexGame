#include "game.h"


Game::Game(QWidget *parent)
{
    //set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    //set up scene
    m_gScene = new QGraphicsScene();
    m_gScene->setSceneRect(0, 0, 1024, 768);
    setScene(m_gScene);

}
