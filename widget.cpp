#include "widget.h"
#include "ui_widget.h"
#include <QtGui/QMouseEvent>
#include <QPainter>
#include <QTextEdit>



Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
   //   ui->setupUi(this);
      mMoveing=false;
      setFixedSize(498,340);
      setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
     // this->setStyleSheet("QWidget{border:2px solid green;}");


      QWidget * left = new QWidget();
      left->setFixedWidth(115);
      left->setStyleSheet("background-color:rgb(45 ,45 ,45);");
      vb  = new QVBoxLayout();
      vb->addWidget(left);
      vb->setSpacing(0);


      QWidget * right = new QWidget();
      right->setFixedSize(383,26);
      right->setStyleSheet("background-color:white;");

      QVBoxLayout   *vb2  = new QVBoxLayout();
      QTextEdit *T  = new QTextEdit();
      T->setFixedSize(359,290);
      T->setStyleSheet("background-color:white;");

      QHBoxLayout *hb1 =new QHBoxLayout();
      QHBoxLayout *hb2 =new QHBoxLayout();

      QLabel *lab = new QLabel("kehuduan");
      hb2->addWidget(lab);//
      right->setLayout(hb2);




      hb1->setSpacing(0);
      hb1->addSpacing(12);
      hb1->addWidget(T);
      hb1->addSpacing(12);
      hb1->addStretch(0);


      vb2->addWidget(right);
      vb2->addSpacing(12);
      vb2->addLayout(hb1);
      vb2->addSpacing(12);

      //vb2->addStretch(0);
     // vb2->addSpacing(12);
     // vb2->addWidget(T);
     // vb2->addSpacing(12);


      btn = new QPushButton("close");
      btn->setStyleSheet("background-color:green;");
      QPushButton  *btn1 = new QPushButton("hehe");
      btn1->setStyleSheet("background-color:green;");

      QVBoxLayout   *vb3  = new QVBoxLayout();
      vb3->addWidget(btn);
      vb3->addWidget(btn1);
      left->setLayout(vb3);

   QHBoxLayout *hb =new QHBoxLayout();
   hb->addItem(vb);
   hb->addItem(vb2);
   hb->setSpacing(0);
   hb->setMargin(0);





      this->setLayout(hb);

      connect(btn,SIGNAL(clicked()),this,SLOT(Close()));

}


//重写鼠标按下事件
void Widget::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mMovePosition = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
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
