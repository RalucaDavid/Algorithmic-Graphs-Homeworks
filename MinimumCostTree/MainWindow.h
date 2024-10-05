#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Graph.h"
#include <QMouseEvent>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QObject>
#include <QCoreApplication>
#include <math.h>
#include <QInputDialog>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);
private slots:
    void runGeneric();
    void runBoruvka();
private:
    Ui::MainWindowClass ui;
    Graph graph;
    Node* firstNode=nullptr;
    QPushButton* Generic, * Boruvka;
};
