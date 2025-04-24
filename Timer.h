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
    

private:
    QWidget* widget;
    QLineEdit* line;
    QPushButton* btn1;
    QGridLayout* layout;
    QString hours;
    QMessageBox* msgBox; 
    int converttime{};
};
