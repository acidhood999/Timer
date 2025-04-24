#include "Timer.h"
#include <QtWidgets/QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Timer w;
    a.setWindowIcon(QIcon("icon_app.ico"));
    w.show();

    return a.exec();
}

Timer::Timer(QWidget* parent) : QMainWindow(parent)
{
    widget = new QWidget(this);
    setCentralWidget(widget);
    setFixedSize(200, 60);
    //
    btn1 = new QPushButton("ON");
    btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn1->setFixedWidth(50);
    //
    line = new QLineEdit;
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //
    QFont font = QApplication::font();
    font.setBold(true);
    font.setPointSize(14);
    QApplication::setFont(font);
    //
    line->setValidator(new QIntValidator(this));
    //
    layout = new QGridLayout(widget);
    //
    layout->setSpacing(5);
    //
    layout->addWidget(line, 0, 0);  
    layout->addWidget(btn1, 0, 1);   
    //
    layout->setColumnStretch(0, 1);
    //
    line->setAlignment(Qt::AlignCenter);    
    //
    connect(btn1, &QPushButton::clicked, this, &Timer::onClick);
    

 
   
    

}

void Timer::onClick()
{
    if (btn1->text() == "ON")
    {
        
        converttime = line->text().toInt();
        converttime = (converttime * 60) * 60;
        if (converttime != 0)
        {
            hours = "shutdown /s /t ";
            hours += QString::number(converttime);
            const string a = hours.toStdString();
            system(a.c_str());
            btn1->setText("OFF");
            converttime = 0;
        }
        else
        {
            msgBox = new QMessageBox;  
            msgBox->setText("ERROR"); 
            msgBox->exec();
        }

        converttime = 0;
        line->clear();
    }
    else
    {
        btn1->setText("ON");
        system("shutdown /a");
    }
}

Timer::~Timer()
{
    if (msgBox) 
    {
        delete msgBox;
    }
}