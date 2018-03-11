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
      this->resize(498,340); //������
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



// ���ñ������ϰ�ť����;
// ���ڲ�ͬ���ڱ������ϵİ�ť����һ�������Կ����Զ���������еİ�ť;
// �����ṩ���ĸ���ť���ֱ�Ϊ��С������ԭ����󻯡��رհ�ť�������Ҫ������ť�������������;
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





// ���洰�����ǰ���ڵ�λ���Լ���С;
void Widget::saveRestoreInfo(const QPoint point, const QSize size)
{
	m_restorePos = point;
	m_restoreSize = size;
}
// ��ȡ�������ǰ���ڵ�λ���Լ���С;
void Widget::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePos;
	size = m_restoreSize;
}


/*
// ˫����Ӧ�¼�����Ҫ��ʵ��˫��������������󻯺���С������;
void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
	// ֻ�д�����󻯡���ԭ��ťʱ˫������Ч;
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		// ͨ����󻯰�ť��״̬�жϵ�ǰ�����Ǵ�����󻯻���ԭʼ��С״̬;
		// ����ͨ���������ñ�������ʾ��ǰ����״̬;
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
		hide();    //������Qt::Tool �������showMinimized()�򴰿ھ������ˣ�����
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
