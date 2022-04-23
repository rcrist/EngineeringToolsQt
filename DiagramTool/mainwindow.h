#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include "scene.h"
#include "customrectitem.h"
#include <QAction>
#include <QActionGroup>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
public slots:
    void actionGroupClicked(QAction*);
private:
    QGraphicsView* view;
    Scene* scene;

    void createActions();
    void createConnections();
    void createToolBar();

    QAction* lineAction;
    QAction* selectAction;
    QAction* rect1Action;
    QAction* rect2Action;
    QActionGroup* actionGroup;
    QToolBar* drawingToolBar;
};

#endif // MAINWINDOW_H
