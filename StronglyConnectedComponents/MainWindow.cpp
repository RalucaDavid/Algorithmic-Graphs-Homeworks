#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    graph.CreateGraph();
    reverseGraph.CreateReversal();
    graph.PTDF();
    reverseGraph.PTDF2(graph.getT2());
}

std::pair<bool, std::pair<int, int>> VerifyConexComponents(Node* node1, Node* node2, const std::vector<std::vector<Node*>>& conexComponents) 
{
    int indexNode1 = -1;
    int indexNode2 = -1;
    for (int i = 0; i < conexComponents.size(); ++i) 
    {
        const auto& component = conexComponents[i];
        auto itNode1 = std::find_if(component.begin(), component.end(), [node1](Node* node) {
            return node->getValue() == node1->getValue();
            });
        auto itNode2 = std::find_if(component.begin(), component.end(), [node2](Node* node) {
            return node->getValue() == node2->getValue();
            });
        if (itNode1 != component.end()) 
        {
            indexNode1 = i;
        }

        if (itNode2 != component.end()) 
        {
            indexNode2 = i;
        }
    }
    if (indexNode1 != -1 && indexNode2 != -1 && indexNode1 != indexNode2) 
    {
        return { true, { indexNode1, indexNode2 } };
    }
    return { false, { -1, -1 } };
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter paint(this);
    std::vector<Arch*> arches = graph.getArches();
    std::vector<std::vector<Node*>> conexComponents= reverseGraph.getConexComponents();
    std::vector<std::pair<int,int>> coords;
    int nodeWidth = 30; 
    int nodeHeight = 30;
    int rowSpacing = 40;
    int valueSpacing = 3; 
    std::random_device rd;
    std::mt19937 gen(rd());
    for (const auto& row : conexComponents)
    {
        int x = std::uniform_int_distribution<>(0, 800)(gen);
        int y = std::uniform_int_distribution<>(0, 600)(gen);
        coords.push_back({ y,x });
        QRect rowRectangle(x, y, row.size() * nodeWidth, nodeHeight);
        paint.setPen(Qt::black);
        paint.setBrush(Qt::white);
        paint.drawEllipse(rowRectangle);
        int nodeX = x;
        for (Node* node : row)
        {
            QRect nodeRectangle(nodeX, y, nodeWidth, nodeHeight);
            QString string;
            string.setNum(node->getValue());
            paint.drawText(nodeRectangle, Qt::AlignCenter, string);
            nodeX += nodeWidth + valueSpacing;
        }
    }
    for (Arch* arch : arches)
    {
        std::pair<bool, std::pair<int, int>> verify = VerifyConexComponents(arch->getSourceNode(),arch->getDestinationNode(), conexComponents);
        if (verify.first == true)
        {
            int radius = 15;
            int nodeWidth = 30; 
            int nodeHeight = 30; 
            QPoint startP(coords[verify.second.first].second + nodeWidth / 2, coords[verify.second.first].first + nodeHeight / 2);
            QPoint endP(coords[verify.second.second].second + nodeWidth / 2, coords[verify.second.second].first + nodeHeight / 2);
            double angle = std::atan2(endP.y() - startP.y(), endP.x() - startP.x());
            startP.setX(startP.x() + radius * std::cos(angle));
            startP.setY(startP.y() + radius * std::sin(angle));
            endP.setX(endP.x() - radius * std::cos(angle));
            endP.setY(endP.y() - radius * std::sin(angle));
            paint.drawLine(startP, endP);
            int sizeArrow = 10;
            paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle - M_PI / 6), endP.y() - sizeArrow * std::sin(angle - M_PI / 6));
            paint.drawLine(endP.x(), endP.y(), endP.x() - sizeArrow * std::cos(angle + M_PI / 6), endP.y() - sizeArrow * std::sin(angle + M_PI / 6));
        }
    }
}

MainWindow::~MainWindow()
{
}
