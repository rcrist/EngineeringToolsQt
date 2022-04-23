#ifndef CUSTOMTRIANGLEITEM_H
#define CUSTOMTRIANGLEITEM_H

#include <QGraphicsPathItem>
#include "scene.h"
#include "math.h"

class CustomTriangleItem : public QGraphicsPathItem
{
public:
    CustomTriangleItem(QGraphicsItem* parent = 0);
    QColor penColor;
    QColor brushColor;
protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);
};

#endif // CUSTOMTRIANGLEITEM_H
