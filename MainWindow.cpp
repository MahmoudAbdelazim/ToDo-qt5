#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
    this, &MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add Task"),
                                         tr("Task name"),
                                         QLineEdit::Normal,
                                         tr("Untitled Task"), &ok);
    if (ok && !name.isEmpty()) {
        Task *task = new Task(name);
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task *task)
{
    updateStatus();
}

void MainWindow::updateStatus() {
    int completedCount = 0;
    for (Task* t: mTasks) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText(QString("Status: %1 todo / %2 completed").arg(todoCount).arg(completedCount));
}

