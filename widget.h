#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


 private slots:
      void Close();

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




};

#endif // WIDGET_H
