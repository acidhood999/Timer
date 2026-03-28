#include "Timer.h"


using namespace std;

Timer::Timer(QWidget* parent) : QMainWindow(parent)
{
    widget = new QWidget(this);
    setCentralWidget(widget);

    settingsWindow();

    QFont mainFont("Consolas", 12);
    QFont timerFont("Consolas", 22, QFont::Bold);

    line = new QLineEdit(widget);
    initializationButton(mainFont);
    //
    line->setFixedHeight(60);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setReadOnly(true);
    line->setFocusPolicy(Qt::StrongFocus);
    line->installEventFilter(this);
    line->setFont(timerFont);
    line->setText("00d 00h 00m 00s");
    line->setAlignment(Qt::AlignCenter);
    line->setContextMenuPolicy(Qt::NoContextMenu);
    line->setStyleSheet(
        "QLineEdit {"
        "  border: 1px solid #E0E0E0;"
        "  border-radius: 12px;"
        "  color: #1D1D1F;"
        "  background: #F8F9FA;" 
        "  padding: 5px;"
        "}"
        "QLineEdit:hover {"
        "  background: #FFFFFF;"    
        "  border: 1px solid #000000;" 
        "}"
        "QLineEdit:focus {"
        "  border: 2px solid #000000;" 
        "  background: #FFFFFF;"
        "}"
    );

    QPointer <QGroupBox> group = new QGroupBox(widget);
    group->setStyleSheet("border: none; margin: 0;");
    QPointer <QHBoxLayout> groupLayout = new QHBoxLayout(group);
    groupLayout->setContentsMargins(0, 0, 0, 0);
    groupLayout->setSpacing(10);
    groupLayout->addWidget(line);
    groupLayout->addWidget(btn1);

  
    layout = new QGridLayout(widget);
    layout->setContentsMargins(15, 15, 15, 15); 
    layout->setSpacing(8);                   
    layout->setVerticalSpacing(5);
    layout->addWidget(group, 0, 0, 1, 5);
    layout->addWidget(btn2, 1, 0);
    layout->addWidget(btn3, 1, 1);
    layout->addWidget(btn4, 1, 2);
    layout->addWidget(btn5, 1, 3);
    layout->addWidget(btn6, 1, 4);

    saveAction();

    updateStyles();

    trayIcon = new QSystemTrayIcon(this);
    QIcon appIcon(":/new/prefix1/icon.ico");
    if (appIcon.isNull()) appIcon = style()->standardIcon(QStyle::SP_ComputerIcon);
    trayIcon->setIcon(appIcon);
    trayIcon->setToolTip("Timer");
    this->setWindowIcon(appIcon);

    QPointer <QMenu> trayMenu = new QMenu(this);
    QPointer <QAction> quitAction = new QAction("Exit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason)
    {
        if (reason == QSystemTrayIcon::Trigger) { this->showNormal(); this->activateWindow(); }
    });
    connect(line, &QLineEdit::textEdited, this, &Timer::onTextChanged);
    connect(btn1, &QPushButton::clicked, this, &Timer::onClick);

    setupPresetButton(btn2, "00d 00h 15m 00s");
    setupPresetButton(btn3, "00d 00h 30m 00s");
    setupPresetButton(btn4, "00d 00h 45m 00s");
    setupPresetButton(btn5, "00d 01h 00m 00s");
    setupPresetButton(btn6, "00d 02h 00m 00s");

    this->setFocus();
}

void Timer::onTextChanged(const QString& arg1)
{
    static int lastDigitsCount = 0;

    //
    QString digits = arg1;
    digits.remove(QRegularExpression("\\D"));
    //

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
                updateStyles(); 

                QDateTime deadline = QDateTime::currentDateTime().addSecs(totalSeconds);
                settings.setValue("timerActive", true);
                settings.setValue("deadline", deadline.toString(Qt::ISODate));
                settings.setValue("lastTime", line->text());

                line->setText("00d 00h 00m 00s");
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
            updateStyles(); 
            settings.setValue("timerActive", false);
        }
    }
}

void Timer::settingsWindow()
{
    setFixedSize(380, 140); 
    setWindowTitle("Timer");
    widget->setStyleSheet("background-color: #FFFFFF;");
}

void Timer::initializationButton(const QFont& font)
{
    btn1 = new QPushButton("ON");
    btn1->setFixedSize(70, 60);

    btn2 = new QPushButton("15m");
    btn3 = new QPushButton("30m");
    btn4 = new QPushButton("45m");
    btn5 = new QPushButton("1h");
    btn6 = new QPushButton("2h");

    QList<QPushButton*> allButtons = { btn1, btn2, btn3, btn4, btn5, btn6 };
    for (QPushButton* b : allButtons)
    {
        b->setFont(font);
        b->setFocusPolicy(Qt::NoFocus);
        b->setCursor(Qt::PointingHandCursor);
    }
}

void Timer::updateStyles()
{

    QString presetStyle = { "QPushButton { background-color: #F0F0F0; color: #555555; border: none; border-radius: 8px; padding: 8px; }"
        "QPushButton:hover { background-color: #E8E8E8; color: #000000; }"
        "QPushButton:pressed { background-color: #D0D0D0; }" };
     

    btn2->setStyleSheet(presetStyle);
    btn3->setStyleSheet(presetStyle);
    btn4->setStyleSheet(presetStyle);
    btn5->setStyleSheet(presetStyle);
    btn6->setStyleSheet(presetStyle);


    if (btn1->text() == "ON") 
    {
        btn1->setStyleSheet(
            "QPushButton {"
            "  background-color: #000000; color: #FFFFFF; border-radius: 12px; font-weight: bold; font-size: 20px;"
            "}"
            "QPushButton:hover { background-color: #333333; }"
        );
    }
    else
    {
        btn1->setStyleSheet(
            "QPushButton {"
            "  background-color: #FFFFFF; color: #FF3B30; border: 2px solid #FF3B30; border-radius: 12px; font-weight: bold; font-size: 20px;"
            "}"
            "QPushButton:hover { background-color: #FFF5F5; }"
        );
    }
}

void Timer::saveAction()
{
    QSettings settings("acidhood", "Timer");
    bool isActive = settings.value("timerActive", false).toBool();

    if (isActive)
    {
        QString deadlineStr = settings.value("deadline").toString();
        QDateTime deadline = QDateTime::fromString(deadlineStr, Qt::ISODate);

        if (deadline.isValid() && QDateTime::currentDateTime() < deadline) 
        {
            btn1->setText("OFF");
            updateStyles();
            QString savedTime = settings.value("lastTime", "00d 00h 00m 00s").toString();
            line->setText(savedTime);
        }
        else 
        {
            settings.setValue("timerActive", false);
            btn1->setText("ON");
            updateStyles();
            line->setText("00d 00h 00m 00s");
        }
    }
    else 
    {
        btn1->setText("ON");
        updateStyles();
    }
}

bool Timer::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == line && event->type() == QEvent::KeyPress) 
    {
        keyPressEvent(static_cast<QKeyEvent*>(event));
        return true; 
    }
    return QMainWindow::eventFilter(obj, event);
}

void Timer::closeEvent(QCloseEvent* event)
{
    if (trayIcon->isVisible()) 
    {
        this->hide();
        trayIcon->showMessage("Timer", "App is still running in tray", QSystemTrayIcon::Information, 2000);
        event->ignore(); 
    }
}


void Timer::keyPressEvent(QKeyEvent* event)
{
    QString digits = line->text().remove(QRegularExpression("\\D"));
    while (digits.startsWith('0') && digits.length() > 0) 
    {
        digits.remove(0, 1);
    }

    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) 
    {
        if (digits.length() < 8)
        {
            digits += event->text();
            onTextChanged(digits);
        }
    }
    else if (event->key() == Qt::Key_Backspace)
    {
        if (!digits.isEmpty()) 
        {
            digits.chop(1); 
            onTextChanged(digits);
        }
    }
}

void Timer::setupPresetButton(QPushButton* btn, QString timeStr)
{
    connect(btn, &QPushButton::clicked, this, [this, timeStr]()
    {
        line->setText(timeStr);
        if (btn1->text() == "OFF") system("shutdown /a");
        onClick();
    });
}

Timer::~Timer()
{}
