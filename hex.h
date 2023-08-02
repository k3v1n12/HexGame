#ifndef HEX_H
#define HEX_H

#include<QGraphicsPolygonItem>
#include "Utils.h"

class Hex: public QGraphicsPolygonItem
{
public:
    //constructor
    Hex(QGraphicsItem* parent = nullptr);

    //getter
    int getAttackof(int side);

    //setter
    void setAttackof(int side, int value);
    void setOwner(Player player);

private:
    Player m_eOwner;
    int m_nSide0Attack;
    int m_nSide1Attack;
    int m_nSide2Attack;
    int m_nSide3Attack;
    int m_nSide4Attack;
    int m_nSide5Attack;

};

#endif // HEX_H
