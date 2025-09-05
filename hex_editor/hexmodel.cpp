#include "hexmodel.h"

HexModel::HexModel() :
    rows(0),
    columns(0),
    bufferSize(0),
    matrix(){

}

HexModel::~HexModel()
{
    matrix.clear();
}

void HexModel::setBufferSize(int size){
    bufferSize = size;
}

void HexModel::insertData(const QByteArray &data,int row,int column){

}
void HexModel::insertData(const std::vector<char>& newRows){

}

void HexModel::unpdateBuffer(const QByteArray& data){

    if(!matrix.empty())
        matrix.clear();

    int currentByte = 0;
    for(int i = 0; i < rows; i++){
        std::vector<char> columnData;
        for(int j = 0; j < columns; j++){
            if(currentByte < data.size()){
                columnData.push_back( data.at(currentByte) );
                currentByte++;
            }
        }
        matrix.push_back(columnData);
    }
}

void HexModel::processBuffer(char *data, int size){

}

void HexModel::setRowCount(int rows){
    this->rows = rows;
}

void HexModel::setColumnCount(int columns){
    this->columns = columns;
}

int HexModel::rowCount(const QModelIndex &parent) const{
    return rows;
}

int HexModel::columnCount(const QModelIndex &parent) const{
    return columns;
}

QVariant HexModel::data(const QModelIndex &index, int role) const{


    if (role == Qt::DisplayRole || role == Qt::EditRole) {

        std::string hex = charToHex(matrix[index.row()][index.column()]);
        return QByteArray(hex);
    }

    if (role == Qt::DisplayRole || role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
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
