#include "widget.h"
#include "ui_widget.h"
#include <QtGui/QMouseEvent>
#include <QPainter>




Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
      mMoveing=false;
      setFixedSize(498,340);
      setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);


      m_pLeftWidget = new QWidget();
      m_pLeftWidget->setFixedWidth(115);
      m_pLeftWidget->setStyleSheet("background-color:rgb(45 ,45 ,45);");
      m_pVBLeftLayout  = new QVBoxLayout();
      m_pVBLeftLayout->addWidget(m_pLeftWidget);
      m_pVBLeftLayout->setSpacing(0);


      m_pRightWidget = new QWidget();
      m_pRightWidget->setFixedSize(383,26);
      m_pRightWidget->setStyleSheet("background-color:white;");

      m_pVBRightLayout  = new QVBoxLayout();
      m_pText = new QTextEdit();
      m_pText->setFixedSize(359,290);
      m_pText->setStyleSheet("background-color:white;");

      m_pHBRightBottomLayout =new QHBoxLayout();
      m_pHBRightTopLayout =new QHBoxLayout();

      m_pLab = new QLabel("Title");

      m_pHBRightTopLayout->addWidget(m_pLab);
      m_pRightWidget->setLayout(m_pHBRightTopLayout);


      m_pHBRightBottomLayout->setSpacing(0);
      m_pHBRightBottomLayout->addSpacing(12);
      m_pHBRightBottomLayout->addWidget(m_pText);
      m_pHBRightBottomLayout->addSpacing(12);
      m_pHBRightBottomLayout->addStretch(0);


      m_pVBRightLayout->addWidget(m_pRightWidget);
      m_pVBRightLayout->addSpacing(12);
      m_pVBRightLayout->addLayout(m_pHBRightBottomLayout);
      m_pVBRightLayout->addSpacing(12);


      m_pBtnClose = new QPushButton("Close");
      m_pBtnClose->setStyleSheet("background-color:green;");
      m_pBtnTest = new QPushButton("Test");
      m_pBtnTest->setStyleSheet("background-color:green;");

      QVBoxLayout   *m_pVBLayout  = new QVBoxLayout();
      m_pVBLayout->addWidget(m_pBtnClose);
      m_pVBLayout->addWidget(m_pBtnTest);
      m_pLeftWidget->setLayout(m_pVBLayout);

     QHBoxLayout *m_pHBLayout =new QHBoxLayout();
     m_pHBLayout->addItem(m_pVBLeftLayout);
     m_pHBLayout->addItem(m_pVBRightLayout);
     m_pHBLayout->setSpacing(0);
     m_pHBLayout->setMargin(0);





      this->setLayout(m_pHBLayout);

      connect(m_pBtnClose,SIGNAL(clicked()),this,SLOT(Close()));

}


//��д��갴���¼�
void Widget::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //��¼���������ڴ��ڵ�λ��
    //event->globalPos()��갴��ʱ����������������Ļλ��
    //pos() this->pos()��갴��ʱ�����������������Ļλ��
    mMovePosition = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

//��д����ƶ��¼�
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)���������
    //����ƶ��¼���Ҫ�ƶ����ڣ������ƶ��������أ�����Ҫ��ȡ����ƶ��У�������������Ļ�����꣬Ȼ��move��������꣬��ô��ȡ���ꣿ
    //ͨ���¼�event->globalPos()֪��������꣬��������ȥ�������ڴ���λ�ã����Ǵ�����������Ļ������
    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}



void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}



void Widget::Close()
{
    this->close();
}

Widget::~Widget()
{
    //delete ui;
}
