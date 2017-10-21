#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>

class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;

class RenderArea;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void slot_clear();
    void slot_save();
    void slot_quit();

private:
    RenderArea *renderArea;
    QPushButton *btnClear;
    QPushButton *btnSave;
    QPushButton *btnQuit;
};

#endif // MAINWINDOW_H
