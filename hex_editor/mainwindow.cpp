#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , serializeUI(new SerializeUserInterface(this))
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

        QItemSelectionModel *model = ui->tableView->selectionModel();
        QModelIndexList list = model->selectedIndexes();
        tempBuffer.clear();
        for(int i=0; i < list.size(); i ++){
            tempBuffer += list[i].data().value<QByteArray>();
        }
        qDebug()<<tempBuffer;
    }

    if(event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier){
        qDebug()<<"Ctrl+V";
        qDebug()<< "currentRow: " << currentRow;
        qDebug()<< "currentColumn: " << currentColumn;
        hexModel->insertData(tempBuffer,currentRow,currentColumn);
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
//    ui->tableView->setShowGrid(false); // hide or shor table grids
//    ui->tableView->setStyleSheet(QString("QTableView{ color: red; } ")); // color change

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

    currentRow = index.row();
    currentColumn = index.column();
    int columnCount = ui->tableView->model()->columnCount();

    int offset = currentRow*columnCount + currentColumn;
    ui->tableWidgetServiceInfo->setItem(ROW_CURRENT_POS,COL_HEX,new QTableWidgetItem( QString::number(offset,16) ));
    ui->tableWidgetServiceInfo->setItem(ROW_CURRENT_POS,COL_DEC,new QTableWidgetItem( QString::number(offset) ));

}









