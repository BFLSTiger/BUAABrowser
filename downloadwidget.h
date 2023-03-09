#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include "qheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DownloadWidget; }
QT_END_NAMESPACE

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    static const int height=70;
    DownloadWidget(QWidget *parent = nullptr);
    ~DownloadWidget();
    void setDownload(QWebEngineDownloadRequest *download);
signals:
    void downloadCanceled(QWidget *widget);
private slots:
    void downloadProgress();
    void on_cancel_Button_clicked();

    void on_play_Button_clicked();

private:
    Ui::DownloadWidget *ui;
    QWebEngineDownloadRequest *download;
    QString withUnit(qreal byte);
};
#endif // DOWNLOADWIDGET_H
