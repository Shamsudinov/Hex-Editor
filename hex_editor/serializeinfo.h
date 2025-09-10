#ifndef SERIALIZEINFO_H
#define SERIALIZEINFO_H

#include <QString>
#include <QDebug>

class SerializeInfo
{
    QString name;
    int size;
    QString hex;
    QString dec;
    QString alg;
public:
    SerializeInfo();
    SerializeInfo(const SerializeInfo&);

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

    void print() const;
};

#endif // SERIALIZEINFO_H
