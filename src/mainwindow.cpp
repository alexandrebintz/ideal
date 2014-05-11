/**
 * This file is part of the _ideal_ project
 *
 * @author Alexandre Bintz <alexandre.bintz@gmail.com>
 * @date   May 2014
 *
 * @file   mainwindow.cpp
 * @brief  Program's main window implementation file
 */

#include "mainwindow.h"

/**
 * @brief Constructor
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
}
