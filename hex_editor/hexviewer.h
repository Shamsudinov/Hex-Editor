#ifndef HEXMODEL_H
#define HEXMODEL_H

#include <QObject>
#include <QTextEdit>
#include <QScrollBar>
#include <QByteArray>
#include <QMouseEvent>
#include <QPainter>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>

class HexViewer : public QTextEdit{

    Q_OBJECT

    QString hex_str;
    int _byteCharCount = 3;
    int _bytesPerLine = 16;
    // other variables

    int _pxCharWidth, _pxCharHeight;            // char dimensions (dependend on font)
    int _pxAreaMargin;                          // gap left and right from areas
    int _pxCursorWidth;                         // cursor width
    int _pxSelectionSub;                        // offset selection rect

    QRect _cursorRect;
    int _pxCursorX;                             // current cursor pos
    int _pxCursorY;                             // current cursor pos
    int _pxPosHexX;                             // X-Pos of HeaxArea
    int _cursorPosition;
    qint64 _bPosFirst;                          // position of first byte shown
public:
    HexViewer(QWidget *parent = nullptr);

    void setFont(const QFont&);
    void setData(const QByteArray&);
    void setCursorPosition(int);
    void setBytesCountInLine(int);
    void showBytesInLine8();
    void showBytesInLine16();
    void showBytesInLine32();
protected:
//    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;
};

void separate(std::string&, uint32_t, const char);
std::string uint8_to_hex_string(const uint8_t*, const size_t);
std::string charToHex(unsigned char);

// Вспомогательная функция для вывода данных в формете HEX
void printUint8AsHex(uint8_t*, uint32_t);

#endif // HEXMODEL_H
