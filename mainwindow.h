#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDirModel>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_createEnable_stateChanged(int arg1);
    void on_changeEnable_stateChanged(int arg1);
    void on_acessEnable_stateChanged(int arg1);

    void on_filePanel_clicked(const QModelIndex &index);
    void on_filePanel_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *filemodel;
    QModelIndex indexToSave;
};
#endif // MAINWINDOW_H
