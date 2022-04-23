#include "customtriangleitem.h"

CustomTriangleItem::CustomTriangleItem(QGraphicsItem* parent):
    QGraphicsPathItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);

    QPainterPath* path = new QPainterPath();
    path->moveTo(0,0);
    path->lineTo(30,-60);
    path->lineTo(60,0);
    path->lineTo(0,0);
    this->setPath(*path);

    penColor = QColor(Qt::black);
    brushColor = QColor(Qt::green);
}

QVariant CustomTriangleItem::itemChange(GraphicsItemChange change,
                                        const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<Scene*> (scene())){
            Scene* customScene = qobject_cast<Scene*> (scene());
            int gridSize = customScene->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}
