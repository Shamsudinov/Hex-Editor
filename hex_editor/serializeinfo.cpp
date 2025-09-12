#include "serializeinfo.h"

SerializeInfo::SerializeInfo() :
    name("Название параметра"),
    size(0),
    hex("HEX"),
    dec("DEC"),
    alg("Алгоритм распаковки") {

}

SerializeInfo::SerializeInfo(const SerializeInfo &info){

    name = info.getName();
    size = info.getSize();
    hex = info.getHex();
    dec = info.getDec();
    alg = info.getAlg();
}

QString SerializeInfo::getName() const{
    return name;
}

int SerializeInfo::getSize() const{
    return size;
}

QString SerializeInfo::getHex() const{
    return hex;
}

QString SerializeInfo::getDec() const{
    return dec;
}

QString SerializeInfo::getAlg() const{
    return alg;
}

void SerializeInfo::setName(const QString &name){
    this->name = name;
}

void SerializeInfo::setSize(int size){
    this->size = size;
}

void SerializeInfo::setHex(const QString &hex){
    this->hex = hex;
}

void SerializeInfo::setDec(const QString &dec){
    this->dec = dec;
}

void SerializeInfo::setAlg(const QString &alg){
    this->alg = alg;
}

void SerializeInfo::print() const
{
    qDebug() << name << " " << size << " " << hex << " " << dec << " " << alg;
}
