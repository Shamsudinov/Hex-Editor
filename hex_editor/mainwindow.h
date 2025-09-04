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

    void on_tableView_clicked(const QModelIndex &index);

private:
    const int ROW_SIZEOF_FILE = 0;
    const int ROW_CURRENT_POS = 1;

    const int COL_HEX = 0;
    const int COL_DEC = 1;

    HexModel *hexModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
