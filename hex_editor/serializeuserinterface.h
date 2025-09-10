#ifndef SERIALIZEUSERINTERFACE_H
#define SERIALIZEUSERINTERFACE_H

#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QTableWidget>
#include <QList>

#include "serializeinfo.h"

namespace Ui {
class SerializeUserInterface;
}

class SerializeUserInterface : public QWidget
{
    Q_OBJECT

public:
    explicit SerializeUserInterface(QWidget *parent = nullptr);
    ~SerializeUserInterface();

private slots:
    void on_btnAddTemplate_clicked();

    void on_btnDeleteTemplate_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_btnAddParameter_clicked();

    void on_btnSaveParams_clicked();

private:
    QList<SerializeInfo> vector;
    Ui::SerializeUserInterface *ui;
};

#endif // SERIALIZEUSERINTERFACE_H
