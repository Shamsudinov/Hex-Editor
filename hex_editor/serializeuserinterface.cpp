#include "serializeuserinterface.h"
#include "ui_serializeuserinterface.h"

SerializeUserInterface::SerializeUserInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerializeUserInterface)
{
    ui->setupUi(this);

}

SerializeUserInterface::~SerializeUserInterface(){
    delete ui;
}

void SerializeUserInterface::on_btnAddTemplate_clicked(){

    QString templateName = "Новый шаблон " + QString::number(ui->listWidget->count());
    QListWidgetItem *item = new QListWidgetItem(templateName,ui->listWidget);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
}

void SerializeUserInterface::on_btnDeleteTemplate_clicked(){
    QScopedPointer ptr(ui->listWidget->currentItem());
}

void SerializeUserInterface::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->groupBox->setTitle(item->text());
}

void SerializeUserInterface::on_btnAddParameter_clicked()
{

    SerializeInfo info;
    vector.append(info);
    int rowCount = ui->paramsTable->rowCount();
    ui->paramsTable->insertRow(rowCount);
    ui->paramsTable->setItem(rowCount,0,new QTableWidgetItem("Название параметра"));
    ui->paramsTable->setItem(rowCount,1,new QTableWidgetItem("Размер в битах"));
    ui->paramsTable->setItem(rowCount,2,new QTableWidgetItem("HEX"));
    ui->paramsTable->setItem(rowCount,3,new QTableWidgetItem("DEC"));
    ui->paramsTable->setItem(rowCount,4,new QTableWidgetItem("Алгоритм распаковки"));
}

void SerializeUserInterface::on_btnSaveParams_clicked()
{
    int rows = ui->paramsTable->rowCount();
    int columns = ui->paramsTable->columnCount();

    for( int i = 0; i < rows; i++){

        vector[i].setName(ui->paramsTable->item(i,0)->text());
        vector[i].setSize(ui->paramsTable->item(i,1)->text().toInt());
        vector[i].setHex(ui->paramsTable->item(i,2)->text());
        vector[i].setDec(ui->paramsTable->item(i,3)->text());
        vector[i].setAlg(ui->paramsTable->item(i,4)->text());
    }
}
