#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>

class Button : public QObject, public QGraphicsRectItem {

    Q_OBJECT

public:
    //constructor
    Button(QString text, QGraphicsItem* parent = nullptr);

    //public method
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();

private:
    QString m_strText;
};

#endif // BUTTON_H
