#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Graph.h"
#include <QPainter>
#include <QPushButton>
#include <algorithm>
#include <QPainterPath>
#include <unordered_set>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    Graph graph,reverseGraph;
};
