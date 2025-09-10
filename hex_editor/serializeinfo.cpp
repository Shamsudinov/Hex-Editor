#include "serializeinfo.h"

SerializeInfo::SerializeInfo()
{

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
