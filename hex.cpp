#include "hex.h"

const int SCALE_BY = 40;

Hex::Hex(QGraphicsItem *parent) {
    // draw the polygon
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1, 0) << QPointF(2, 0) << QPointF(3, 1)
              << QPointF(2, 2) << QPointF(1, 2) << QPointF(0, 1);

    for(int i = 0; i < hexPoints.size(); i++) {
        hexPoints[i] *= SCALE_BY;
    }

    setPolygon(hexPoints);
}

void Hex::setOwner(Player player)   {
    m_eOwner = player;
}
