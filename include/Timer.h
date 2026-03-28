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

class Timer : public QMainWindow
{
    Q_OBJECT

public:
    Timer(QWidget *parent = nullptr);
    ~Timer();
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
    QGridLayout* layout = nullptr;
    QString hours;
    QMessageBox* msgBox = nullptr;
    int converttime = 0;

    void saveOff();

    void settingsWindow();
};
