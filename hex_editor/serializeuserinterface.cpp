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

    int rowCount = ui->paramsTable->rowCount();
    ui->paramsTable->insertRow(rowCount);
//    ui->paramsTable->setItem(rowCount,0,new QTableWidgetItem(s.name));
//    ui->paramsTable->setItem(rowCount,1,new QTableWidgetItem(QString::number(s.size)));
//    ui->paramsTable->setItem(rowCount,2,new QTableWidgetItem(s.hex));
//    ui->paramsTable->setItem(rowCount,3,new QTableWidgetItem(s.dec));
//    ui->paramsTable->setItem(rowCount,4,new QTableWidgetItem(s.alg));
}
