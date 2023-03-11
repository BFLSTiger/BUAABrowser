#include "downloadmanager.h"
#include "ui_downloadmanager.h"
DownloadManager::DownloadManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadManager)
{
    ui->setupUi(this);
}

DownloadManager::~DownloadManager()
{
    delete ui;
}

void DownloadManager::add(QWebEngineDownloadRequest *download)
{
    DownloadWidget *newdownload = new DownloadWidget(this);
    newdownload->setDownload(download);
    this->ui->verticalLayout->insertWidget(0,newdownload,0,Qt::AlignTop);
    this->connect(newdownload,SIGNAL(downloadCanceled(QWidget*)),this,SLOT(remove(QWidget*)));
    this->ui->scrollArea->resize(this->width(),qMin(this->height(),qMax(1,this->ui->verticalLayout->count())*DownloadWidget::height+2));
}

void DownloadManager::remove(QWidget *widget)
{
    this->ui->verticalLayout->removeWidget(widget);
    this->ui->scrollArea->resize(this->width(),qMin(this->height(),qMax(1,this->ui->verticalLayout->count())*DownloadWidget::height+2));
    delete widget;
}

void DownloadManager::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->ui->scrollArea->setGeometry(0,0,event->size().width(),qMin(event->size().height(),qMax(1,this->ui->verticalLayout->count())*DownloadWidget::height+2));
}
