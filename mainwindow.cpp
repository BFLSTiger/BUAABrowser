#include "mainwindow.h"
#include "subwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWebEngineProfile *profile,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->smallrt=this->geometry();
    this->maxflag=true;
    this->tag=false;
    this->setWindowFlag(Qt::FramelessWindowHint);

    close_Button = new QPushButton("×",this);
    close_Button->setStyleSheet("QPushButton{font-weight:500;font-size:24px;border:none;outline:none;}\nQPushButton:hover{background-color: red; color: white;}");
    this->connect(close_Button,SIGNAL(clicked()),this,SLOT(closewindow()));

    size_Button = new QPushButton(this);
    size_Button->setIcon(QIcon(":/icons/small.png"));
    size_Button->setIconSize(QSize(12,12));
    size_Button->setStyleSheet("QPushButton{font-weight:500;font-size:24px;border:none;outline:none;}\nQPushButton:hover{background-color: rgb(92,141,170);}");
    this->connect(size_Button,SIGNAL(clicked()),this,SLOT(windowresize()));

    min_Button = new QPushButton(this);
    min_Button->setIcon(QIcon(":/icons/min.png"));
    min_Button->setIconSize(QSize(10,10));
    min_Button->setStyleSheet("QPushButton{font-weight:500;font-size:24px;border:none;outline:none;}\nQPushButton:hover{background-color: rgb(92,141,170);}");
    this->connect(min_Button,SIGNAL(clicked()),this,SLOT(showMinimized()));

    this->profile=profile;
    this->start=new SubWindow(profile,this->ui->tabWidget);
    start->setWindowFlags(Qt::Widget);
    this->connect(this->start,SIGNAL(swebViewTitleChanged(QWidget*)),this,SLOT(tab_Changed(QWidget*)));
    this->connect(start,SIGNAL(addnewtab(bool)),this,SLOT(newtab(bool)));
    this->ui->tabWidget->addTab(start,start->windowTitle());

    this->mdrag=0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete close_Button;
    delete min_Button;
    delete size_Button;
}

void MainWindow::tab_Changed(QWidget *webwindow)
{
    int now=this->ui->tabWidget->indexOf(webwindow);
    this->ui->tabWidget->setTabText(now,webwindow->windowTitle());
    this->ui->tabWidget->setTabToolTip(now,webwindow->windowTitle());
    this->ui->tabWidget->setTabIcon(now,webwindow->windowIcon());
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    SubWindow *closeview = qobject_cast<SubWindow*>(this->ui->tabWidget->widget(index));
    closeview->close();
    delete closeview;
    if(this->ui->tabWidget->count() == 0)
        this->close();
}

QWebEngineView *MainWindow::newtab(bool flag)
{
    SubWindow *newswindow= new SubWindow(this->profile,this->ui->tabWidget);
    int now=this->ui->tabWidget->addTab(newswindow,newswindow->windowTitle());
    this->connect(newswindow,SIGNAL(swebViewTitleChanged(QWidget*)),this,SLOT(tab_Changed(QWidget*)));
    this->connect(newswindow,SIGNAL(addnewtab(bool)),this,SLOT(newtab(bool)));
    if(flag)
    {
        this->ui->tabWidget->setCurrentIndex(now);
    }
    newswindow->setManager(this->manager);
    return newswindow->web_view;
}

QWebEngineView *MainWindow::starttab()
{
    return this->start->web_view;
}

void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    on_tabWidget_tabCloseRequested(index);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if(maxflag)
    {
        this->ui->tabWidget->setGeometry(0,0,this->width(),this->height());
        this->ui->tabWidget->setStyleSheet(QString("QTabWidget::pane {\
                                                    border: none;\
                                                    }\
                                                    QTabBar::tab\
                                                    {\
                                                        height:35;\
                                                        text-align:left;\
                                                        width: 240;\
                                                        border-top-left-radius:10;\
                                                        border-top-right-radius:10;\
                                                        background-color:white;\
                                                    }\
                                                    QTabBar{\nmax-width: ")+QString::number(this->width()-135)+";\n}");
        close_Button->setGeometry(this->width()-45,0,45,35);
        size_Button->setGeometry(this->width()-90,0,45,35);
        min_Button->setGeometry(this->width()-135,0,45,35);
        this->ui->left_label->setGeometry(0,5,5,this->height()-10);
        this->ui->topleft_label->setGeometry(0,0,5,5);
        this->ui->top_label->setGeometry(5,0,this->width()-10,5);
        this->ui->topright_label->setGeometry(this->width()-5,0,5,5);
        this->ui->right_label->setGeometry(this->width()-5,5,5,this->height()-10);
        this->ui->buttomright_label->setGeometry(this->width()-5,this->height()-5,5,5);
        this->ui->buttom_label->setGeometry(5,this->height()-5,this->width()-10,5);
        this->ui->buttomleft_label->setGeometry(0,this->height()-5,5,5);
        this->ui->left_label->setVisible(false);
        this->ui->topleft_label->setVisible(false);
        this->ui->top_label->setVisible(false);
        this->ui->topright_label->setVisible(false);
        this->ui->right_label->setVisible(false);
        this->ui->buttomright_label->setVisible(false);
        this->ui->buttom_label->setVisible(false);
        this->ui->buttomleft_label->setVisible(false);
        this->size_Button->setIcon(QIcon(":/icons/small.png"));
    }
    else
    {
        this->ui->tabWidget->setGeometry(3,3,this->width()-6,this->height()-6);
        this->ui->tabWidget->setStyleSheet(QString("QTabWidget::pane {\
                                                    border: none;\
                                                    }\
                                                    QTabBar::tab\
                                                    {\
                                                        height:35;\
                                                        text-align:left;\
                                                        width: 240;\
                                                        border-top-left-radius:10;\
                                                        border-top-right-radius:10;\
                                                        background-color:white;\
                                                    }\
                                                    QTabBar{\nmax-width: ")+QString::number(this->width()-141)+";\n}");
        close_Button->setGeometry(this->width()-48,3,45,35);
        size_Button->setGeometry(this->width()-93,3,45,35);
        min_Button->setGeometry(this->width()-138,3,45,35);
        this->ui->left_label->setGeometry(0,3,3,this->height()-10);
        this->ui->topleft_label->setGeometry(0,0,3,3);
        this->ui->top_label->setGeometry(3,0,this->width()-6,3);
        this->ui->topright_label->setGeometry(this->width()-3,0,3,3);
        this->ui->right_label->setGeometry(this->width()-3,3,3,this->height()-6);
        this->ui->buttomright_label->setGeometry(this->width()-3,this->height()-3,3,3);
        this->ui->buttom_label->setGeometry(3,this->height()-3,this->width()-6,3);
        this->ui->buttomleft_label->setGeometry(0,this->height()-3,3,3);
        this->ui->left_label->setVisible(true);
        this->ui->topleft_label->setVisible(true);
        this->ui->top_label->setVisible(true);
        this->ui->topright_label->setVisible(true);
        this->ui->right_label->setVisible(true);
        this->ui->buttomright_label->setVisible(true);
        this->ui->buttom_label->setVisible(true);
        this->ui->buttomleft_label->setVisible(true);
        this->size_Button->setIcon(QIcon(":/icons/large.png"));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(maxflag||event->button()!=Qt::LeftButton)
        return;
    this->delta=this->frameGeometry().topLeft()-event->globalPosition().toPoint();
    this->startrt=this->geometry();
    this->startpoint=event->globalPosition().toPoint();
    int a=event->position().toPoint().x();
    int b=event->position().toPoint().y();
    int c=this->width()-a;
    int d=this->height()-b;
    if(b<=35&&b>=3&&a>=3&&c>=3)
        this->mdrag=1;
    if(c<3&&b>=3&&d>=3)
        this->mdrag=2;
    if(b<3&&c<3)
        this->mdrag=3;
    if(b<3 && a>=3 && c>=3)
        this->mdrag=4;
    if(a<3&&b<3)
        this->mdrag=5;
    if(a<3&&b>=3&&d>=3)
        this->mdrag=6;
    if(a<3&&d<3)
        this->mdrag=7;
    if(d<3&&a>=3&&c>=3)
        this->mdrag=8;
    if(c<3&&d<3)
        this->mdrag=9;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!this->mdrag)
        return;
    if(this->mdrag==1)
    {
        this->move(event->globalPosition().toPoint()+delta);
        smallrt=this->geometry();
        return;
    }
    QRect nxtrt=this->startrt;
    QPoint dis=event->globalPosition().toPoint()-startpoint;
    switch(this->mdrag)
    {
    case 2:
        nxtrt.setRight(this->startrt.right()+dis.x());
        break;
    case 3:
        nxtrt.setTopRight(startrt.topRight()+dis);
        break;
    case 4:
        nxtrt.setTop(this->startrt.top()+dis.y());
        break;
    case 5:
        nxtrt.setTopLeft(this->startrt.topLeft()+dis);
        break;
    case 6:
        nxtrt.setLeft(this->startrt.left()+dis.x());
        break;
    case 7:
        nxtrt.setBottomLeft(this->startrt.bottomLeft()+dis);
        break;
    case 8:
        nxtrt.setBottom(this->startrt.bottom()+dis.y());
        break;
    case 9:
        nxtrt.setBottomRight(this->startrt.bottomRight()+dis);
        break;
    }
    smallrt=nxtrt;
    this->setGeometry(nxtrt);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        this->mdrag=0;
}

void MainWindow::windowresize()
{
    if(maxflag)
    {
        if(!this->tag)
        {
            largert=this->geometry();
            this->tag=true;
        }
        maxflag=false;
        this->setGeometry(smallrt);
        this->size_Button->setIcon(QIcon(":/icons/large.png"));
    }
    else
    {
        maxflag=true;
        this->setGeometry(largert);
        this->size_Button->setIcon(QIcon(":/icons/small.png"));
    }
}

void MainWindow::setManager(DownloadManager *manager)
{
    this->manager=manager;
    this->start->setManager(manager);
}

void MainWindow::closewindow()
{
    delete this->ui->tabWidget;
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    SubWindow *curwindow = qobject_cast<SubWindow*>(this->ui->tabWidget->currentWidget());
    if(event->modifiers()==Qt::NoModifier&&event->key()==Qt::Key_F12)
    {
        curwindow->DevToolsRequest();
    }
    if(event->modifiers()==Qt::ControlModifier&&event->key()==Qt::Key_F)
    {
        curwindow->FindTextRequest();
    }
}
