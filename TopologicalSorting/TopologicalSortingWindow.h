#pragma once
#include <QMainWindow>
#include <QPainter>
#include <stack>
#include "Graph.h"

class TopologicalSortingWindow : public QMainWindow
{
    Q_OBJECT

public:
    TopologicalSortingWindow(QWidget* parent = nullptr);
    void setTopologicalSorting(const Graph& graph);
protected:
    virtual void paintEvent(QPaintEvent* event);
private:
    Graph m_graph;
};

