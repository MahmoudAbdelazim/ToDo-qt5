#include "Task.h"
#include "ui_Task.h"
#include <QInputDialog>

Task::Task(const QString &name, QWidget *parent)
    :QWidget(parent), ui(new Ui::Task){
    ui->setupUi(this);
    setName(name);
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QPushButton::clicked, this, &Task::remove);
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->checkbox->setText(name);
}

QString Task::name() const
{
    return ui->checkbox->text();
}

void Task::rename()
{
    bool ok;
    QString newName = QInputDialog::getText(this,
                                            tr("Edit Task"),
                                            tr("New Task Name"),
                                            QLineEdit::Normal,
                                            this->name(), &ok);
    if (ok && !newName.isEmpty()) {
        setName(newName);
    }
}

void Task::remove()
{
    emit removed(this);
}

void Task::checked(bool checked)
{
    QFont font(ui->checkbox->font());
    font.setStrikeOut(checked);
    ui->checkbox->setFont(font);
    emit statusChanged(this);
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}
