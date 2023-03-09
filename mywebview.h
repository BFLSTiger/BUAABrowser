#ifndef MYWEBVIEW_H
#define MYWEBVIEW_H
#include "qheaders.h"
#include "downloadmanager.h"

class MyWebView: public QWebEngineView
{
    Q_OBJECT
public:
    MyWebView(QWebEngineProfile *profile,QWidget *parent = nullptr);
    DownloadManager *manager;
private:
    QWebEngineView * createWindow(QWebEnginePage::WebWindowType type) override;
};

#endif // MYWEBVIEW_H
