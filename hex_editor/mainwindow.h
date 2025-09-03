#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QTableWidget>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include "hexmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionOpen_triggered();

private:
    HexModel *hexModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
