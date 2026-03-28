#include "Timer.h"
#include <QtWidgets/QApplication>
#include <QRegularExpression>
#include <QMessageBox>
#include <iostream>
#include <string>

using namespace std;

Timer::Timer(QWidget* parent) : QMainWindow(parent)
{
    widget = new QWidget(this);
    setCentralWidget(widget);

    settingsWindow();

    btn1 = new QPushButton("ON");
    btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn1->setFixedWidth(50);

    line = new QLineEdit;
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //
    QFont font = QApplication::font();
    font.setBold(true);
    font.setPointSize(14);
    line->setFont(font);
    //
    line->setText("00d 00h 00m 00s");
    line->setAlignment(Qt::AlignCenter);
    line->setContextMenuPolicy(Qt::NoContextMenu);
    //
    layout = new QGridLayout(widget);
    layout->setSpacing(5);
    layout->addWidget(line, 0, 0);
    layout->addWidget(btn1, 0, 1);
    layout->setColumnStretch(0, 1);
    //
    connect(line, &QLineEdit::textEdited, this, &Timer::onTextChanged);
    connect(btn1, &QPushButton::clicked, this, &Timer::onClick);
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
        }
    }
}

Timer::~Timer()
{}

void Timer::settingsWindow()
{
    setFixedSize(260, 70);
    setWindowTitle("Timer");
}