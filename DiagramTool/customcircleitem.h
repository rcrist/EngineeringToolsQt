#ifndef CUSTOMCIRCLEITEM_H
#define CUSTOMCIRCLEITEM_H

#include <QGraphicsEllipseItem>
#include "scene.h"
#include "math.h"

class CustomCircleItem : public QGraphicsEllipseItem
{
public:
    CustomCircleItem(const QRect& rect, QGraphicsItem* parent = 0);
    QColor penColor;
    QColor brushColor;
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
};

#endif // CUSTOMCIRCLEITEM_H
