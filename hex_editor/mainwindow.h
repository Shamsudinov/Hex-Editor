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
#include <QKeyEvent>
#include "hexmodel.h"
#include "serializeuserinterface.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_actionOpen_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_action8_triggered();

    void on_action16_triggered();

    void on_action32_triggered();

private:
    SerializeUserInterface *serializeUI;
    HexModel *hexModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
