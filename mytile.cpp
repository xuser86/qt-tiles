#include "mytile.h"
#include <cassert>
#include <iostream>


MyTile::MyTile(qreal x, qreal y, qreal width, qreal height, qreal margin, qreal cellsize) :
    margin(margin), cellsize(cellsize)
{
    boundRect = new QRectF(x, y, width, height);
    setFlag(ItemIsSelectable);

    tstate = steady;

    maincolor.setHsv(qrand()%60+180,255,200);
}

void MyTile::advance(int phase) {
    if( phase == 0 )
        return;

    if( tstate == steady ) {
        prepareGeometryChange();
        fitIntoGridProject();
        doCollision();
        fitIntoGridMove();
        update();
    }
}

MyTile::tilestate MyTile::gettstate() {
    return tstate;
}

QRectF MyTile::boundingRect() const {
    return *boundRect;
}

void MyTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    updatePoints();

    painter->fillRect(*boundRect, QBrush(maincolor));

    QColor sel_color(Qt::white);
    //sel_color.setHsv( ((maincolor.hue()+180)%360), 255, 127 );

    if(rectX == 1 && rectY == 1) {
        painter->fillRect(r11, QBrush(sel_color));
    }
    if(rectX == 1 && rectY == 2) {
        painter->fillRect(r12, QBrush(sel_color));
    }
    if(rectX == 1 && rectY == 3) {
        painter->fillRect(r13, QBrush(sel_color));
    }
    if(rectX == 2 && rectY == 1) {
        painter->fillRect(r21, QBrush(sel_color));
    }
    if(rectX == 2 && rectY == 2) {
        painter->fillRect(r22, QBrush(sel_color));
    }
    if(rectX == 2 && rectY == 3) {
        painter->fillRect(r23, QBrush(sel_color));
    }
    if(rectX == 3 && rectY == 1) {
        painter->fillRect(r31, QBrush(sel_color));
    }
    if(rectX == 3 && rectY == 2) {
        painter->fillRect(r32, QBrush(sel_color));
    }
    if(rectX == 3 && rectY == 3) {
        painter->fillRect(r33, QBrush(sel_color));
    }

}

void MyTile::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //mousePos = event->pos();

    // dla pewnosci
    tstate = grabed;

    QPointF diff = event->pos() - event->lastPos();
    QPointF topLeft = boundRect->topLeft();
    QPointF bottomRight = boundRect->bottomRight();

    if(rectX == 1 && rectY == 1) {
        topLeft += diff;
    }
    if(rectX == 1 && rectY == 2) {
        topLeft.setY( topLeft.y()+diff.y());
    }
    if(rectX == 1 && rectY == 3) {
        topLeft.setY( topLeft.y()+diff.y());
        bottomRight.setX( bottomRight.x()+diff.x());
    }
    if(rectX == 2 && rectY == 1) {
       topLeft.setX( topLeft.x()+diff.x());
    }
    if(rectX == 2 && rectY == 2) {
        bottomRight += diff;
        topLeft += diff;
    }
    if(rectX == 2 && rectY == 3) {
       bottomRight.setX( bottomRight.x()+diff.x());
    }
    if(rectX == 3 && rectY == 1) {
        topLeft.setX( topLeft.x()+diff.x());
        bottomRight.setY( bottomRight.y()+diff.y());
    }
    if(rectX == 3 && rectY == 2) {
        bottomRight.setY( bottomRight.y()+diff.y());
    }
    if(rectX == 3 && rectY == 3) {
        bottomRight += diff;
    }

    //std::cout << diff.x() << " " << diff.y() << std::endl;

    prepareGeometryChange();

    boundRect->setTopLeft(topLeft);
    boundRect->setBottomRight(bottomRight);

    update();


    QGraphicsItem::mouseMoveEvent(event);
}

void MyTile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    pressed = false;
    tstate = steady;
    rectX = -1; rectY = -1;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void MyTile::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    pressed = true;

    tstate = grabed;

    QPointF mousePos = event->pos();

    if( r11.contains(mousePos) ) {
        rectX = 1; rectY = 1;
    } else if( r12.contains(mousePos) ) {
        rectX = 1; rectY = 2;
    } else if( r13.contains(mousePos) ) {
        rectX = 1; rectY = 3;
    } else if( r21.contains(mousePos) ) {
        rectX = 2; rectY = 1;
    } else if( r22.contains(mousePos) ) {
        rectX = 2; rectY = 2;
    } else if( r23.contains(mousePos) ) {
        rectX = 2; rectY = 3;
    } else if( r31.contains(mousePos) ) {
        rectX = 3; rectY = 1;
    } else if( r32.contains(mousePos) ) {
        rectX = 3; rectY = 2;
    } else if( r33.contains(mousePos) ) {
        rectX = 3; rectY = 3;
    } else {
        rectX = -1; rectY = -1;
    }

    //std::cout << rectX << " " << rectY << std::endl;

    update();

    QGraphicsItem::mousePressEvent(event);
}

void MyTile::updatePoints() {
    QPointF p11(boundRect->topLeft().x(), boundRect->topLeft().y());
    QPointF p12(boundRect->topLeft().x()+10, boundRect->topLeft().y());
    QPointF p13(boundRect->topRight().x()-10, boundRect->topRight().y());
    QPointF p14(boundRect->topRight().x(), boundRect->topRight().y());

    QPointF p21(boundRect->topLeft().x(), boundRect->topLeft().y()+10);
    QPointF p22(boundRect->topLeft().x()+10, boundRect->topLeft().y()+10);
    QPointF p23(boundRect->topRight().x()-10, boundRect->topRight().y()+10);
    QPointF p24(boundRect->topRight().x(), boundRect->topRight().y()+10);

    QPointF p31(boundRect->bottomLeft().x(), boundRect->bottomLeft().y()-10);
    QPointF p32(boundRect->bottomLeft().x()+10, boundRect->bottomLeft().y()-10);
    QPointF p33(boundRect->bottomRight().x()-10, boundRect->bottomRight().y()-10);
    QPointF p34(boundRect->bottomRight().x(), boundRect->bottomRight().y()-10);

    QPointF p41(boundRect->bottomLeft().x(), boundRect->bottomLeft().y());
    QPointF p42(boundRect->bottomLeft().x()+10, boundRect->bottomLeft().y());
    QPointF p43(boundRect->bottomRight().x()-10, boundRect->bottomRight().y());
    QPointF p44(boundRect->bottomRight().x(), boundRect->bottomRight().y());


    r11 = QRectF(p11,p22);
    r12 = QRectF(p12,p23);
    r13 = QRectF(p13,p24);

    r21 = QRectF(p21,p32);
    r22 = QRectF(p22,p33);
    r23 = QRectF(p23,p34);

    r31 = QRectF(p31,p42);
    r32 = QRectF(p32,p43);
    r33 = QRectF(p33,p44);
}

void MyTile::fitIntoGridMove() {
    //int targetWidth = ;
    if(     targetWidth == -1 &&
            targetHeight == -1 &&
            targetX == -1 &&
            targetY == -1 ) {

        return;
    }

    int currentY = boundRect->top();
    int currentX = boundRect->left();
    int currentWidth = boundRect->width();
    int currentHeight = boundRect->height();


    if( targetWidth != -1 ) {
        if( targetWidth > currentWidth ) {
            boundRect->setRight( (int)boundRect->right()+1 );
        } else {
            boundRect->setRight( (int)boundRect->right()-1 );
        }
    }

    if( targetHeight != -1 ) {
        if( targetHeight > currentHeight ) {
            boundRect->setBottom( (int)boundRect->bottom()+1 );
        } else {
            boundRect->setBottom( (int)boundRect->bottom()-1 );
        }
    }

    if( targetX != -1 ) {
        if( targetX < currentX ) {
            boundRect->setLeft( (int)boundRect->left()-1 );
        } else {
            boundRect->setLeft( (int)boundRect->left()+1 );
        }
    }

    if( targetY != -1 ) {
        if( targetY < currentY ) {
            boundRect->setTop( (int)boundRect->top()-1 );
        } else {
            boundRect->setTop( (int)boundRect->top()+1 );
        }
    }

}

void MyTile::fitIntoGridProject() {

    // obecne wartosci
    int currentY = boundRect->top();
    int currentX = boundRect->left();
    int currentWidth = boundRect->width();
    int currentHeight = boundRect->height();

    // wartosci do uzyskania
    targetWidth = -1;
    targetHeight = -1;
    targetX = -1;
    targetY = -1;

    if( currentHeight < cellsize ) {
        // zabezpieczenie przed zbyt malym klockiem
        targetHeight = cellsize;
    } else if( currentHeight % (int)cellsize != 0 ) {
        if( currentHeight % (int)cellsize > cellsize/2 ) {
            // zaokraglam do gory
            targetHeight = currentHeight - currentHeight % (int)cellsize + (int)cellsize;
        } else {
            // zaokraglam do dolu
            targetHeight = currentHeight - currentHeight % (int)cellsize;
        }
    }

    if( currentWidth < cellsize ) {
        // zabezpieczenie przed zbyt malym klockiem
        targetWidth = cellsize;
    } else if( currentWidth % (int)cellsize != 0 ) {
        if( currentWidth % (int)cellsize > cellsize/2 ) {
            // j.w.
            targetWidth = currentWidth - currentWidth % (int)cellsize + (int)cellsize;
        } else {
            // j.w.
            targetWidth = currentWidth - currentWidth % (int)cellsize;
        }
    }

    // wyznaczenie pozycji X
    if( currentX % (int)cellsize !=0 ) {
        // wyznaczenie reszty o ksztalcie pily
        int modRemain = currentX % (int)cellsize;
        if(modRemain < 0) {
            modRemain += (int)cellsize;
        }

        if( modRemain < (int)cellsize/2 ) {
            targetX = currentX - modRemain;
        } else {
            targetX = currentX - modRemain + cellsize;
        }

        //std::cout << targetX << " " << currentX << " " << modRemain << " " << cellsize << std::endl;
    }
//return;
    // wyznaczenie pozycji Y
    if( currentY % (int)cellsize !=0 ) {
        // wyznaczenie reszty o ksztalcie pily
        int modRemain = currentY % (int)cellsize;
        if(modRemain < 0) {
            modRemain += (int)cellsize;
        }

        if( modRemain < (int)cellsize/2 ) {
            targetY = currentY - modRemain;
        } else {
            targetY = currentY - modRemain + cellsize;
        }
    }

}

void MyTile::doCollision() {
    if( tstate == grabed )
        return;

    int currentY = boundRect->top();
    int currentX = boundRect->left();


    if( !scene()->collidingItems(this).isEmpty() ) {
        QGraphicsItem *collindingItem = scene()->collidingItems(this).first();

        QPointF collRectCenter = collindingItem->boundingRect().center();
        QPointF thisRectCenter = boundRect->center();

        if( collRectCenter.x() > thisRectCenter.x() ) {
            targetX = currentX - cellsize;
        } else { //if ( collRectCenter.x() < thisRectCenter.x() ) {
            targetX = currentX + cellsize;
        } //else {
         //   targetX = currentX + cellsize * (qrand()>0.5?-1:1);
        //}

        if ( collRectCenter.y() > thisRectCenter.y() ) {
            targetY = currentY - cellsize;
        } else { // if ( collRectCenter.y() < thisRectCenter.y() ) {
            targetY = currentY + cellsize;
        } //else {
            //targetY = currentY + cellsize * (qrand()>0.5?-1:1);
        //}
    }
}
