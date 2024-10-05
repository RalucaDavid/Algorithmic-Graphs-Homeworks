#include "TopologicalSortingWindow.h"

TopologicalSortingWindow::TopologicalSortingWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Topological Sorting");
}

void TopologicalSortingWindow::setTopologicalSorting(const Graph& graph)
{
    m_graph = graph;
}

void TopologicalSortingWindow::paintEvent(QPaintEvent* event)
{
    QPainter paint(this);
    std::vector<Arch> arches = m_graph.getArchesTS();
    std::vector<Node*> nodes = m_graph.getNodes();
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
    for (Arch& arch : arches)
    {
        int radius = 15;
        QPoint startP(arch.getSourceNode()->getCoord().second * 100 + 45, arch.getSourceNode()->getCoord().first * 100 + 45);
        QPoint endP(arch.getDestinationNode()->getCoord().second * 100 + 45, arch.getDestinationNode()->getCoord().first * 100 + 45);
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
