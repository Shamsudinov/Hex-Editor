#ifndef HEXEDITOR_H
#define HEXEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QStatusBar>

QT_BEGIN_NAMESPACE
namespace Ui { class HexEditor; }
QT_END_NAMESPACE

class HexEditor : public QMainWindow
{
    Q_OBJECT

public:
    HexEditor(QWidget *parent = nullptr);
    ~HexEditor();

private slots:
    void openFile();
    void saveFile();
    void goToOffset();
    void updateStatusBar();
    void cellChanged(int row, int column);
private:
    Ui::HexEditor *ui;

    void setupUI();
    void loadFileData();
    void displayData();
    bool saveChanges();

    QFile *file;
    QByteArray fileData;
    bool isModified;

    // UI элементы
    QTableWidget *hexTable;
    QTextEdit *asciiView;
    QPushButton *openButton;
    QPushButton *saveButton;
    QPushButton *goButton;
    QSpinBox *offsetSpinBox;
    QLabel *statusLabel;

    // Константы
    static const int BYTES_PER_ROW = 16;
    static const int COLUMNS_PER_BYTE = 3; // 2 hex символа + пробел
};
#endif // HEXEDITOR_H
