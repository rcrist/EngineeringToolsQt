#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Initialize the MainWindow parameters: Title and Center in Screen
    this->setWindowTitle("Engineering Tools: Diagram Tool");
    this->move(screen()->geometry().center() - frameGeometry().center());

    // Create the scene and view
    scene = new Scene(this);
    scene->setSceneRect(0,0,800,600);
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

    rectAction = new QAction("Rect",this);
    rectAction->setData(int(Scene::DrawRect));
    rectAction->setIcon(QIcon(":/icons/rect.png"));
    rectAction->setCheckable(true);

    circAction = new QAction("Circ",this);
    circAction->setData(int(Scene::DrawCirc));
    circAction->setIcon(QIcon(":/icons/circ.png"));
    circAction->setCheckable(true);

    triAction = new QAction("Tri",this);
    triAction->setData(int(Scene::DrawTri));
    triAction->setIcon(QIcon(":/icons/tri.png"));
    triAction->setCheckable(true);

    penAction = new QAction("Pen",this);
    penAction->setData(int(Scene::SetPen));
    penAction->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(selectAction);
    actionGroup->addAction(rectAction);
    actionGroup->addAction(circAction);
    actionGroup->addAction(triAction);
    actionGroup->addAction(penAction);
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
    drawingToolBar->addAction(rectAction);
    drawingToolBar->addAction(circAction);
    drawingToolBar->addAction(triAction);
    drawingToolBar->addAction(penAction);
}
