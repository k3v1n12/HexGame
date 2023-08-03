#ifndef HEX_H
#define HEX_H

#include<QGraphicsPolygonItem>
#include<QGraphicsSceneMouseEvent>
#include "Utils.h"

class Hex: public QGraphicsPolygonItem
{
public:
    //constructor
    Hex(QGraphicsItem* parent = nullptr);

    //getter
    int getAttackof(int side);
    Player getOwner();
    bool getIsPlaced();

    //setter
    void setAttackof(int side, int value);
    void setOwner(Player player);
    void setIsPlaced(bool value);

    //public method
    void displaySideAttack();
    void createLines();
    void findNeighbours();
    void SwitchOwner();
    void captureNeighbour();

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    Player m_eOwner;
    bool m_bisPlaced;
    int m_lSideAttack[6];
    QList<QGraphicsTextItem*> m_lAttackTexts;
    QList<Hex*> m_lNeighbours;
    QList<QGraphicsLineItem*> m_lLines;

};


#endif // HEX_H
