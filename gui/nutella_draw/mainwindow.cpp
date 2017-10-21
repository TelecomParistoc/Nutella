#include "renderarea.h"
#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow()
{
    renderArea = new RenderArea;
    btnClear = new QPushButton("Clear");
    btnSave = new QPushButton("Save");
    btnQuit = new QPushButton("Quit");

    connect(btnClear, SIGNAL(clicked(bool)), this, SLOT(slot_clear()));
    connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(slot_save()));
    connect(btnQuit, SIGNAL(clicked(bool)), this, SLOT(slot_quit()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, -1);
    mainLayout->addWidget(btnClear, 1, 1);
    mainLayout->addWidget(btnSave, 1, 2);
    mainLayout->addWidget(btnQuit, 1, 3);
    setLayout(mainLayout);

    setWindowTitle(tr("Nutella Drawing"));
}

void MainWindow::slot_clear()
{
    renderArea->clear();
}

void MainWindow::slot_save()
{
    renderArea->save();
}

void MainWindow::slot_quit()
{
    QApplication::quit();
}
