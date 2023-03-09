#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include "qheaders.h"

class MyWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    MyWebPage(QWebEngineProfile *profile,QWidget *parent = nullptr);
private slots:
    void handleCertificateError(const QWebEngineCertificateError &certificateError);
};

#endif // MYWEBPAGE_H
