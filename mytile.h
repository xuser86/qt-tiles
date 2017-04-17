#ifndef MYTILE_H
#define MYTILE_H

#include <QGraphicsItem>
#include <QtGui>
#include <QtCore>



class MyTile : public QGraphicsItem
{

public:
    //explicit MyTile(QObject *parent = 0);
    MyTile(qreal x, qreal y, qreal width, qreal height, qreal margin=5, qreal cellsize=100);

    enum tilestate {grabed, fitmove, steady};

    void advance(int phase);

    enum tilestate gettstate(void);

signals:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF *boundRect;
    //QPointF mousePos;
    bool pressed;
    bool moved;

    void updatePoints(void);
    void fitIntoGridMove(void);

    void fitIntoGridProject(void);
    void doCollision(void);

    QRectF r11,r12,r13;
    QRectF r21,r22,r23;
    QRectF r31,r32,r33;

    int rectX;
    int rectY;

    int targetWidth;
    int targetHeight;
    int targetX;
    int targetY;

    enum tilestate tstate;

    qreal margin;
    qreal cellsize;
    QColor maincolor;
};

#endif // MYTILE_H
