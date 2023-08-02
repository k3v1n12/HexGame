#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
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
    Player getCurrentPlayer();
    void setCurrentPlayer(Player nextPlayer);
    void pickUpCard(Hex* card);
    void placeCard(Hex* hexToReplace);

    //events
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

public slots:
    void start();

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity = 0.5);
    void drawGUI();
    void createNewCard(Player player);
    void createInitialCards();
    void drawCards();
    void removeFromDeck(Hex* card, Player player);
    void nextPlayersTurn();

public:
    //member
    QGraphicsScene* m_gScene;
    HexBoard* m_gHexBoard;
    Player m_eCurrentPlayer;
    QGraphicsTextItem* m_gCurrentPlayerText;
    Hex* m_gCardToPlace;
    QPointF m_pOriginalPos;

private:
    QList<Hex* >m_gPlayer1Cards;
    QList<Hex* >m_gPlayer2Cards;
};

#endif // GAME_H
