#pragma once

#include <QString>
#include <string>
#include <QtWidgets/QMainWindow>
#include <QLineEdit> 
#include <QPushButton>
#include <QGridLayout>
#include <QFont>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QStyle>
#include <QPointer>
#include <QtWidgets/QApplication>
#include <iostream>
#include <QRegularExpression>
#include <QGroupBox>
#include <QSettings>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>

class Timer : public QMainWindow
{
    Q_OBJECT

public:
    Timer(QWidget *parent = nullptr);
    ~Timer();
protected:
    void keyPressEvent(QKeyEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private slots:

    void onClick(); 
    void onTextChanged(const QString& arg1);

private:
    QPointer<QWidget> widget = nullptr;
    QPointer<QLineEdit> line = nullptr;
    QPointer<QPushButton> btn1 = nullptr;
    QPointer<QPushButton> btn2 = nullptr;
    QPointer<QPushButton> btn3 = nullptr;
    QPointer<QPushButton> btn4 = nullptr;
    QPointer<QPushButton> btn5 = nullptr;
    QPointer<QPushButton> btn6 = nullptr;
    QPointer<QGridLayout> layout = nullptr;
    QPointer<QMessageBox> msgBox = nullptr;
    QPointer<QSystemTrayIcon> trayIcon = nullptr;
  
    QString hours;
   
    int converttime = 0;
    void setupPresetButton(QPushButton* btn, QString timeStr);
    void settingsWindow(); 
    void initializationButton(const QFont& font);
    void saveAction();
    void updateStyles();
};
