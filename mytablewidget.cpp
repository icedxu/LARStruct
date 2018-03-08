#pragma execution_character_set("utf-8")
#include "mytablewidget.h"
#include <QString>
myTableWidget::myTableWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("pushButton delegate embedded in table"));
     //  setFixedSize(520, 250);

       initPath();
       QVBoxLayout* mainLayout = new QVBoxLayout(this);
       mainLayout->addWidget(m_tableWidget);

}

myTableWidget::~myTableWidget()
{

}



void myTableWidget::initPath()   //初始化白名单列表
{
   int row = 3;
    m_tableWidget = new QTableWidget(row,0,this);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0; i<row; ++i)
    {
       // QTableWidgetItem* item0 = new QTableWidgetItem(pathList1.at(i));


      //  m_tableWidget->setItem(i, 0, item0);
       // m_tableWidget->setItem(i, 1, item1);

    }
     m_tableWidget->setColumnWidth(0,50);
     m_tableWidget->setColumnWidth(1,50);

}




