#include "linedrawer.h"
#include <QtWidgets>

LineDrawer::LineDrawer( QWidget *pParent, size_t num)
    :QWidget(pParent), num(num)
{
    setAttribute(Qt::WA_NoSystemBackground, true);


}

void LineDrawer::numCh(size_t num)
{
    this->num = num;

    m_Pixmap.fill(Qt::white);
    QPainter painter(&m_Pixmap);

    fillVector(num);

    painter.setPen(QPen(Qt::black, 0));
    painter.setRenderHint(QPainter::Antialiasing,true);


    for(size_t i = 0; i<num;++i)
    {
        painter.setFont(QFont("Times",fontSize,QFont::Normal));
        painter.drawText(m_numbers[i], QString::number(i));

        for(size_t j = i;j<num;++j)
        {
            painter.drawLine(m_points[i],m_points[j]);
        }
    }



}

void LineDrawer::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,m_Pixmap);

}

void LineDrawer::resizeEvent(QResizeEvent *event)
{
    QSize w_size = event->size();
    m_Pixmap = QPixmap(w_size);
    m_Pixmap.fill(Qt::white);

    QPainter painter(&m_Pixmap);

    fillVector(num);

    painter.setPen(QPen(Qt::black, 0));
    painter.setRenderHint(QPainter::Antialiasing,true);


    for(size_t i = 0; i<num;++i)
    {
        painter.setFont(QFont("Times",fontSize,QFont::Normal));
        painter.drawText(m_numbers[i], QString::number(i));

        for(size_t j = i;j<num;++j)
        {
            painter.drawLine(m_points[i],m_points[j]);            
        }
    }
}

void LineDrawer::fillVector(size_t num)
{
    m_points.clear();
    m_numbers.clear();
    int w_size = qMin(m_Pixmap.width(),m_Pixmap.height());
    fontSize = w_size/(4* qPow(num,0.7));
    for(size_t i = 0; i < num; ++i)
    {        
        qreal fAngle = ::qDegreesToRadians(360.0 * i / num);
        qreal x = w_size/2 + cos(fAngle)*0.30*w_size;
        qreal y = w_size/2 + sin(fAngle)*0.30*w_size;
        qreal xn = x+cos(fAngle)* w_size /(100 * num)+cos(fAngle)*fontSize*0.8 - fontSize/2;
        qreal yn = y+sin(fAngle)* w_size /(100 * num)+sin(fAngle)*fontSize*0.8 + fontSize/2;

        m_points.push_back(QPointF(x,y));
        m_numbers.push_back(QPointF(xn,yn));
    }
}
