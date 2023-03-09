#include "mywebpage.h"

MyWebPage::MyWebPage(QWebEngineProfile *profile,QWidget *parent):
    QWebEnginePage(profile,parent)
{
    this->connect(this,SIGNAL(certificateError(const QWebEngineCertificateError&)),this,SLOT(handleCertificateError(const QWebEngineCertificateError&)));
}

void MyWebPage::handleCertificateError(const QWebEngineCertificateError &certificateError)
{
    QWebEngineCertificateError error=certificateError;
    error.acceptCertificate();
}
