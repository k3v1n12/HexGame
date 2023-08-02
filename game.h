#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "Utils.h"
#include "hexboard.h"


class Game: public QGraphicsView
{
    Q_OBJECT
public:
    //constructor
    Game(QWidget* parent = nullptr);

    //public function
    void DisplayMainMenu();

public slots:
    void start();

public:
    //member
    QGraphicsScene* m_gScene;
    HexBoard* m_gHexBoard;
    Player m_eCurrentPlayer;

};

#endif // GAME_H
