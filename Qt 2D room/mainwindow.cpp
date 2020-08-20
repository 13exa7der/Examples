#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    f = new QFile ("DataInput.txt");
    if (f->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString str;
        QTextStream stream (f);
        stream >> str;
        a = str.toInt();
        stream >> str;
        b = str.toInt();

        resize(a, b);

        int first, second;
        stream >> str;
        first = str.toInt();
        stream >> str;
        second = str.toInt();
        while (str != "")
        {
            p.push_back(QPair <int, int> (first, second));
            stream >> str;
            first = str.toInt();
            stream >> str;
            second = str.toInt();
        }


        room = new int* [b];
        for (int i =0; i<b; i++)
        {
            room[i] = new int [a]{};
        }
    }

    f->close();
}


void MainWindow::Work()
{
    srand (time(NULL));
    int timecount = 1000000;
    while (p.size())
    {

        QFrame *temp = new QFrame (this);
        temp->show();

        while(true)
        {
            if (rand()%2)
            {
                ChangePair();
            }
            int x, y;
            GenerationXY(x, y);
            if (Check(x, y))
            {
                FillRoom(temp, x, y);
                p.pop_front();
                break;
            }
        }
        --timecount;
        if (!timecount)
        {
            close();
            break;
        }

    }
}

void MainWindow::FillRoom (QFrame *temp, int x, int y)
{
    for (int j =y; j<(y+p[0].first); j++)
    {
        for (int k =x; k<(x+p[0].second); k++)
        {
            room[j][k] = 1;
        }
    }
    temp->setStyleSheet("background: blue");
    temp->setGeometry(x, y, p[0].second, p[0].first);

    temp->setFrameShape(QFrame::Box);
    temp-> setLineWidth(3);
}

void MainWindow::GenerationXY (int &x, int &y)
{
    switch (rand()%9) {
    case 0:
        x = 0;
        y = 0;
        break;
    case 1:
        x=0;
        y=b-p[0].first;
        break;
    case 2:
        x=a-p[0].second;
        y=0;
        break;
    case 3:
        x=a-p[0].second;
        y=b-p[0].first;
        break;
    case 4:
        x = 0;
        y = rand()%(b-p[0].first);
        break;
    case 5:
        x= rand()%(a-p[0].second);
        y=b-p[0].first;
        break;
    case 6:
        x= rand()%(a-p[0].second);
        y=0;
        break;
    case 7:
        x=a-p[0].second;
        y = rand()%(b-p[0].first);
        break;
    case 8:
        x= rand()%(a-p[0].second);
        y = rand()%(b-p[0].first);
        break;
    }

}

void MainWindow::ChangePair()
{
    int temp = p[0].first;
    p[0].first = p[0].second;
    p[0].second = temp;
}

bool MainWindow::Check(int x, int y)
{
    for (int j =y; j<(y+p[0].first); j++)
    {
        for (int k =x; k<(x+p[0].second); k++)
        {
            if (room[j][k]==1)
            {
                j =y;
                return 0;
            }
        }
    }
    return 1;
}

MainWindow::~MainWindow()
{
    for (int i =0; i<b; i++)
    {
        delete [] room[i];
    }
    delete[] room;

    delete ui;
}




