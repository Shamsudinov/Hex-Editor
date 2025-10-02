#include "hexmodel.h"



HexModel::HexModel(QWidget *parent)
{
    byte_characters_count = 3;
    bytes_in_line = 16;
    this->setLineWrapMode(LineWrapMode::FixedColumnWidth);
    this->setLineWrapColumnOrWidth(bytes_in_line * byte_characters_count);
}

void HexModel::setData(const QByteArray &data){

    QFont font;
    font.setBold(true);
    this->setFont(font);

    QString hex_str = QString::fromLatin1(data.toHex(' '));
    this->setPlainText(hex_str.toUpper());
}

void HexModel::setBytesCountInLine(int count){
    bytes_in_line = count;
    this->setLineWrapColumnOrWidth(bytes_in_line * byte_characters_count);
}

void HexModel::showBytesInLine8(){
    bytes_in_line = 8;
    this->setLineWrapColumnOrWidth(24);
}

void HexModel::showBytesInLine16(){
    bytes_in_line = 16;
    this->setLineWrapColumnOrWidth(bytes_in_line * byte_characters_count);
}

void HexModel::showBytesInLine32(){
    bytes_in_line = 32;
    this->setLineWrapColumnOrWidth(bytes_in_line * byte_characters_count);
}


void separate(std::string & input, uint32_t step, const char separator){

    for ( auto it = input.begin(); (step+1) <= std::distance(it, input.end()); ++it ){
        std::advance(it,step);
        it = input.insert(it,separator);
    }
}

std::string uint8_to_hex_string(const uint8_t *v, const size_t s) {

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (uint32_t i = 0; i < s; i++) {
        ss << std::hex << std::setw(2) << static_cast<int>(v[i]);
    }

    return ss.str();
}

std::string charToHex(unsigned char c) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    return ss.str();
}

// Вспомогательная функция для вывода данных в формете HEX
void printUint8AsHex(uint8_t *str, uint32_t size){

    std::string str_hex = uint8_to_hex_string(str,size);
    separate(str_hex,2,' ');
    std::cout<<"hex: "<<str_hex<<std::endl;
    std::cout.flush();
}
