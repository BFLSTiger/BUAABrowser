#include "mywebview.h"
#include "mainwindow.h"
#include "mywebpage.h"

MyWebView::MyWebView(QWebEngineProfile *profile,QWidget *parent)
    : QWebEngineView(profile,parent)
{
    this->setPage(new MyWebPage(profile,this));
}

QWebEngineView *MyWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    if(type==QWebEnginePage::WebBrowserWindow)
    {
        MainWindow *newwindow = new MainWindow(this->page()->profile(),nullptr);
        newwindow->setManager(this->manager);
        newwindow->setWindowState(Qt::WindowMaximized);
        newwindow->show();
        return newwindow->starttab();
    }
    MainWindow *windownow = qobject_cast<MainWindow*>(window());
    if(type==QWebEnginePage::WebBrowserTab)
    {
        return windownow->newtab(true);
    }
    if(type==QWebEnginePage::WebBrowserBackgroundTab)
    {
        return windownow->newtab(false);
    }
    if(type==QWebEnginePage::WebDialog)
    {
        return QWebEngineView::createWindow(type);
    }
    return QWebEngineView::createWindow(type);
}
