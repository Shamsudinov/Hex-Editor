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
