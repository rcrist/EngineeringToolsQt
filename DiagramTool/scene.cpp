#include "scene.h"
#include "CustomRectItem.h"
#include <math.h>

Scene::Scene(QObject* parent):
    QGraphicsScene(parent), gridSize(10)
{
    sceneMode = NoMode;
    itemToDraw = 0;
    Q_ASSERT(gridSize > 0);
}

void Scene::setMode(Mode mode){
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject){
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
    }
    else if(mode == DrawRect){
        CustomRectItem* rectItem = new CustomRectItem(QRect(0,0,80,80));
        rectItem->setPos(50,50);
        rectItem->setBrush(Qt::gray);
        this->addItem(rectItem);
    }
    else if(mode == DrawCirc){
        QGraphicsEllipseItem* circItem = new QGraphicsEllipseItem(QRect(0,0,40,40));
        circItem->setPos(150,150);
        circItem->setBrush(Qt::blue);
        circItem->setFlags(QGraphicsItem::ItemIsSelectable |
                           QGraphicsItem::ItemIsMovable |
                           QGraphicsItem::ItemSendsGeometryChanges);
        this->addItem(circItem);
    }
    else if(mode == DrawTri){
        QPainterPath* path = new QPainterPath();
        path->moveTo(0,0);
        path->lineTo(30,60);
        path->lineTo(60,0);
        path->lineTo(0,0);

        QGraphicsPathItem* triItem = new QGraphicsPathItem();
        triItem->setPath(*path);
        triItem->setPos(200,200);
        triItem->setFlags(QGraphicsItem::ItemIsSelectable |
                          QGraphicsItem::ItemIsMovable |
                          QGraphicsItem::ItemSendsGeometryChanges);
        triItem->setBrush(Qt::green);
        this->addItem(triItem);
    }
    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::makeItemsControllable(bool areControllable){
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Scene::SnapToGrid(qreal &x, qreal &y) // C++ pass arguments by reference
{
    int grid_gap = getGridSize();

    x = grid_gap * round(x / grid_gap);
    y = grid_gap * round(y / grid_gap);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine)
    {
        origPoint = event->scenePos(); // Get the mouse position
        qreal x = origPoint.x();
        qreal y = origPoint.y();
        SnapToGrid(x, y);
        snapOrigPoint.setX((int)x);
        snapOrigPoint.setY((int)y);

    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawLine){
        if(!itemToDraw){
            itemToDraw = new QGraphicsLineItem;
            this->addItem(itemToDraw);
            itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));
            itemToDraw->setPos(snapOrigPoint);
        }
        endPoint = event->scenePos(); // Get the mouse position
        qreal x = endPoint.x();
        qreal y = endPoint.y();
        SnapToGrid(x, y);
        snapEndPoint.setX((int)x);
        snapEndPoint.setY((int)y);

        itemToDraw->setLine(0,0,
                            snapEndPoint.x() - snapOrigPoint.x(),
                            snapEndPoint.y() - snapOrigPoint.y());
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    itemToDraw = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else
        QGraphicsScene::keyPressEvent(event);
}

// Draws the background of the scene using painter, before any items and the foreground are drawn.
// Background is drawn automatically on resize events
void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setWidth(2);
    pen.setCosmetic(true);
    painter->setPen(pen);

    int left = int(rect.left()) - (int(rect.left()) % gridSize);
    int top = int(rect.top()) - (int(rect.top()) % gridSize);

    QVector<QPointF> points;
    for (int x = left; x < rect.right(); x += gridSize){
        for (int y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

