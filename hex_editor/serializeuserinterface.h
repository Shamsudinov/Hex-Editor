#ifndef SERIALIZEUSERINTERFACE_H
#define SERIALIZEUSERINTERFACE_H

#include <QWidget>
#include <QString>
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

private:
    Ui::SerializeUserInterface *ui;
};

#endif // SERIALIZEUSERINTERFACE_H
