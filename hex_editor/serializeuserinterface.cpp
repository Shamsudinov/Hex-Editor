#include "serializeuserinterface.h"
#include "ui_serializeuserinterface.h"

void SerializeUserInterface::clearCellsContent(QTableWidget *table) const {

    for(int row = 0; row < table->rowCount(); row++){
        for(int col = 0; col < table->columnCount(); col++){
            table->item(row,col)->setText("");
        }
    }
}

SerializeUserInterface::SerializeUserInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerializeUserInterface)
{
    ui->setupUi(this);

    ui->btnAddParameter->setEnabled(false);
    ui->btnSaveParams->setEnabled(false);
    ui->btnDeleteParam->setEnabled(false);
}

SerializeUserInterface::~SerializeUserInterface(){
    delete ui;
}

void SerializeUserInterface::on_btnAddTemplate_clicked(){

    int currentNumber = ui->listWidget->count();
    QString templateName = "Новый шаблон " + QString::number( currentNumber );
    QListWidgetItem *item = new QListWidgetItem(templateName,ui->listWidget);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
    QPair<int,QList<SerializeInfo>> tempPair;
    tempPair.first = currentNumber;
    vector.append(tempPair);
}

void SerializeUserInterface::on_btnDeleteTemplate_clicked(){
    QScopedPointer ptr(ui->listWidget->currentItem());
}

void SerializeUserInterface::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->groupBox->setTitle(item->text());
    ui->btnAddParameter->setEnabled(true);
    ui->btnSaveParams->setEnabled(true);
    ui->btnDeleteParam->setEnabled(true);

    ui->paramsTable->clear();
//    clearCellsContent(ui->paramsTable);

    int currrentTemplateNumber = ui->listWidget->currentRow();
    ui->paramsTable->setRowCount(vector[currrentTemplateNumber].second.size());
//    qDebug()<<"currrentTemplateNumber " << currrentTemplateNumber << " params count  " << vector[currrentTemplateNumber].second.size();
    if( vector[currrentTemplateNumber].second.size() == 0 ){

        return;
    }

    for(int i = 0; i < vector.size(); i++){
        if(vector[i].first == currrentTemplateNumber){

            for(int currRow = 0; currRow < vector[i].second.size(); currRow++){
//                qDebug()<<"currRow: " << currRow << " " << currrentTemplateNumber;
//                ui->paramsTable->item(currRow,0)->setText(vector[i].second[currRow].getName());
//                ui->paramsTable->item(currRow,1)->setText(QString::number(vector[i].second[currRow].getSize()));
//                ui->paramsTable->item(currRow,2)->setText(vector[i].second[currRow].getHex());;
//                ui->paramsTable->item(currRow,3)->setText(vector[i].second[currRow].getDec());;
//                ui->paramsTable->item(currRow,4)->setText(vector[i].second[currRow].getAlg());

                ui->paramsTable->setItem(currRow,0,new QTableWidgetItem(vector[i].second[currRow].getName()));
                ui->paramsTable->setItem(currRow,1,new QTableWidgetItem( QString::number(vector[i].second[currRow].getSize())));
                ui->paramsTable->setItem(currRow,2,new QTableWidgetItem(vector[i].second[currRow].getHex()));
                ui->paramsTable->setItem(currRow,3,new QTableWidgetItem(vector[i].second[currRow].getDec()));
                ui->paramsTable->setItem(currRow,4,new QTableWidgetItem(vector[i].second[currRow].getAlg()));
            }
            break;
        }
    }

}

void SerializeUserInterface::on_btnAddParameter_clicked(){

    int rowCount = ui->paramsTable->rowCount();
    ui->paramsTable->insertRow(rowCount);
    ui->paramsTable->setItem(rowCount,0,new QTableWidgetItem("Название параметра"));
    ui->paramsTable->setItem(rowCount,1,new QTableWidgetItem("Размер в битах"));
    ui->paramsTable->setItem(rowCount,2,new QTableWidgetItem("HEX"));
    ui->paramsTable->setItem(rowCount,3,new QTableWidgetItem("DEC"));
    ui->paramsTable->setItem(rowCount,4,new QTableWidgetItem("Алгоритм распаковки"));

    int currrentTemplateNumber = ui->listWidget->currentRow();
    for(int i = 0; i < vector.size(); i++){
        if(vector[i].first == currrentTemplateNumber){
            SerializeInfo info;
            vector[i].second.append(info);
        }
    }
}

void SerializeUserInterface::on_btnSaveParams_clicked(){

    int currrentTemplateNumber = ui->listWidget->currentRow();

//    for(int i = 0; i < vector.size(); i++){
//        if(vector[i].first == currrentTemplateNumber){
//            SerializeInfo info;
//            vector[i].second.append(info);
//        }
//    }

    for( int i = 0; i < vector.size(); i++){

        if(vector[i].first == currrentTemplateNumber){

            int rows = ui->paramsTable->rowCount();
            for(int currRow = 0; currRow < rows; currRow++){
                vector[i].second[currRow].setName(ui->paramsTable->item(currRow,0)->text());
                vector[i].second[currRow].setSize(ui->paramsTable->item(currRow,1)->text().toInt());
                vector[i].second[currRow].setHex(ui->paramsTable->item(currRow,2)->text());
                vector[i].second[currRow].setDec(ui->paramsTable->item(currRow,3)->text());
                vector[i].second[currRow].setAlg(ui->paramsTable->item(currRow,4)->text());
            }
        }
    }

}
