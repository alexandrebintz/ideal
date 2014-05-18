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
#include <qDebug>

/**
 * @brief Constructor
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
}

/**
 * @brief Executes a command.
 * Call initProcess before using this command.
 * Use getCmdOutput to get the command output.
 * @param QString cmd
 */
void MainWindow::execCmd(QString cmd)
{
    mProcess->startDetached(cmd);
}


/**
 * @brief Returns output of the last executed command.
 * Read data connot be read again (i.e. next call to getCmdOutput will return
 * nothing, unless another command has been executed).
 * @return output of the last executed command
 */
QByteArray MainWindow::getCmdOutput()
{
    return mProcess->readAll();
}

/**
 * @brief Makes QProcess object ready to use.
 */
void MainWindow::initProcess()
{
    mProcess = new QProcess(this);

    disconnect(mProcess,0,0,0); // disconnect before connecting, in case connexions
                                // already exist

    connect(mProcess,SIGNAL(started()),
            this,SLOT(processStarted()));
    connect(mProcess,SIGNAL(finished(int,QProcess::ExitStatus)),
            this,SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(mProcess,SIGNAL(stateChanged(QProcess::ProcessState)),
            this,SLOT(processStateChanged(QProcess::ProcessState)));
    connect(mProcess,SIGNAL(error(QProcess::ProcessError)),
            this,SLOT(processError(QProcess::ProcessError)));
}


void MainWindow::processError(QProcess::ProcessError err)
{
    qDebug() << "process error : " << err;
}

void MainWindow::processFinished(int code, QProcess::ExitStatus status)
{
    qDebug() << "process finished with code " << code << " and status " << status;
}

void MainWindow::processStarted()
{
    qDebug() << "process started";
}

void MainWindow::processStateChanged(QProcess::ProcessState state)
{
    qDebug() << "process state changed to " << state;
}

