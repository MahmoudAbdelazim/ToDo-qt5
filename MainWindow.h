#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateStatus();

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;

public slots:
    void addTask();
    void removeTask(Task* task);
    void taskStatusChanged(Task *task);
};
#endif // MAINWINDOW_H
