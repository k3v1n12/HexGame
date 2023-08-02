#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "Utils.h"
#include "hexboard.h"


class Game: public QGraphicsView
{
public:
    //constructor
    Game(QWidget* parent = nullptr);

    //function
    void start();

    //member
    QGraphicsScene* m_gScene;
    HexBoard* m_gHexBoard;
    Player m_eCurrentPlayer;

};

#endif // GAME_H
