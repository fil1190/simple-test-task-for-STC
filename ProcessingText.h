#ifndef PROCESSINGTEXT_H
#define PROCESSINGTEXT_H

#include <QObject>
#include <QString>
#include <QTimer>

class ProcessingText: public QObject
{
    Q_OBJECT
public:
    explicit ProcessingText(QObject *parent = NULL);
    ~ProcessingText(){
        delete _timer;
    }
    ProcessingText &operator = (const ProcessingText& other);
    ProcessingText (const ProcessingText& other)
        :QObject(this)
    {
        *this = other;
    }

public slots:
    void process();
    void textChanged(const QString& str);
    void movingLetter();
    void stopProcessing();

signals:
    void dataReady(const QString& str);

private:
    void _getPointers();
    void _insertLetter();
    void _copyFirstPart();
    void _copyLastPart();
    void _beginFromBeginning();
    QTimer *_timer;
    QString _text;
    char *_newStr;
    char *_cStr;
    int _index{0};
};

#endif // PROCESSINGTEXT_H
