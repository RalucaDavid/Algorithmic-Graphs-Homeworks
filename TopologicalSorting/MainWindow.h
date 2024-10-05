#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Graph.h"
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include "TopologicalSortingWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    ~MainWindow();
private slots:
    void startPTDF();
private:
    Ui::MainWindowClass ui;
    Graph graph;
    bool checkCircuits;
    QPushButton* PTDF;
    TopologicalSortingWindow* sortingWindow;
};
