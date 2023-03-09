#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include "qheaders.h"

#include "mywebview.h"
#include "downloadmanager.h"

namespace Ui { class SubWindow;}

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    SubWindow(QWebEngineProfile *profile,QWidget *parent = nullptr);
    ~SubWindow();
    MyWebView *web_view;
    void setManager(DownloadManager *manager);
    void FindTextRequest();
signals:
    void swebViewTitleChanged(QWidget *webwindow);
    void addnewtab(bool flag);
protected:
    void resizeEvent(QResizeEvent *event);
public slots:
    void DevToolsRequest();
private slots:
    void webViewLoadStarted();
    void webViewLoadFinished(bool ok);
    void webViewUrlChanged(const QUrl &url);
    void webViewTitleChanged(const QString &title);
    void webDownload(QWebEngineDownloadRequest *download);
    void fullScreen(QWebEngineFullScreenRequest request);
    void findTextFinished(const QWebEngineFindTextResult &result);

    void on_back_Button_clicked();

    void on_url_lineEdit_returnPressed();

    void on_forward_Button_clicked();

    void on_refresh_Button_clicked();

    void on_stop_Button_clicked();

    void on_home_Button_clicked();

    void on_add_Button_clicked();

    void on_download_Button_clicked();

    void on_find_lineEdit_textChanged(const QString &arg1);

    void on_cancelButton_clicked();

    void on_nxtButton_clicked();

    void on_preButton_clicked();

private:
    Ui::SubWindow *ui;
    MyWebView *devtool;
    QString homeurl;
    QRect prert;
};

#endif // SUBWINDOW_H


