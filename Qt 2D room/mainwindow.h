#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPair>
#include <QVector>
#include <ctime>
#include <QFrame>
#include "smartpointer.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    int a, b;
    **room;

    QVector <QPair<int, int>> p;
    QFile *f;

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Work ();
    void FillRoom (QFrame *temp, int x, int y);
    void GenerationXY (int &x, int &y);
    bool Check (int x, int y);
    void ChangePair();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
