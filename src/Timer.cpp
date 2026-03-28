#include "Timer.h"
#include <QtWidgets/QApplication>
#include <QRegularExpression>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QGridLayout>
#include <QGroupBox>
#include <QSettings>
#include <QDateTime>

using namespace std;

Timer::Timer(QWidget* parent) : QMainWindow(parent)
{
    widget = new QWidget(this);
    setCentralWidget(widget);

    settingsWindow();

    btn1 = new QPushButton("ON");
    btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn1->setFixedWidth(50);

    btn2 = new QPushButton("15m");
    btn2->setFixedWidth(50);

    btn3 = new QPushButton("30m");
    btn3->setFixedWidth(50);

    btn4 = new QPushButton("1h");
    btn4->setFixedWidth(50);

    btn5 = new QPushButton("2h");
    btn5->setFixedWidth(50);

    line = new QLineEdit;
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //

    QSettings settings("acidhood", "Timer");

   
    bool isActive = settings.value("timerActive", false).toBool();

    if (isActive)
    {
        btn1->setText("OFF");
        QString savedTime = settings.value("lastTime", "00d 00h 00m 00s").toString();
        line->setText(savedTime);
    }
    else btn1->setText("ON");

    //
    QFont font = QApplication::font();
    font.setPointSize(14);
    line->setFont(font);

 
    line->setStyleSheet("border-bottom: none");
    line->setStyleSheet(
        "QLineEdit {"
        "border: 1px solid black;"
        "border-radius: 5px;"
        "padding: 2px 5px;"
        "}"
    );




    //
    line->setText("00d 00h 00m 00s");
    line->setAlignment(Qt::AlignCenter);
    line->setContextMenuPolicy(Qt::NoContextMenu);
    //

    QGroupBox* group = new QGroupBox(widget);
    group->setStyleSheet(R"(
    QGroupBox {
        border: 1px solid gray;
        border-radius: 9px;
        margin-top: 10px;
    }

    QGroupBox::title {
       subcontrol-origin: margin;
       left: 10px;
       padding: 0 3px 0 3px;
    })");    

    QHBoxLayout* groupLayout = new QHBoxLayout(group);
    groupLayout->addWidget(line);
    groupLayout->addWidget(btn1);

    layout = new QGridLayout(widget);
    layout->setSpacing(10);

    layout->addWidget(group, 0, 0, 1, 4);

    layout->addWidget(btn2, 1, 0);
    layout->addWidget(btn3, 1, 1);
    layout->addWidget(btn4, 1, 2);
    layout->addWidget(btn5, 1, 3);
    layout->setColumnStretch(0, 1);
    //
    connect(line, &QLineEdit::textEdited, this, &Timer::onTextChanged);
    connect(btn1, &QPushButton::clicked, this, &Timer::onClick);




    connect(btn2, &QPushButton::clicked, this, [this]() 
    {
        QString cmd = "shutdown /s /t " + QString::number(900);
        if (system(cmd.toStdString().c_str()) == 0) saveOff();
        else  QMessageBox::critical(this, "ERROR", "Failed to start timer!");
    });
    connect(btn3, &QPushButton::clicked, this, [this]() 
    {
        QString cmd = "shutdown /s /t " + QString::number(1800);
        if (system(cmd.toStdString().c_str()) == 0) saveOff();
        else QMessageBox::critical(this, "ERROR", "Failed to start timer!");
    });
    connect(btn4, &QPushButton::clicked, this, [this]()
    {
        QString cmd = "shutdown /s /t " + QString::number(3600);
        if (system(cmd.toStdString().c_str()) == 0)  saveOff();
        else QMessageBox::critical(this, "ERROR", "Failed to start timer!");
    });
    connect(btn5, &QPushButton::clicked, this, [this]() 
    {
        QString cmd = "shutdown /s /t " + QString::number(7200);
        if (system(cmd.toStdString().c_str()) == 0)   saveOff();
        else QMessageBox::critical(this, "ERROR", "Failed to start timer!");
    });
}


void Timer::onTextChanged(const QString& arg1)
{
    static int lastDigitsCount = 0;

    //
    QString digits = arg1;
    digits.remove(QRegularExpression("\\D"));
    //
    if (arg1.length() < 15 && digits.length() >= lastDigitsCount && digits.length() > 0)
    {
        digits.chop(1);
    }

    //
    while (digits.startsWith('0') && digits.length() > 1)
    {
        digits.remove(0, 1);
    }

    //
    if (digits.length() > 8) 
    {
        digits = digits.left(8);
    }

    //
    lastDigitsCount = digits.length();
    //
    QString padded = digits.rightJustified(8, '0');
    // 
    QString d = padded.mid(0, 2);
    QString h = padded.mid(2, 2);
    QString m = padded.mid(4, 2);
    QString s = padded.mid(6, 2);

    QString formatted = QString("%1d %2h %3m %4s").arg(d, h, m, s);
    //
    line->blockSignals(true);
    line->setText(formatted);
    line->setCursorPosition(formatted.length());
    line->blockSignals(false);
}

void Timer::onClick()
{
    QSettings settings("acidhood", "Timer");
    if (btn1->text() == "ON")
    {
       
        QString digits = line->text().remove(QRegularExpression("\\D"));

        long d = digits.mid(0, 2).toLong();
        long h = digits.mid(2, 2).toLong();
        long m = digits.mid(4, 2).toLong();
        long s = digits.mid(6, 2).toLong();

  
        long totalSeconds = s + (m * 60) + (h * 3600) + (d * 86400);

        if (totalSeconds > 0)
        {
            QString cmd = "shutdown /s /t " + QString::number(totalSeconds);
            if (system(cmd.toStdString().c_str()) == 0) 
            {
                btn1->setText("OFF");
                settings.setValue("timerActive", true);
                settings.setValue("lastTime", line->text());
            }
            else 
            {
                QMessageBox::critical(this, "ERROR", "Failed to start timer!");
            }
        }
        else
        {
            QMessageBox::warning(this, "ERROR", "Enter the time!");
        }
    }
    else
    {
        if (system("shutdown /a") == 0) 
        {
            btn1->setText("ON");
            settings.setValue("timerActive", false);
        }
    }
}

Timer::~Timer()
{}

void Timer::saveOff()
{
    QSettings settings("acidhood", "Timer");
    btn1->setText("OFF");
    settings.setValue("timerActive", true);
    settings.setValue("lastTime", line->text());
}

void Timer::settingsWindow()
{
    setFixedSize(320, 150);
    setWindowTitle("Timer");
}