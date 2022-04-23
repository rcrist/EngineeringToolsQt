#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Initialize the MainWindow parameters: Title and Center in Screen
    this->setWindowTitle("Engineering Tools: Diagram Tool");
    this->move(screen()->geometry().center() - frameGeometry().center());

    // Create the scene and view
    scene = new Scene(this);
    scene->setSceneRect(0,0,400,400);
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
    setCentralWidget(view);

    // Setup toolbar
    createActions();
    createConnections();
    createToolBar();

}

void MainWindow::createActions(){
    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setIcon(QIcon(":/icons/line.png"));
    lineAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setIcon(QIcon(":/icons/select.png"));
    selectAction->setCheckable(true);

    rect1Action = new QAction("Rect1",this);
    rect1Action->setData(int(Scene::DrawRect1));;
    rect1Action->setCheckable(true);

    rect2Action = new QAction("Rect2",this);
    rect2Action->setData(int(Scene::DrawRect2));;
    rect2Action->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(selectAction);
    actionGroup->addAction(rect1Action);
    actionGroup->addAction(rect2Action);
}

void MainWindow::createConnections(){
    connect(actionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionGroupClicked(QAction*)));
}

void MainWindow::actionGroupClicked(QAction *action){
    scene->setMode(Scene::Mode(action->data().toInt()));
}

void MainWindow::createToolBar(){
    drawingToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, drawingToolBar);
    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);
    drawingToolBar->addAction(rect1Action);
    drawingToolBar->addAction(rect2Action);
}
