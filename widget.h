#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QTextEdit>
enum ButtonType
{
	MIN_BUTTON = 0,			// 最小化和关闭按钮;
	MIN_MAX_BUTTON ,		// 最小化、最大化和关闭按钮;
	ONLY_CLOSE_BUTTON		// 只有关闭按钮;
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    // 设置标题栏上按钮类型;
    void setButtonType(ButtonType buttonType);

    // 保存/获取 最大化前窗口的位置及大小;
    void saveRestoreInfo(const QPoint point, const QSize size);
    void getRestoreInfo(QPoint& point, QSize& size);


 private slots:
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool        mMoveing;
    QWidget     *m_pLeftWidget;
    QWidget     *m_pRightWidget;
    QPoint       mMovePosition;
    QPushButton *m_pBtnClose;
    QPushButton *m_pBtnTest;

    QLabel      *m_pLab;
    QTextEdit   *m_pText;
    QVBoxLayout *m_pVBLeftLayout;
    QVBoxLayout *m_pVBRightLayout;

    QHBoxLayout *m_pHBRightTopLayout;
    QHBoxLayout *m_pHBRightBottomLayout;

    // 最大化，最小化变量;
    QPoint m_restorePos;
    QSize m_restoreSize;

    // 按钮类型;
    ButtonType m_buttonType;
    QPushButton * m_pButtonMin;			// 最小化按钮;
    QPushButton * m_pButtonRestore;		// 最大化还原按钮;
    QPushButton * m_pButtonMax;			// 最大化按钮;
    QPushButton * m_pButtonClose;		// 关闭按钮;





};

#endif // WIDGET_H
