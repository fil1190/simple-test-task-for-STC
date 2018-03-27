#include "ProcessingText.h"

ProcessingText::ProcessingText(QObject *parent)
    : QObject(parent)
{
    _timer = new QTimer(this);
}

ProcessingText &ProcessingText::operator =(const ProcessingText &other)
{
    if (&other != this)
    {
        delete _timer;
        _timer = new QTimer(this);
        _timer = other._timer;
        _text = other._text;
        _index = other._index;
    }
    return *this;
}

void ProcessingText::process()
{
    connect(_timer, SIGNAL(timeout()), this, SLOT(movingLetter()));
    _timer->setInterval(500);
    _timer->start();
}

void ProcessingText::textChanged(const QString &str)
{
    _timer->stop();
    _text = str;
    _timer->start();
}

void ProcessingText::movingLetter()
{
    if (_text.size())
    {
        _getPointers();
        if (_index < _text.size())
            _insertLetter();
        else
            _beginFromBeginning();
        _text = QString(_newStr);
        emit dataReady(_text);
        delete [] _newStr;
    }
}

void ProcessingText::_getPointers()
{
    _cStr = _text.toUtf8().data();
    _newStr = new char[_text.size()+2];
    memset(_newStr, 0, _text.size()+2);
}

void ProcessingText::_insertLetter()
{
    if (_index)
        _copyFirstPart();
    _copyLastPart();
    ++_index;
}

void ProcessingText::_copyFirstPart()
{
    memcpy(_newStr, _cStr, sizeof(char)*(_index-1));
    *(_newStr+_index-1) = *(_cStr+_index);
}

void ProcessingText::_copyLastPart()
{
    *(_newStr+(_index)) = '*';
    if (_index)
        memcpy((_newStr + _index +1),
               (_cStr + _index +1),
               sizeof(char)*(_text.size() - _index));
    else
        memcpy((_newStr + 1),
               (_cStr),
               sizeof(char)*(_text.size()));
}

void ProcessingText::_beginFromBeginning()
{
    memcpy(_newStr, _cStr, sizeof(char)*(_index-1));
   _index = 0;
}

void ProcessingText::stopProcessing()
{
    _timer->stop();
}

