/**
 * This file is part of the _ideal_ project
 *
 * @author Alexandre Bintz <alexandre.bintz@gmail.com>
 * @date   May 2014
 *
 * @file   mainwindow.h
 * @brief  Program's main window header file
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QSlider>

#include "ui_mainwindow.h"
#include "ui_about.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    // core
    void execCmd(QString cmd);
    QByteArray getCmdOutput();
    void initProcess();

    // gui
    void initUI();
    void clear();
    void exec();

public slots:
    //core
    void processError(QProcess::ProcessError);
    void processFinished(int,QProcess::ExitStatus);
    void processStarted();
    void processStateChanged(QProcess::ProcessState);

    // gui
    void about();
    void clearBtnClicked();
    void execBtnClicked();

private:
    Ui::MainWindow ui;
    Ui::About ui_about;

    QDialog* mAboutDialog;

    QProcess* mProcess;
    QStatusBar* mStatusBar;
    QSlider* mStatusSlider;
};

#endif // MAINWINDOW_H
