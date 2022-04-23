#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>
#include <QApplication>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {NoMode, SelectObject, DrawLine, DrawRect1, DrawRect2};
    explicit Scene(QObject *parent = 0);
    int getGridSize() const {return this->gridSize;}
    void setMode(Mode mode);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void drawBackground (QPainter* painter, const QRectF &rect);
    void SnapToGrid(qreal &x, qreal &y);
private:
    Mode sceneMode;
    QPointF origPoint;
    QPointF endPoint;
    QPoint snapOrigPoint;
    QPoint snapEndPoint;
    QGraphicsLineItem* itemToDraw;
    void makeItemsControllable(bool areControllable);
    int gridSize;
};

#endif // SCENE_H
