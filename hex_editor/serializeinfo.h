#ifndef SERIALIZEINFO_H
#define SERIALIZEINFO_H

#include <QString>

class SerializeInfo
{
    QString name;
    int size;
    QString hex;
    QString dec;
    QString alg;
public:
    SerializeInfo();

    QString getName() const;
    int getSize() const;
    QString getHex() const;
    QString getDec() const;
    QString getAlg() const;

    void setName(const QString&);
    void setSize(int);
    void setHex(const QString&);
    void setDec(const QString&);
    void setAlg(const QString&);
};

#endif // SERIALIZEINFO_H
