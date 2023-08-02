#include "hex.h"
#include <QBrush>
#include "game.h"

extern Game* game;

const int SCALE_BY = 40;

Hex::Hex(QGraphicsItem *parent)
    :m_eOwner(Noone)
    ,m_bisPlaced(true)
{
    // draw the polygon
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1, 0) << QPointF(2, 0) << QPointF(3, 1)
              << QPointF(2, 2) << QPointF(1, 2) << QPointF(0, 1);

    for(int i = 0; i < hexPoints.size(); i++) {
        hexPoints[i] *= SCALE_BY;
    }

    setPolygon(hexPoints);
}

Player Hex::getOwner()
{
    return m_eOwner;
}

bool Hex::getIsPlaced()
{
    return m_bisPlaced;
}

void Hex::setOwner(Player player)   {
    //set the owner and change the color
    m_eOwner = player;

    if(player == Noone) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    }

    if(player == Player1) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    }

    if(player == Player2) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void Hex::setIsPlaced(bool value)
{
    m_bisPlaced = value;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event)  {

    //if the hex is not placed, pick it up
    if(!getIsPlaced()) {
        game->pickUpCard(this);
    }

    //if the hex is placed, replace it
    else {
        if(getOwner() == Noone) {
            game->placeCard(this);
        }
    }
}
