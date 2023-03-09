#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qheaders.h"
#include "subwindow.h"
#include "downloadmanager.h"

namespace Ui { class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWebEngineProfile *profile,QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    bool maxflag;
    QRect smallrt,largert;
    DownloadManager *manager;
    void setManager(DownloadManager *manager);

public slots:
    QWebEngineView *newtab(bool flag);
    QWebEngineView *starttab();

private slots:
    void tab_Changed(QWidget *webwindow);
    void windowresize();
    void closewindow();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_tabBarDoubleClicked(int index);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QWebEngineProfile *profile;
    SubWindow *start;
    QPushButton *close_Button,*min_Button,*size_Button;
    QPoint delta,startpoint;
    QRect startrt;
    int mdrag;
    bool tag;
};
#endif // MAINWINDOW_H
