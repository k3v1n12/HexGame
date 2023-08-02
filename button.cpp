#include "button.h"
#include <QBrush>


Button::Button(QString text, QGraphicsItem *parent)
    :m_strText(text)
{
    //draw rect
    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    //draw text
    QGraphicsTextItem* textRect = new QGraphicsTextItem(m_strText, this);
    int xpos = rect().width() / 2 - textRect->boundingRect().width() / 2;
    int ypos = rect().height() / 2 - textRect->boundingRect().height() / 2;

    textRect->setPos(xpos, ypos);

    //set hover event
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)   {

    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)   {

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)   {

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
