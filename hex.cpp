#include "hex.h"
#include <QBrush>
#include "game.h"
#include <QDebug>

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

    //create lines
    createLines();

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

int Hex::getAttackof(int side)
{
    return m_lSideAttack[side];
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

void Hex::createLines() {
    QPointF hexCenter(x() + 60, y() + 40);
    QPointF finalPoint(hexCenter.x(), hexCenter.y() - 60);
    QLineF ln(hexCenter, finalPoint);
    for(auto i = 0; i < 6; i++) {
        QLineF lnCopy(ln);
        lnCopy.setAngle(90 + 60 * i);
        QGraphicsLineItem* line = new QGraphicsLineItem(lnCopy, this);
        line->setVisible(false);
        m_lLines.append(line);

    }
}

void Hex::findNeighbours() {

    foreach(auto line, m_lLines) {
        //if line collidings it an item of type hex, add it to neighbour
        QList<QGraphicsItem*> colliding = line->collidingItems();
        foreach(auto collide, colliding) {
            auto item{dynamic_cast<Hex*>(collide)};
            if(item !=this && item) {
                m_lNeighbours.append(item);
                qDebug()<<item->pos();
            }
        }
    }
}

void Hex::SwitchOwner() {

    if(getOwner() == Player1) {
        setOwner(Player2);
    }
    else if(getOwner() == Player2) {
        setOwner(Player1);
    }

}

void Hex::captureNeighbour() {
    for(auto i = 0; i < m_lNeighbours.size(); i++) {
        bool isEnemy = false;
        bool isNotNuetral = false;

        if(getOwner() != m_lNeighbours[i]->getOwner()) {
            isEnemy = true;
        }

        if(m_lNeighbours[i]->getOwner() != Noone) {
            isNotNuetral = true;
        }

        //if its enemy and not nuetral
        if(isEnemy && isNotNuetral) {
            //find attack of adjacent intersecting sides
            int thisAttack = 0;
            int neighboursAttack = 0;
            switch(i) {
                case 0: thisAttack = getAttackof(0);
                        neighboursAttack = m_lNeighbours[0]->getAttackof(3);
                        break;
                case 1: thisAttack = getAttackof(1);
                        neighboursAttack = m_lNeighbours[1]->getAttackof(4);
                        break;
                case 2: thisAttack = getAttackof(2);
                        neighboursAttack = m_lNeighbours[2]->getAttackof(5);
                        break;
                case 3: thisAttack = getAttackof(3);
                        neighboursAttack = m_lNeighbours[3]->getAttackof(0);
                        break;
                case 4: thisAttack = getAttackof(4);
                        neighboursAttack = m_lNeighbours[4]->getAttackof(1);
                        break;
                case 5: thisAttack = getAttackof(5);
                        neighboursAttack = m_lNeighbours[5]->getAttackof(2);
                        break;
            }

            if(thisAttack > neighboursAttack) {
                        m_lNeighbours[i]->SwitchOwner();
            }
        }
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
