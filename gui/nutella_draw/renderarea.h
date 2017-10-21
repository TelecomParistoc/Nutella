#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>

#define LINE_WIDTH     2
#define MAX_NB_POINTS  256

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void save();
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;

private:
    const int nb_points = MAX_NB_POINTS;
    int points[MAX_NB_POINTS * 2];
    int idx_points = 0;
};

#endif // RENDERAREA_H
