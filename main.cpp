#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载QSS样式表
    QFile qss(":/new/prefix1/Resources/MyTitle.css");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    Widget w;
    w.show();

    return a.exec();
}
