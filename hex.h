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

    //event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    Player m_eOwner;
    bool m_bisPlaced;
    int m_nSide0Attack;
    int m_nSide1Attack;
    int m_nSide2Attack;
    int m_nSide3Attack;
    int m_nSide4Attack;
    int m_nSide5Attack;

};


#endif // HEX_H
