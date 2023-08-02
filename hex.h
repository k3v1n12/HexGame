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

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    Player m_eOwner;
    bool m_bisPlaced;
    int m_lSideAttack[6];
    QList<QGraphicsTextItem*> m_lAttackTexts;

};


#endif // HEX_H
