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
#include <QMessageBox>

/**
 * @brief Constructor
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
    mStatusBar = statusBar();

    initUI();
    initProcess();
    clear();
}

/**
 * @brief Shows "About ideal" popup.
 */
void MainWindow::about()
{
    mAboutDialog->show();
}

/**
 * @brief Clears GUI components.
 */
void MainWindow::clear()
{
    ui.inText->clear();
    ui.outText->clear();

    mStatusBar->showMessage("Ready");
}

void MainWindow::clearBtnClicked()
{
    clear();
}

/**
 * @brief Executes command input by user and displays its output
 */
void MainWindow::exec()
{
    execCmd(ui.inText->toPlainText());
}

void MainWindow::execBtnClicked()
{
    exec();
}

/**
 * @brief Executes a command.
 * Call initProcess before using this command.
 * Use getCmdOutput to get the command output.
 * @param QString cmd
 */
void MainWindow::execCmd(QString cmd)
{
    mProcess->start(cmd);
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

/**
 * @brief Initializes the UI.
 * Should be called only once.
 */
void MainWindow::initUI()
{
    mAboutDialog = new QDialog(this);
    ui_about.setupUi(mAboutDialog);

    mStatusSlider = new QSlider(this);
    mStatusSlider->setOrientation(Qt::Horizontal);
    mStatusSlider->setRange(0,0);
    mStatusSlider->setValue(-1);

    mStatusBar->addPermanentWidget(mStatusSlider);

    mStatusSlider->setVisible(false);

    connect(ui.clearButton,SIGNAL(clicked()),
            this,SLOT(clearBtnClicked()));
    connect(ui.execButton,SIGNAL(clicked()),
            this,SLOT(execBtnClicked()));

    connect(ui.aboutAction,SIGNAL(triggered()),
            this,SLOT(about()));
    connect(ui.aboutQtAction,SIGNAL(triggered()),
            qApp,SLOT(aboutQt()));
}

/**
 * @brief Reacts to process error
 * @param QProcess::ProcessError error
 */
void MainWindow::processError(QProcess::ProcessError err)
{
    qDebug() << "process error : " << err;

    QString message;

    switch(err)
    {
    case QProcess::FailedToStart:
        message = "Process failed to start";
        break;
    case QProcess::Crashed:
        message = "Process crashed";
        break;
    case QProcess::Timedout:
        message = "Process timed out";
        break;
    case QProcess::WriteError:
        message = "Process write error";
        break;
    case QProcess::ReadError:
        message = "Process readError";
        break;
    case QProcess::UnknownError:
    default:
        message = "Unknown error";
        break;
    }

    QMessageBox::warning(this,"Error","Error: "+message);
}

/**
 * @brief Reacts to process finished
 * @param int process exit code
 * @param QProcess::ExitStatus process exit status
 */
void MainWindow::processFinished(int code, QProcess::ExitStatus status)
{
    qDebug() << "process finished with code " << code << " and status " << status;

    ui.outText->setPlainText(getCmdOutput());

    mStatusBar->showMessage("Command finished with code " + QString::number(code) + " and status " + QString::number(status));
    mStatusSlider->setVisible(false);
}

/**
 * @brief Reacts to process started
 */
void MainWindow::processStarted()
{
    qDebug() << "process started";

    mStatusBar->showMessage("Command started");
    mStatusSlider->setVisible(true);
}

/**
 * @brief Reacts to proccess state changes
 * @param QProcess::ProcessState new state
 */
void MainWindow::processStateChanged(QProcess::ProcessState state)
{
    qDebug() << "process state changed to " << state;
}

