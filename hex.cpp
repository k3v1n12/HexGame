#include "hex.h"
#include <QBrush>
#include "game.h"

extern Game* game;

const int SCALE_BY = 40;

Hex::Hex(QGraphicsItem *parent)
    :m_eOwner(Noone)
    ,m_bisPlaced(true)
    ,m_lSideAttack{}
{
    // draw the polygon
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1, 0) << QPointF(2, 0) << QPointF(3, 1)
              << QPointF(2, 2) << QPointF(1, 2) << QPointF(0, 1);

    for(int i = 0; i < hexPoints.size(); i++) {
        hexPoints[i] *= SCALE_BY;
    }

    setPolygon(hexPoints);

    //create QGraphicsTextItem to visualise each side's attack
    QGraphicsTextItem* text0 = new QGraphicsTextItem(QString::number(0), this);
    QGraphicsTextItem* text1 = new QGraphicsTextItem(QString::number(0), this);
    QGraphicsTextItem* text2 = new QGraphicsTextItem(QString::number(0), this);
    QGraphicsTextItem* text3 = new QGraphicsTextItem(QString::number(0), this);
    QGraphicsTextItem* text4 = new QGraphicsTextItem(QString::number(0), this);
    QGraphicsTextItem* text5 = new QGraphicsTextItem(QString::number(0), this);

    //add it to list to track it
    m_lAttackTexts.append(text0);
    m_lAttackTexts.append(text1);
    m_lAttackTexts.append(text2);
    m_lAttackTexts.append(text3);
    m_lAttackTexts.append(text4);
    m_lAttackTexts.append(text5);

    //set their position in hex
    text0->setPos(50, 0);
    text1->setPos(20, 15);
    text2->setPos(20, 40);
    text3->setPos(50, 55);
    text4->setPos(80, 40);
    text5->setPos(80, 15);

    //set all attacktexts to be invincible
    foreach(auto item, m_lAttackTexts) {
        item->setVisible(false);
    }



}

Player Hex::getOwner()
{
    return m_eOwner;
}

bool Hex::getIsPlaced()
{
    return m_bisPlaced;
}

void Hex::setAttackof(int side, int value)
{
    m_lSideAttack[side] = value;
    m_lAttackTexts[side]->setPlainText(QString::number(value));
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

void Hex::displaySideAttack() {

    foreach(auto item, m_lAttackTexts) {
        item->setVisible(true);
    }
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
