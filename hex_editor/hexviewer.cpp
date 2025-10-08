#include "hexviewer.h"


HexViewer::HexViewer(QWidget *parent)
{
    _byte_char_count = 3;
    _bytes_per_line = 16;
    this->setLineWrapMode(LineWrapMode::FixedColumnWidth);
    this->setLineWrapColumnOrWidth(_bytes_per_line * _byte_char_count);
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

void HexViewer::setBytesCountInLine(int count){
    _bytes_per_line = count;
    this->setLineWrapColumnOrWidth(_bytes_per_line * _byte_char_count);
}

void HexViewer::showBytesInLine8(){
    _bytes_per_line = 8;
    this->setLineWrapColumnOrWidth(24);
}

void HexViewer::showBytesInLine16(){
    _bytes_per_line = 16;
    this->setLineWrapColumnOrWidth(_bytes_per_line * _byte_char_count);
}

void HexViewer::showBytesInLine32(){
    _bytes_per_line = 32;
    this->setLineWrapColumnOrWidth(_bytes_per_line * _byte_char_count);
}

int HexViewer::getRowNumber() const{
    return _curr_row;
}

int HexViewer::getByteAddress() const{
    return _curr_address;
}

void HexViewer::setCurrRow(int position){
    _curr_row = position/(_bytes_per_line*_byte_char_count);
}

void HexViewer::setByteAddress(int position){
    _curr_address = position/_byte_char_count;
}

#include <QTextBlock>
void HexViewer::mousePressEvent(QMouseEvent *event)
{
    QTextEdit::mousePressEvent(event); // Вызываем базовый обработчик события
}



void HexViewer::mouseReleaseEvent(QMouseEvent *event){

    QTextCursor cursor = textCursor(); // Получаем курсор
    setCurrRow(cursor.position());
    setByteAddress(cursor.position());
    qDebug() << getByteAddress();
    cursorPositionChanged();
    QTextEdit::mouseReleaseEvent(event); // Вызываем базовый обработчик события
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
