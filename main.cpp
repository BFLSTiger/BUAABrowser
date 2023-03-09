#include "mainwindow.h"
#include "downloadmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
 //   QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
 //   qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--ignore-gpu-blacklist --enable-gpu-rasterization --enable-native-gpu-memory-buffers");
    QApplication a(argc, argv);
    QWebEngineProfile *profile = new QWebEngineProfile(a.applicationName());
    MainWindow w(profile);
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    DownloadManager *manager=new DownloadManager();
    manager->hide();
    w.setManager(manager);
    return a.exec();
}
