#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , hexModel(new HexModel())
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    int columnCount = 16;
//    for(int i = 0; i < 1000; i++){
//        int currRowCount = ui->tableWidget->rowCount();
//        ui->tableWidget->setColumnCount(columnCount);
//        ui->tableWidget->setColumnWidth(currRowCount,10);
//        ui->tableWidget->insertRow(currRowCount);
//    }



}

MainWindow::~MainWindow()
{
    delete ui;
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

//    qint64 buffSize = file.size();;
//    char *buf = new char[buffSize];
//    qint64 read = file.read(buf,buffSize);

    QByteArray data = file.readAll();

    int columns = 16;
    int rows = (data.size() / columns);
    if(data.size()%columns != 0)
        rows++;

    hexModel->setColumnCount(columns);
    hexModel->setRowCount(rows);
    hexModel->unpdateBuffer(data);

    ui->tableView->setModel(hexModel);
    ui->tableView->resizeColumnsToContents();

    ui->tableWidgetServiceInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetServiceInfo->resizeColumnsToContents();
    ui->tableWidgetServiceInfo->setItem(ROW_SIZEOF_FILE,COL_HEX,new QTableWidgetItem( QString::number(data.size(),16) ));
    ui->tableWidgetServiceInfo->setItem(ROW_SIZEOF_FILE,COL_DEC,new QTableWidgetItem( QString::number(data.size()) ));
//    int columnWidth = 10;
//    for(int column = 0; column < ui->tableView->model()->columnCount(); column++){
//        ui->tableView->setColumnWidth(column,columnWidth);

//    }

//    QByteArray bytes;
//    while(!file.atEnd()){
//        bytes = file.readAll();
//    }
//    qDebug()<<bytes.toHex(' ') << " " << bytes.toHex(' ').size();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    qDebug()<<"row: " << index.row();
    qDebug()<<"col: " << index.column();
    qDebug()<<"-------------------------";
}
