#include "hexmodel.h"



HexModel::HexModel(QWidget *parent)
{

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
