#include "renderarea.h"

#include <QPainter>
#include <stdio.h>
#include <QFileDialog>
#include <QTextStream>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, LINE_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i < idx_points; i+=2)
        painter.drawLine(points[i], points[i+1], points[i+2], points[i+3]);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::mouseReleaseEvent(QMouseEvent * event)
{
    points[idx_points++] = event->x();
    points[idx_points++] = event->y();
    points[idx_points] =  event->x();
    points[idx_points + 1] =  event->y();
    update();
}

void RenderArea::mouseMoveEvent(QMouseEvent * event)
{
    points[idx_points] = event->x();
    points[idx_points + 1] = event->y();
    update();
}

void RenderArea::save()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/blacksocks/Documents/robotics/Nutella/", tr("Text (*.txt)"));
    // Add ".txt" extension if there is another extension
    if(filename.right(4).compare(".txt") != 0)
        filename.append(".txt");
    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly)) {
        printf("An error occured during saving\n");
        return;
    }
    QTextStream out(&f);
    for (int i = 0; i < idx_points; i+=2)
        out << points[i] << " " << points[i+1] << "\n";
    f.close();
}

void RenderArea::clear()
{
    idx_points = 0;
}
