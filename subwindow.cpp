#include "subwindow.h"
#include "mainwindow.h"
#include "ui_subwindow.h"

SubWindow::SubWindow(QWebEngineProfile *profile,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SubWindow)
{
    this->ui->setupUi(this);
    this->ui->label_input->setGeometry(120,0,this->width()-180,30);
    this->ui->url_lineEdit->setGeometry(135,0,this->width()-200,30);
    this->ui->label->setGeometry(0,0,this->width(),30);
    this->ui->add_Button->setGeometry(this->width()-60,0,30,30);
    this->ui->download_Button->setGeometry(this->width()-30,0,30,30);
    this->web_view = new MyWebView(profile,this);
    this->web_view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    this->connect(this->web_view->page(),SIGNAL(findTextFinished(const QWebEngineFindTextResult&)),this,SLOT(findTextFinished(const QWebEngineFindTextResult&)));
    this->connect(this->web_view->page(),SIGNAL(fullScreenRequested(QWebEngineFullScreenRequest)),this,SLOT(fullScreen(QWebEngineFullScreenRequest)));
    this->connect(this->web_view,SIGNAL(loadStarted()),this,SLOT(webViewLoadStarted()));
    this->connect(this->web_view,SIGNAL(loadFinished(bool)),this,SLOT(webViewLoadFinished(bool)));
    this->connect(this->web_view,SIGNAL(urlChanged(const QUrl&)),this,SLOT(webViewUrlChanged(const QUrl&)));
    this->connect(this->web_view,SIGNAL(titleChanged(const QString&)),this,SLOT(webViewTitleChanged(const QString&)));
    this->connect(this->web_view->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadRequest*)),this,SLOT(webDownload(QWebEngineDownloadRequest*)));
    this->ui->horizontalLayoutWidget->setGeometry(0,30,this->width(),this->height()-30);
    this->ui->horizontalLayout->addWidget(this->web_view);
    this->homeurl = "file:///"+QDir::currentPath()+"/home.html";
    this->web_view->load(QUrl(this->homeurl));
    this->ui->findWidget->hide();
    this->ui->findWidget->move(this->width()-500,30);
    this->ui->findWidget->raise();

    this->ui->back_Button->setEnabled(false);
    this->ui->forward_Button->setEnabled(false);
    this->ui->stop_Button->setEnabled(false);
    this->ui->stop_Button->setVisible(false);

}

SubWindow::~SubWindow()
{
    delete ui;
    delete web_view;
}


void SubWindow::webViewLoadStarted()
{
    this->ui->refresh_Button->setEnabled(false);
    this->ui->refresh_Button->setVisible(false);
    this->ui->stop_Button->setEnabled(true);
    this->ui->stop_Button->setVisible(true);
}

void SubWindow::webViewLoadFinished(bool ok)
{
    if(ok)
    {
        this->ui->refresh_Button->setEnabled(true);
        this->ui->refresh_Button->setVisible(true);
        this->ui->stop_Button->setEnabled(false);
        this->ui->stop_Button->setVisible(false);
        this->ui->back_Button->setEnabled(this->web_view->history()->canGoBack());
        this->ui->forward_Button->setEnabled(this->web_view->history()->canGoForward());
    }
}

void SubWindow::webViewUrlChanged(const QUrl &url)
{
    QString cururl=url.toString();
    if(cururl!=homeurl)
    {
        this->ui->url_lineEdit->setText(cururl);
    }
    else
    {
        this->ui->url_lineEdit->setText("");
    }
}

void SubWindow::webViewTitleChanged(const QString &title)
{
    this->setWindowTitle(title);
    this->setWindowIcon(this->web_view->icon());
    emit swebViewTitleChanged(this);
}

void SubWindow::on_back_Button_clicked()
{
    this->web_view->back();
}

void SubWindow::on_forward_Button_clicked()
{
    this->web_view->forward();
}


void SubWindow::on_url_lineEdit_returnPressed()
{
    QUrl url = QUrl(this->ui->url_lineEdit->text());
    if(url.scheme()=="file")
    {
        this->web_view->load(url);
        return;
    }
    if (!this->ui->url_lineEdit->text().contains("://"))
    {
        url=QUrl::fromUserInput(this->ui->url_lineEdit->text());
        if(url.scheme()=="http")url.setScheme("https");
    }
    QString urlhost=url.host();
    if(urlhost.right(15)!="vpn.buaa.edu.cn")
    {
        urlhost.replace("-","--");
        urlhost.replace(".","-");
        urlhost+=(url.port()==-1?"-s":"-"+QString::number(url.port())+"-p")+".vpn.buaa.edu.cn";
        url.setHost(urlhost);
        url.setPort(8118);
    }
    this->web_view->load(url);
}

void SubWindow::on_refresh_Button_clicked()
{
    this->web_view->reload();
    this->ui->refresh_Button->setEnabled(false);
    this->ui->refresh_Button->setVisible(false);
    this->ui->stop_Button->setEnabled(true);
    this->ui->stop_Button->setVisible(true);
}

void SubWindow::on_stop_Button_clicked()
{
    this->web_view->stop();
    this->ui->refresh_Button->setEnabled(true);
    this->ui->refresh_Button->setVisible(true);
    this->ui->stop_Button->setEnabled(false);
    this->ui->stop_Button->setVisible(false);
}

void SubWindow::on_home_Button_clicked()
{
    this->web_view->load(QUrl(homeurl));
}

void SubWindow::fullScreen(QWebEngineFullScreenRequest request)
{
    MainWindow *windownow = qobject_cast<MainWindow*>(window());
    request.accept();
    if(request.toggleOn())
    {
        this->web_view->setParent(nullptr);
        windownow->hide();
        this->web_view->setWindowState(Qt::WindowMaximized);
        this->web_view->showFullScreen();
    }
    else
    {
        this->web_view->setWindowState(Qt::WindowNoState);
        this->ui->horizontalLayout->addWidget(this->web_view);
        windownow->show();
    }
}

void SubWindow::on_add_Button_clicked()
{
    emit addnewtab(true);
}

void SubWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    this->ui->label_input->setGeometry(120,0,this->width()-180,30);
    this->ui->url_lineEdit->setGeometry(135,0,this->width()-200,30);
    this->ui->label->setGeometry(0,0,this->width(),30);
    this->ui->add_Button->setGeometry(this->width()-60,0,30,30);
    this->ui->download_Button->setGeometry(this->width()-30,0,30,30);
    this->ui->horizontalLayoutWidget->setGeometry(0,30,this->width(),this->height()-30);
    this->ui->findWidget->move(this->width()-500,30);
    this->ui->findWidget->raise();
}

void SubWindow::webDownload(QWebEngineDownloadRequest *download)
{
    if(download&&download->state()==QWebEngineDownloadRequest::DownloadRequested)
    {
        QString path=QFileDialog::getSaveFileName(this, "Save as", QDir(download->downloadDirectory()).filePath(download->downloadFileName()));
        if(path=="")
        {
            download->cancel();
            return;
        }
        download->setDownloadDirectory(QFileInfo(path).path());
        download->setDownloadFileName(QFileInfo(path).fileName());
        download->accept();
        this->web_view->manager->add(download);
        this->web_view->manager->raise();
        this->web_view->manager->show();
        this->web_view->manager->activateWindow();
    }
}

void SubWindow::setManager(DownloadManager *manager)
{
    this->web_view->manager=manager;
}

void SubWindow::on_download_Button_clicked()
{
    this->web_view->manager->raise();
    this->web_view->manager->show();
    this->web_view->manager->activateWindow();
}

void SubWindow::DevToolsRequest()
{
    if(this->ui->horizontalLayout->count()==1)
    {
        this->devtool = new MyWebView(this->web_view->page()->profile(),this);
        this->devtool->setAttribute(Qt::WA_DeleteOnClose,true);
        this->connect(this->devtool->page(),SIGNAL(windowCloseRequested()),this,SLOT(DevToolsRequest()));
        this->web_view->page()->setDevToolsPage(this->devtool->page());
        this->devtool->setMaximumWidth(555);
        this->devtool->setMinimumWidth(555);
        this->ui->horizontalLayout->addWidget(this->devtool);
    }
    else
    {
        this->web_view->page()->setDevToolsPage(nullptr);
        this->devtool->deleteLater();
    }
}

void SubWindow::FindTextRequest()
{
    if(this->ui->findWidget->isHidden())
    {
        this->ui->findWidget->show();
        this->web_view->findText(this->ui->find_lineEdit->text());
    }
    else
    {
        this->ui->findWidget->hide();
        this->web_view->findText("");
    }
}

void SubWindow::on_find_lineEdit_textChanged(const QString &arg1)
{
    this->web_view->findText(arg1);
}

void SubWindow::findTextFinished(const QWebEngineFindTextResult &result)
{
    if(this->ui->find_lineEdit->text()=="")
        this->ui->findLabel->setText(QString("%1/%2").arg(QString::number(result.activeMatch()),QString::number(result.numberOfMatches())));
    else this->ui->findLabel->setText("");
}

void SubWindow::on_cancelButton_clicked()
{
    this->ui->findWidget->hide();
    this->web_view->findText("");
}

void SubWindow::on_nxtButton_clicked()
{
    this->web_view->findText(this->ui->find_lineEdit->text());
}

void SubWindow::on_preButton_clicked()
{
    this->web_view->findText(this->ui->find_lineEdit->text(),QWebEnginePage::FindBackward);
}
