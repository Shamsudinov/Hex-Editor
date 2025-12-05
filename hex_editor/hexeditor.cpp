// hexeditor.cpp
#include "hexeditor.h"
#include <QScrollBar>

HexEditor::HexEditor(QWidget *parent)
    : QMainWindow(parent), file(nullptr), isModified(false) {
    setupUI();
    setWindowTitle("Простой Hex Editor");
    resize(800, 600);
}

HexEditor::~HexEditor() {
    if (file) {
        delete file;
    }
}

void HexEditor::setupUI() {
    // Центральный виджет
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Панель инструментов
    QHBoxLayout *toolbarLayout = new QHBoxLayout();

    openButton = new QPushButton("Открыть", this);
    saveButton = new QPushButton("Сохранить", this);
    saveButton->setEnabled(false);

    QLabel *offsetLabel = new QLabel("Перейти к:", this);
    offsetSpinBox = new QSpinBox(this);
    offsetSpinBox->setRange(0, 0);
    offsetSpinBox->setPrefix("0x");
    offsetSpinBox->setDisplayIntegerBase(16);

    goButton = new QPushButton("Перейти", this);
    goButton->setEnabled(false);

    toolbarLayout->addWidget(openButton);
    toolbarLayout->addWidget(saveButton);
    toolbarLayout->addStretch();
    toolbarLayout->addWidget(offsetLabel);
    toolbarLayout->addWidget(offsetSpinBox);
    toolbarLayout->addWidget(goButton);

    // Таблица для hex представления
    hexTable = new QTableWidget(this);
    hexTable->setColumnCount(BYTES_PER_ROW);
    hexTable->setRowCount(0);

    // Заголовки колонок
    QStringList headers;
    for (int i = 0; i < BYTES_PER_ROW; i++) {
        headers << QString("%1").arg(i, 2, 16, QChar('0')).toUpper();
    }
    hexTable->setHorizontalHeaderLabels(headers);

    // Настройка таблицы
    hexTable->verticalHeader()->setVisible(true);
    hexTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    hexTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Текстовое поле для ASCII представления
    asciiView = new QTextEdit(this);
    asciiView->setReadOnly(false);
    asciiView->setMaximumWidth(300);
    asciiView->setFont(QFont("Courier", 10));

    // Layout для hex и ascii представлений
    QHBoxLayout *dataLayout = new QHBoxLayout();
    dataLayout->addWidget(hexTable, 1);
    dataLayout->addWidget(asciiView);

    // Статус бар
    statusLabel = new QLabel(this);
    statusBar()->addWidget(statusLabel);

    // Добавление всех виджетов в основной layout
    mainLayout->addLayout(toolbarLayout);
    mainLayout->addLayout(dataLayout);

    // Подключение сигналов
    connect(openButton, &QPushButton::clicked, this, &HexEditor::openFile);
    connect(saveButton, &QPushButton::clicked, this, &HexEditor::saveFile);
    connect(goButton, &QPushButton::clicked, this, &HexEditor::goToOffset);
    connect(hexTable, &QTableWidget::cellChanged, this, &HexEditor::cellChanged);
    connect(hexTable->verticalScrollBar(), &QScrollBar::valueChanged,
            asciiView->verticalScrollBar(), &QScrollBar::setValue);
    connect(asciiView->verticalScrollBar(), &QScrollBar::valueChanged,
            hexTable->verticalScrollBar(), &QScrollBar::setValue);
}

void HexEditor::openFile() {
    if (isModified) {
        if (!saveChanges()) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл");
    if (fileName.isEmpty()) {
        return;
    }

    if (file) {
        delete file;
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Ошибка",
                            "Не удалось открыть файл: " + file->errorString());
        delete file;
        file = nullptr;
        return;
    }

    loadFileData();
    displayData();

    saveButton->setEnabled(true);
    goButton->setEnabled(true);
    setWindowTitle("Hex Editor - " + fileName);
    isModified = false;
}

void HexEditor::loadFileData() {
    if (!file) return;

    file->seek(0);
    fileData = file->readAll();
    offsetSpinBox->setRange(0, fileData.size() - 1);
}

void HexEditor::displayData() {
    if (!file) return;

    hexTable->blockSignals(true);
    asciiView->blockSignals(true);

    // Очистка
    hexTable->clearContents();
    asciiView->clear();

    int rows = (fileData.size() + BYTES_PER_ROW - 1) / BYTES_PER_ROW;
    hexTable->setRowCount(rows);

    QString asciiText;

    for (int row = 0; row < rows; row++) {
        // Установка номера строки
        hexTable->setVerticalHeaderItem(row,
            new QTableWidgetItem(QString("%1").arg(row * BYTES_PER_ROW, 8, 16, QChar('0')).toUpper()));

        for (int col = 0; col < BYTES_PER_ROW; col++) {
            int index = row * BYTES_PER_ROW + col;

            if (index < fileData.size()) {
                unsigned char byte = fileData[index];

                // Hex представление
                QTableWidgetItem *hexItem = new QTableWidgetItem(
                    QString("%1").arg(byte, 2, 16, QChar('0')).toUpper());
                hexItem->setTextAlignment(Qt::AlignCenter);
                hexTable->setItem(row, col, hexItem);

                // ASCII представление
                QChar asciiChar = (byte >= 32 && byte <= 126) ? QChar(byte) : '.';
                asciiText.append(asciiChar);
            } else {
                asciiText.append(' ');
            }
        }
        asciiText.append('\n');
    }

    asciiView->setPlainText(asciiText);

    hexTable->blockSignals(false);
    asciiView->blockSignals(false);
    updateStatusBar();
}

bool HexEditor::saveChanges() {
    if (!isModified) return true;

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Сохранение",
        "Файл был изменен. Сохранить изменения?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        saveFile();
        return true;
    } else if (reply == QMessageBox::No) {
        return true;
    }

    return false;
}

void HexEditor::saveFile() {
    if (!file || !isModified) return;

    file->seek(0);
    if (file->write(fileData) != fileData.size()) {
        QMessageBox::critical(this, "Ошибка",
                            "Не удалось сохранить файл: " + file->errorString());
        return;
    }

    file->flush();
    isModified = false;
    updateStatusBar();
    QMessageBox::information(this, "Сохранение", "Файл успешно сохранен.");
}

void HexEditor::goToOffset() {
    int offset = offsetSpinBox->value();
    if (offset < 0 || offset >= fileData.size()) return;

    int row = offset / BYTES_PER_ROW;
    int col = offset % BYTES_PER_ROW;

    hexTable->scrollToItem(hexTable->item(row, col));
    hexTable->setCurrentCell(row, col);
}

void HexEditor::cellChanged(int row, int column) {
    if (!file || row < 0 || column < 0) return;

    QTableWidgetItem *item = hexTable->item(row, column);
    if (!item) return;

    QString text = item->text();
    bool ok;
    unsigned char byte = text.toUInt(&ok, 16);

    if (ok && text.length() == 2) {
        int index = row * BYTES_PER_ROW + column;
        if (index < fileData.size()) {
            fileData[index] = byte;
            isModified = true;

            // Обновление ASCII представления
            asciiView->blockSignals(true);
            QString asciiText = asciiView->toPlainText();
            int asciiPos = row * (BYTES_PER_ROW + 1) + column;
            QChar asciiChar = (byte >= 32 && byte <= 126) ? QChar(byte) : '.';
            asciiText[asciiPos] = asciiChar;
            asciiView->setPlainText(asciiText);
            asciiView->blockSignals(false);

            updateStatusBar();
        }
    } else {
        // Восстановление предыдущего значения
        hexTable->blockSignals(true);
        unsigned char prevByte = fileData[row * BYTES_PER_ROW + column];
        item->setText(QString("%1").arg(prevByte, 2, 16, QChar('0')).toUpper());
        hexTable->blockSignals(false);
        QMessageBox::warning(this, "Ошибка",
                           "Введите корректное шестнадцатеричное значение (00-FF)");
    }
}

void HexEditor::updateStatusBar() {
    if (!file) {
        statusLabel->setText("Файл не открыт");
        return;
    }

    QString status = QString("Размер: %1 байт | Позиция: %2 | %3")
                    .arg(fileData.size())
                    .arg(hexTable->currentRow() * BYTES_PER_ROW + hexTable->currentColumn())
                    .arg(isModified ? "Изменен" : "Без изменений");
    statusLabel->setText(status);
}
