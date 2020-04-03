#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MyGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }

private:

protected Q_SLOTS:

    void wheelEvent(QWheelEvent *event)
    {
        if(event->delta() > 0)
            scale(1.1, 1.1);
        else
            scale(0.9, 0.9);
    }

};

#endif // MYQGRAPHICSVIEW_H
