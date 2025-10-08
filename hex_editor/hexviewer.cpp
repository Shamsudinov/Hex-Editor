#include "hexviewer.h"


HexViewer::HexViewer(QWidget *parent)
{
    _byteCharCount = 3;
    _bytesPerLine = 16;
    this->setLineWrapMode(LineWrapMode::FixedColumnWidth);
    this->setLineWrapColumnOrWidth(_bytesPerLine * _byteCharCount);
}

void HexViewer::setFont(const QFont &font)
{
    QFont theFont(font);
    theFont.setStyleHint(QFont::Monospace);
    QWidget::setFont(theFont);
    QFontMetrics metrics = fontMetrics();
#if QT_VERSION > QT_VERSION_CHECK(5, 11, 0)
    _pxCharWidth = metrics.horizontalAdvance(QLatin1Char('2'));
#else
    _pxCharWidth = metrics.width(QLatin1Char('2'));
#endif
    _pxCharHeight = metrics.height();
    _pxAreaMargin = _pxCharWidth / 2;
    _pxCursorWidth = _pxCharHeight / 7;
    _pxSelectionSub = _pxCharHeight / 5;
    viewport()->update();
}

void HexViewer::setData(const QByteArray &data){

    hex_str = QString::fromLatin1(data.toHex(' '));

    qDebug()<<data.size();
    qDebug()<<hex_str.size();

    this->setPlainText(hex_str.toUpper());
}

void HexViewer::setCursorPosition(int position)
{
    int pxOfsX = horizontalScrollBar()->value();
    _bPosFirst = (qint64)pxOfsX * _bytesPerLine;
    int x = (position % (2 * _bytesPerLine));
    _pxCursorY = ((position / 2 - _bPosFirst) / _bytesPerLine + 1) * _pxCharHeight;
    _pxCursorX = (((x / 2) * 3) + (x % 2)) * _pxCharWidth + _pxPosHexX;
    _cursorPosition = position;
    _cursorRect = QRect(
        _pxCursorX - pxOfsX,
        _pxCursorY - _pxCharHeight + _pxSelectionSub,
        _pxCharWidth*2,
        _pxCharHeight
    );
    qDebug()<<_cursorRect;
    viewport()->update(_cursorRect);
}

void HexViewer::setBytesCountInLine(int count){
    _bytesPerLine = count;
    this->setLineWrapColumnOrWidth(_bytesPerLine * _byteCharCount);
}

void HexViewer::showBytesInLine8(){
    _bytesPerLine = 8;
    this->setLineWrapColumnOrWidth(24);
}

void HexViewer::showBytesInLine16(){
    _bytesPerLine = 16;
    this->setLineWrapColumnOrWidth(_bytesPerLine * _byteCharCount);
}

void HexViewer::showBytesInLine32(){
    _bytesPerLine = 32;
    this->setLineWrapColumnOrWidth(_bytesPerLine * _byteCharCount);
}


//void HexModel::mousePressEvent(QMouseEvent *event){
//    QTextEdit::mousePressEvent(event);
//}

void HexViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
//        QTextCursor cursor = this->textCursor();
//        int position = cursor.position();
//        setCursorPosition(position);
//        QTextCursor cursor = this->textCursor();
//        cursor.select(QTextCursor::WordUnderCursor);
//        this->setTextCursor(cursor);
    }
    QTextEdit::mouseReleaseEvent(event);
}

void HexViewer::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_M || event->key() == Qt::Key_N){

    } if(event->key() == Qt::Key_Backspace){
        qDebug()<<"Key_Backspace";

    } else {
        // If you don't handle the event, call the base class implementation
        // so that it can be propagated to parent widgets or default handlers.
        QTextEdit::keyPressEvent(event);
    }

}

#include <QTextBlock>
#include <QTextDocumentFragment>
void HexViewer::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);

    QPainter painter(viewport());
    QPen pen(Qt::red, 2); // Red pen, 2 pixels wide
    painter.setPen(pen);

    QTextCursor cursor = textCursor();
    QTextBlock text_block = cursor.block();

    QRect blockRect = this->cursorRect(cursor);
    blockRect.setLeft(_cursorRect.left());
    blockRect.setTop(_cursorRect.top());
    blockRect.setWidth(_cursorRect.width());
    blockRect.setHeight(_cursorRect.height());
    painter.drawRect(blockRect);

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
