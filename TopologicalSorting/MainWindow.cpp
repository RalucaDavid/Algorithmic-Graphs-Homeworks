#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    graph.CreateGraph();
    PTDF = new QPushButton("PTDF",this);
    PTDF->move(10, 10);
    sortingWindow = new TopologicalSortingWindow();
    connect(PTDF, SIGNAL(clicked()), this, SLOT(startPTDF()));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter paint(this);
    std::vector<Node*> nodes = graph.getNodes();
    std::vector<Arch*> arches = graph.getArches();
    for (Node*& node : nodes)
    {
        QRect rectangle(node->getCoord().second * 100 + 30, node->getCoord().first * 100 + 30, 30, 30);
        QString string;
        string.setNum(node->getValue());
        paint.setPen(Qt::black);
        paint.setBrush(Qt::white);
        paint.drawEllipse(rectangle);
        paint.drawText(rectangle, Qt::AlignCenter, string);
    }
    for (Arch*& arch : arches)
    {
        int radius = 15;
        QPoint startP(arch->getSourceNode()->getCoord().second * 100 + 45, arch->getSourceNode()->getCoord().first * 100 + 45);
        QPoint endP(arch->getDestinationNode()->getCoord().second * 100 + 45, arch->getDestinationNode()->getCoord().first * 100 + 45);
        double angle = std::atan2(endP.y() - startP.y(), endP.x() - startP.x());
        startP.setX(startP.x() + radius * cos(angle));
        startP.setY(startP.y() + radius * sin(angle));
        endP.setX(endP.x() - radius * cos(angle));
        endP.setY(endP.y() - radius * sin(angle));
        paint.drawLine(startP, endP);
        int sizeArrow = 10;
        paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle - M_PI / 6), endP.y() - sizeArrow * std::sin(angle - M_PI / 6));
        paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle + M_PI / 6), endP.y() - sizeArrow * std::sin(angle + M_PI / 6));
    }
}

void MainWindow::startPTDF()
{
    checkCircuits = graph.PTDF();
    if (checkCircuits)
    {
        QMessageBox::information(this, "No Cycle", "The graph does not contain a cycle.");
        sortingWindow->setTopologicalSorting(graph);
        sortingWindow->show();
    }
    else 
        QMessageBox::critical(this, "Cycle Detected", "The graph contains a cycle.");
}

MainWindow::~MainWindow()
{
    delete PTDF;
}
