#ifndef HEXMODEL_H
#define HEXMODEL_H

#include <QAbstractTableModel>
#include <QByteArray>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>

class HexModel : public QAbstractTableModel
{
    int rows;
    int columns;
    int bufferSize;
    std::vector<std::vector<char>> matrix;
public:
    HexModel();
    ~HexModel();

    void setBufferSize(int);
    void insertData(const QByteArray&,int,int);
    void insertData(const std::vector<char>&);
    void unpdateBuffer(const QByteArray&);
    void processBuffer(char*,int);

    void setRowCount(int);
    void setColumnCount(int);
private:
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int) const;

};

void separate(std::string&, uint32_t, const char);
std::string uint8_to_hex_string(const uint8_t*, const size_t);
std::string charToHex(unsigned char);

// Вспомогательная функция для вывода данных в формете HEX
void printUint8AsHex(uint8_t*, uint32_t);

#endif // HEXMODEL_H
