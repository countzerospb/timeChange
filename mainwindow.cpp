#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString sPath ="./home";
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filemodel->setNameFilterDisables(false);
    filemodel->setRootPath(sPath);
    ui->treeView->setModel(filemodel);
    ui->treeView->setRootIndex(filemodel->setRootPath(sPath));

    ui->dateCreated->setEnabled(false);
    ui->timeCreated->setEnabled(false);
    ui->dateChanged->setEnabled(false);
    ui->timeChanged->setEnabled(false);
    ui->dateOpened->setEnabled(false);
    ui->timeOpened->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    file = new QFile(filemodel->filePath(index));

    QDateTime fileDateTime = file->fileTime(QFileDevice::FileBirthTime);
    qDebug()<<file->fileTime(QFileDevice::FileBirthTime);
    ui->dateCreated->setDate(fileDateTime.date());
    ui->timeCreated->setTime(fileDateTime.time());

    fileDateTime = file->fileTime(QFileDevice::FileModificationTime);
    ui->dateChanged->setDate(fileDateTime.date());
    ui->timeChanged->setTime(fileDateTime.time());

    fileDateTime = file->fileTime(QFileDevice::FileAccessTime);
    ui->dateOpened->setDate(fileDateTime.date());
    ui->timeOpened->setTime(fileDateTime.time());
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->createEnable->isEnabled())
    {
        QDateTime fileDateTime(ui->dateCreated->date(),ui->timeCreated->time());
        file->open(QIODevice::ReadWrite);
        file->setFileTime(fileDateTime, QFileDevice::FileBirthTime);
        file->close();
    }

    if (ui->changeEnable->isEnabled())
    {
        QDateTime fileDateTime(ui->dateChanged->date(),ui->timeChanged->time());
        file->open(QIODevice::ReadWrite);
        file->setFileTime(fileDateTime, QFileDevice::FileModificationTime);
        file->close();
    }

    if (ui->acessEnable->isEnabled())
    {
        QDateTime fileDateTime(ui->dateOpened->date(),ui->timeOpened->time());
        file->open(QIODevice::ReadWrite);
        file->setFileTime(fileDateTime, QFileDevice::FileAccessTime);
        file->close();
    }
}

void MainWindow::on_createEnable_stateChanged(int arg1)
{
    ui->dateCreated->setEnabled((arg1!=0));
    ui->timeCreated->setEnabled((arg1!=0));
}

void MainWindow::on_changeEnable_stateChanged(int arg1)
{
    ui->dateChanged->setEnabled((arg1!=0));
    ui->timeChanged->setEnabled((arg1!=0));
}

void MainWindow::on_acessEnable_stateChanged(int arg1)
{
   ui->dateOpened->setEnabled((arg1!=0));
   ui->timeOpened->setEnabled((arg1!=0));
}
