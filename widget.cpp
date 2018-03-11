#include "widget.h"
#include "ui_widget.h"
#include <QtGui/QMouseEvent>
#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>



Widget::Widget(QWidget *parent) :
    QWidget(parent)
   ,m_buttonType(MIN_MAX_BUTTON)
{
      mMoveing=false;
     // setFixedSize(498,340);
      this->resize(498,340); //可伸缩
      setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);


      m_pLeftWidget = new QWidget();
      m_pLeftWidget->setFixedWidth(115);
      m_pLeftWidget->setStyleSheet("background-color:rgb(45 ,45 ,45);");
      m_pVBLeftLayout  = new QVBoxLayout();
      m_pVBLeftLayout->addWidget(m_pLeftWidget);
      m_pVBLeftLayout->setSpacing(0);


      m_pRightWidget = new QWidget();
      //m_pRightWidget->setFixedSize(383,26);
      m_pRightWidget->setFixedHeight(40);
      m_pRightWidget->setStyleSheet("background-color:white;");

      m_pVBRightLayout  = new QVBoxLayout();
      m_pText = new QTextEdit();
    //  m_pText->setFixedSize(359,290);
      m_pText->setStyleSheet("background-color:white;");

      m_pHBRightBottomLayout =new QHBoxLayout();
      m_pHBRightTopLayout =new QHBoxLayout();

      m_pLab = new QLabel("Title");
      m_pButtonMin = new QPushButton; m_pButtonMin->setObjectName("ButtonMin");
      m_pButtonRestore = new QPushButton;m_pButtonRestore->setObjectName("ButtonRestore");
      m_pButtonMax = new QPushButton;m_pButtonMax->setObjectName("ButtonMax");
      m_pButtonClose = new QPushButton;m_pButtonClose->setObjectName("ButtonClose");

      m_pButtonMin->setFixedSize(QSize(31, 30));
      m_pButtonRestore->setFixedSize(QSize(31, 30));
      m_pButtonMax->setFixedSize(QSize(31, 30));
      m_pButtonClose->setFixedSize(QSize(31, 30));

      m_pHBRightTopLayout->addWidget(m_pLab);

      m_pHBRightTopLayout->addSpacing(0);
      m_pHBRightTopLayout->addWidget(m_pButtonMin);
      m_pHBRightTopLayout->addWidget(m_pButtonRestore);
      m_pHBRightTopLayout->addWidget(m_pButtonMax);
      m_pHBRightTopLayout->addWidget(m_pButtonClose);

      m_pRightWidget->setLayout(m_pHBRightTopLayout);


      m_pHBRightBottomLayout->setSpacing(0);
      m_pHBRightBottomLayout->addSpacing(12);
      m_pHBRightBottomLayout->addWidget(m_pText);
      m_pHBRightBottomLayout->addSpacing(12);
    //  m_pHBRightBottomLayout->addStretch(0);


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


      this->setButtonType(MIN_MAX_BUTTON);
      this->setLayout(m_pHBLayout);

      connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
      connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
      connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
      connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
      connect(m_pBtnClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));

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



// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void Widget::setButtonType(ButtonType buttonType)
{
	m_buttonType = buttonType;

	switch (buttonType)
	{
	case MIN_BUTTON:
		{
			m_pButtonRestore->setVisible(false);
			m_pButtonMax->setVisible(false);
		}
		break;
	case MIN_MAX_BUTTON:
		{
			m_pButtonRestore->setVisible(false);
		}
		break;
	case ONLY_CLOSE_BUTTON:
		{
			m_pButtonMin->setVisible(false);
			m_pButtonRestore->setVisible(false);
			m_pButtonMax->setVisible(false);
		}
		break;
	default:
		break;
	}
}





// 保存窗口最大化前窗口的位置以及大小;
void Widget::saveRestoreInfo(const QPoint point, const QSize size)
{
	m_restorePos = point;
	m_restoreSize = size;
}
// 获取窗口最大化前窗口的位置以及大小;
void Widget::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePos;
	size = m_restoreSize;
}


/*
// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作;
void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
	// 只有存在最大化、还原按钮时双击才有效;
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		// 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
		// 或者通过单独设置变量来表示当前窗口状态;
		if (m_pButtonMax->isVisible())
		{
			onButtonMaxClicked();
		}
		else
		{
			onButtonRestoreClicked();
		}
	}

	return QWidget::mouseDoubleClickEvent(event);
}
*/



void Widget::onButtonCloseClicked()
{
    exit(0);
}

void Widget::onButtonMinClicked()
{
	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide();    //设置了Qt::Tool 如果调用showMinimized()则窗口就销毁了？？？
	}
	else
	{
		showMinimized();
	}
}
void Widget::onButtonRestoreClicked()
{
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(true);
        QPoint windowPos;
        QSize windowSize;
        this->getRestoreInfo(windowPos, windowSize);
        this->setGeometry(QRect(windowPos, windowSize));
}

void Widget::onButtonMaxClicked()
{
   m_pButtonMax->setVisible(false);
   m_pButtonRestore->setVisible(true);

  this->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
  QRect desktopRect = QApplication::desktop()->availableGeometry();
  QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
  setGeometry(FactRect);
}

Widget::~Widget()
{
    //delete ui;
}
