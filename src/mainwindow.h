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
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
