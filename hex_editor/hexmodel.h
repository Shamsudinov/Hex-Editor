#ifndef HEXMODEL_H
#define HEXMODEL_H

#include <QObject>
#include <QTextEdit>
#include <QByteArray>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>

class HexModel : public QTextEdit{

    int byte_characters_count;
    int bytes_in_line;

public:
    HexModel(QWidget *parent = nullptr);

    void setData(const QByteArray&);
    void setBytesCountInLine(int);
    void showBytesInLine8();
    void showBytesInLine16();
    void showBytesInLine32();
};

void separate(std::string&, uint32_t, const char);
std::string uint8_to_hex_string(const uint8_t*, const size_t);
std::string charToHex(unsigned char);

// Вспомогательная функция для вывода данных в формете HEX
void printUint8AsHex(uint8_t*, uint32_t);

#endif // HEXMODEL_H
