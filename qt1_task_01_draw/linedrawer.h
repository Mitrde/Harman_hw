#ifndef LINEDRAWER_H
#define LINEDRAWER_H


#include <QPainter>
#include <QtMath>
#include <QWidget>
#include <QVector>

class LineDrawer:public QWidget
{
    Q_OBJECT


public:
    LineDrawer(QWidget *pParent = 0,size_t num = 0 );
public slots:
    void numCh(size_t);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void fillVector(size_t num);
    size_t num;
    size_t fontSize;
    QPixmap m_Pixmap;
    QVector<QPointF> m_points;
    QVector<QPointF> m_numbers;
};

#endif // LINEDRAWER_H
