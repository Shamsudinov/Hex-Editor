#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , serializeUI(new SerializeUserInterface(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_actionOpen_triggered();

    ui->tabWidget->setCurrentIndex(1);
    ui->tab_2->layout()->addWidget(serializeUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//#include <QModelIndexList>
#include <QVariant>
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_C && event->modifiers() == Qt::ControlModifier){
        qDebug()<<"Ctrl+C";
    }

    if(event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier){
        qDebug()<<"Ctrl+V";
    }
//    QWidget::keyPressEvent(event);
}

using namespace std;
#include <string>
void MainWindow::on_actionOpen_triggered(){

//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::homePath(),tr("All Files (*.*)"));

    QString fileName = "D:\\hextest.bin";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error: cannot open file " << fileName;
    }

    QByteArray data = file.readAll();

    ui->hex_model->setData(data);

    ui->tableWidgetServiceInfo->setSelectionMode( QAbstractItemView::ExtendedSelection);
    ui->tableWidgetServiceInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetServiceInfo->resizeColumnsToContents();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

//    currentRow = index.row();
//    currentColumn = index.column();
//    int columnCount = ui->tableView->model()->columnCount();

//    int offset = currentRow*columnCount + currentColumn;
//    ui->tableWidgetServiceInfo->setItem(ROW_CURRENT_POS,COL_HEX,new QTableWidgetItem( QString::number(offset,16) ));
//    ui->tableWidgetServiceInfo->setItem(ROW_CURRENT_POS,COL_DEC,new QTableWidgetItem( QString::number(offset) ));

}

void MainWindow::on_action8_triggered(){
    ui->hex_model->showBytesInLine8();
}

void MainWindow::on_action16_triggered(){
    ui->hex_model->showBytesInLine16();
}

void MainWindow::on_action32_triggered(){
    ui->hex_model->showBytesInLine32();
}
