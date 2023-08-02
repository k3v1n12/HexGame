#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

enum Player{
    Player1,
    Player2
};

class Game: public QGraphicsView
{
public:
    //constructor
    Game(QWidget* parent = nullptr);

    //function
    void start();

    //member
    QGraphicsScene* m_gScene;
    //HexBoard* m_gHexBoard;
    Player m_eCurrentPlayer;

};

#endif // GAME_H
