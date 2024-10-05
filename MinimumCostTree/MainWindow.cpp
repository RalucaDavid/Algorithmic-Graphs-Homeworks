#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Generic = new QPushButton("Generic", this);
    Boruvka = new QPushButton("Boruvka", this);
    Generic->move(20,20);
    Boruvka->move(20,50);
    connect(Generic, SIGNAL(clicked()), this, SLOT(runGeneric()));
    connect(Boruvka, SIGNAL(clicked()), this, SLOT(runBoruvka()));
}

MainWindow::~MainWindow()
{}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
        if (event->button() == Qt::RightButton)
        {
            graph.AddNode(event->pos());
            update();
        }
        else if (event->button() == Qt::LeftButton)
        {
            std::vector<Node*> nodes = graph.GetNodes();
            for (Node*& node : nodes)
            {
                if (fabs(node->GetPosition().x() - event->pos().x()) < 20 &&
                    fabs(node->GetPosition().y() - event->pos().y()) < 20)
                {
                    if (firstNode == nullptr)
                    {
                        firstNode = node;
                        update();
                    }
                    else
                    {
                        bool ok;
                        int cost = QInputDialog::getInt(this, tr("Introduce the cost"),tr("Cost:"), 0, 0, 100, 1, &ok);
                        if (ok)
                        {
                            graph.AddArch(firstNode, node, cost);
                            firstNode = nullptr;
                            update();
                        }
                    }
                    break;
                }
            }
        }
}


void MainWindow::paintEvent(QPaintEvent* event)
{
        QPainter paint(this);
        std::vector<Node*> nodes = graph.GetNodes();
        for (Node*& node : nodes)
        {
            QRect rectangle(node->GetPosition().x() - 10, node->GetPosition().y() - 10, 20, 20);
            QString string;
            string.setNum(node->GetValue());
            if (firstNode == node)
            {
                paint.setPen(Qt::black);
                paint.setBrush(Qt::green);
            }
            else
            {
                paint.setPen(Qt::black);
                paint.setBrush(Qt::white);
            }
            paint.drawEllipse(rectangle);
            paint.drawText(rectangle, Qt::AlignCenter, string);
        }
        std::vector<Arch*> arches = graph.GetAches();
        for (Arch*& arch : arches)
        {
            int radius = 10;
            QPoint startP(arch->GetFirstNode()->GetPosition().x(), arch->GetFirstNode()->GetPosition().y());
            QPoint endP(arch->GetSecondNode()->GetPosition().x(), arch->GetSecondNode()->GetPosition().y());
            double angle = std::atan2(endP.y() - startP.y(), endP.x() - startP.x());
            startP.setX(startP.x() + radius * cos(angle));
            startP.setY(startP.y() + radius * sin(angle));
            endP.setX(endP.x() - radius * cos(angle));
            endP.setY(endP.y() - radius * sin(angle));
            if (arch->GetColor() == 1)
                paint.setPen(Qt::green);
            else if (arch->GetColor() == 2)
                paint.setPen(Qt::red);
            else
                paint.setPen(Qt::black);
            paint.drawLine(startP, endP);

            QString costString = QString::number(arch->GetCost());
            QPoint textPos((startP.x() + endP.x()) / 2, (startP.y() + endP.y()) / 2);
            paint.setPen(Qt::black);
            paint.drawText(textPos, costString);
        }
}

void MainWindow::runBoruvka()
{
    for (Arch*& arch : graph.GetAches())
    {
        arch->SetColor(0);
    }
    graph.Boruvka();
    update();
}

void MainWindow::runGeneric()
{
    for (Arch*& arch : graph.GetAches())
    {
        arch->SetColor(0);
    }
    graph.Generic();
    update();
}


