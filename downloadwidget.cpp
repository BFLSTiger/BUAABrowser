#include "downloadwidget.h"
#include "ui_downloadwidget.h"
#include<iostream>
using namespace std;

DownloadWidget::DownloadWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadWidget)
{
    ui->setupUi(this);
}

DownloadWidget::~DownloadWidget()
{
    delete ui;
}

void DownloadWidget::downloadProgress()
{
    if(this->download->state()==QWebEngineDownloadRequest::DownloadRequested)
        return;
    if(this->download->state()==QWebEngineDownloadRequest::DownloadInProgress)
    {
        this->ui->progressBar->setStyleSheet("QProgressBar\
        {\
        border-radius:2;\
        }\
        QProgressBar::chunk\
        {\
        border-radius:2;\
        background-color:green;\
        }");
        qreal bytesReceived=this->download->receivedBytes();
        qreal bytesTotal=this->download->totalBytes();
        this->ui->name_label->setText(this->download->downloadFileName());
        if(bytesTotal>=0)
            this->ui->status_label->setText(tr("%1/%2").arg(withUnit(bytesReceived),withUnit(bytesTotal)));
        else
            this->ui->status_label->setText(tr("%1/Unknown size").arg(withUnit(bytesReceived)));
        this->ui->progressBar->setValue(100*bytesReceived/bytesTotal);
    }
    if(this->download->state()==QWebEngineDownloadRequest::DownloadCompleted)
    {
        this->ui->progressBar->setVisible(false);
        this->ui->play_Button->setIcon(QIcon(":/logo/buttons/folder.png"));
        this->ui->status_label->setText(tr("%1").arg(withUnit(this->download->receivedBytes())));
    }
    if(this->download->state()==QWebEngineDownloadRequest::DownloadCancelled)
    {
        emit downloadCanceled(this);
    }
    if(this->download->state()==QWebEngineDownloadRequest::DownloadInterrupted)
    {
        this->ui->play_Button->setIcon(QIcon(":/logo/buttons/continue.png"));
        this->ui->progressBar->setStyleSheet("QProgressBar\
        {\
        border-radius:2;\
        }\
        QProgressBar::chunk\
        {\
        border-radius:2;\
        background-color:grey;\
        }");
    }
}

QString DownloadWidget::withUnit(qreal bytes)
{
    if (bytes < (1 << 10))
        return tr("%L1 B").arg(bytes);
    else if (bytes < (1 << 20))
        return tr("%L1 KiB").arg(bytes / (1 << 10), 0, 'f', 2);
    else if (bytes < (1 << 30))
        return tr("%L1 MiB").arg(bytes / (1 << 20), 0, 'f', 2);
    else
        return tr("%L1 GiB").arg(bytes / (1 << 30), 0, 'f', 2);
}

void DownloadWidget::on_cancel_Button_clicked()
{
    this->download->cancel();
    emit downloadCanceled(this);
}

void DownloadWidget::on_play_Button_clicked()
{
    if(this->download->state()==QWebEngineDownloadRequest::DownloadCompleted)
    {
        QString dir=this->download->downloadDirectory(),name=this->download->downloadFileName(),trpath="";
        for(int i=0;i<dir.size();i++)
        {
            if(dir[i]=='/')trpath+='\\';
            else trpath+=dir[i];
        }
        if(trpath[trpath.size()-1]!='\\')
            trpath+='\\';
        trpath+=name;
        QString cmd="explorer /select,"+trpath;
        QProcess *process=new QProcess(this);
        process->startCommand(cmd);
        return;
    }
    if(this->download->isPaused())
    {
        this->download->resume();
        this->ui->play_Button->setIcon(QIcon(":/logo/buttons/pause.png"));
        this->ui->progressBar->setStyleSheet("QProgressBar\
        {\
        border-radius:2;\
        }\
        QProgressBar::chunk\
        {\
        border-radius:2;\
        background-color:green;\
        }");
    }
    else
    {
        this->download->pause();
        this->ui->play_Button->setIcon(QIcon(":/logo/buttons/continue.png"));
        this->ui->progressBar->setStyleSheet("QProgressBar\
        {\
        border-radius:2;\
        }\
        QProgressBar::chunk\
        {\
        border-radius:2;\
        background-color:grey;\
        }");
    }
}

void DownloadWidget::setDownload(QWebEngineDownloadRequest *download)
{
    this->download=download;
    this->connect(this->download,SIGNAL(receivedBytesChanged()),this,SLOT(downloadProgress()));
    this->connect(this->download,SIGNAL(stateChanged(QWebEngineDownloadRequest::DownloadState)),this,SLOT(downloadProgress()));
}
