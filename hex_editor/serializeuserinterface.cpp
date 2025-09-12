#include "serializeuserinterface.h"
#include "ui_serializeuserinterface.h"

void SerializeUserInterface::clearCellsContent(QTableWidget *table) const {

    for(int row = 0; row < table->rowCount(); row++){
        for(int col = 0; col < table->columnCount(); col++){
            table->item(row,col)->setText("");
        }
    }
}

void SerializeUserInterface::saveTableRow(SerializeInfo &info, QTableWidget *table, int row) const{

    info.setName(table->item(row,0)->text());
    info.setSize(table->item(row,1)->text().toInt());
    info.setHex(table->item(row,2)->text());
    info.setDec(table->item(row,3)->text());
    info.setAlg(table->item(row,4)->text());
}

void SerializeUserInterface::fillTableRow(const SerializeInfo &info, QTableWidget *table, int row) const{

    table->setItem(row,0,new QTableWidgetItem(info.getName()));
    table->setItem(row,1,new QTableWidgetItem(QString::number(info.getSize())));
    table->setItem(row,2,new QTableWidgetItem(info.getHex()));
    table->setItem(row,3,new QTableWidgetItem(info.getDec()));
    table->setItem(row,4,new QTableWidgetItem(info.getAlg()));
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

void SerializeUserInterface::on_listWidget_itemClicked(QListWidgetItem *item){

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

                fillTableRow(vector[i].second[currRow],ui->paramsTable,currRow);
            }

            break;
        }
    }

}

void SerializeUserInterface::on_btnAddParameter_clicked(){

    int rowCount = ui->paramsTable->rowCount();
    ui->paramsTable->insertRow(rowCount);

    int currrentTemplateNumber = ui->listWidget->currentRow();
    for(int i = 0; i < vector.size(); i++){
        if(vector[i].first == currrentTemplateNumber){
            SerializeInfo info;
            fillTableRow(info,ui->paramsTable,rowCount);
            vector[i].second.append(info);
        }
    }
}

void SerializeUserInterface::on_btnSaveParams_clicked(){

    int currrentTemplateNumber = ui->listWidget->currentRow();


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
