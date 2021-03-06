#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QGraphicsRectItem>
#include "scene.h"
#include "math.h"

class CustomRectItem : public QGraphicsRectItem
{
public:
    CustomRectItem(const QRect& rect, QGraphicsItem* parent = 0);
    QColor penColor;
    QColor brushColor;
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
};

#endif // CUSTOMRECTITEM_H
