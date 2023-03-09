#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "qheaders.h"

#include "downloadwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DownloadManager; }
QT_END_NAMESPACE

class DownloadManager : public QWidget
{
    Q_OBJECT

public:
    DownloadManager(QWidget *parent = nullptr);
    ~DownloadManager();
    void add(QWebEngineDownloadRequest *download);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void remove(QWidget *widget);

private:
    Ui::DownloadManager *ui;
};
#endif // DOWNLOADMANAGER_H
