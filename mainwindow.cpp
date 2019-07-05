#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    university = University::GetUniversity();

    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ActionTimer()));
    timer->start(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActionTimer()
{
    university->update();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));

    char** table = university->GetMap();
    vector<Student*> liststudents = university->GetListStudent();
    vector<Stall*> liststore = university->GetListStall();
    int width = university->GetMapWidth();
    int length = university->GetMapLength();

    //Отображение текстовой информации.
    QString status;
    if (university->GetStatus())
        status = "Пары";
    else
        status = "Перемена";
    QString time(to_string(university->GetTime()).c_str());
    QString store("Состояние магазинов: ");
    for (int i = 0; i < liststore.size(); i++)
    {
        store += to_string(liststore[i]->GetCountBun()).c_str();
        store += " ";
    }
    ui->textBrowser->setText("Сейчас идёт " + status + ", времени осталось: " + time + ".\n" + store);



    int starty = 50;

    //Рисование карты.
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (table[i][j] == '1' || table[i][j] == '4')
                painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
            else
            if (table[i][j] == '2')
                painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            else
            if (table[i][j] == '3')
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            else
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawRect(j * 50,starty + i * 50, 50, 50);

        }
    }

    //Рисование студентов.
    for (int i = 0; i < liststudents.size(); i++)
    {
        int x = liststudents[i]->GetX();
        int y = liststudents[i]->GetY();
        int widthcircles = liststudents[i]->GetWidth();
        int satiety = liststudents[i]->GetSatiety();
        painter.setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::FlatCap));
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.drawEllipse(QPointF(y * 50 + 25,starty + x * 50 + 25), widthcircles / 2, widthcircles / 2);
        painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawEllipse(QPointF(y * 50 + 25,starty + x * 50 + 25), widthcircles * satiety / 200, widthcircles * satiety / 200);

    }
}
