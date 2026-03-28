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
    QWidget* widget = nullptr;
    QLineEdit* line = nullptr;
    QPushButton* btn1 = nullptr;
    QPushButton* btn2 = nullptr;
    QPushButton* btn3 = nullptr;
    QPushButton* btn4 = nullptr;
    QPushButton* btn5 = nullptr;
    QPushButton* btn6 = nullptr;
    QGridLayout* layout = nullptr;
    QMessageBox* msgBox = nullptr;
    QSystemTrayIcon* trayIcon = nullptr;
  
    QString hours;
   
    int converttime = 0;
    void setupPresetButton(QPushButton* btn, QString timeStr);
    void settingsWindow(); 
    void initializationButton(const QFont& font);
    void saveAction();
};
