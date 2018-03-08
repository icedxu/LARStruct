#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#pragma execution_character_set("utf-8")
//#include "../FsAppControlCode.h"
#include <Windows.h>

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <qfile.h>
#include <qtextstream.h>
class myTableWidget : public QWidget
{
    Q_OBJECT

public:
    myTableWidget(QWidget *parent = 0);
    ~myTableWidget();
    void initPath();
    void addPath(QString path);
    QTableWidget *m_tableWidget;
	

public slots:
        void onItemClicked(QTableWidgetItem *item);

};

#endif // MYTABLEWIDGET_H
