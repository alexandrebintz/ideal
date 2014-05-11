/**
 * This file is part of the _ideal_ project
 *
 * @author Alexandre Bintz <alexandre.bintz@gmail.com>
 * @date   May 2014
 *
 * @file   main.cpp
 * @brief  Program's main file
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
