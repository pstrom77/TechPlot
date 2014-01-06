#include "tp_GraphicsItem.h"
#include "tp_Matrix.h"
#include "tp_GraphicsWidget.h"


namespace tp {

  GraphicsItem::GraphicsItem(QString name, GraphicsItem* parent):
    mParent(parent),
    mName(name),
    mGraphicsWidget(0),
    mRotationX(0),mRotationY(0),mRotationZ(0),
    mTranslate(0,0,0),
    mScale(1,1,1),
    mItemType(0),
    mPen(Qt::black),
    mBrush(Qt::NoBrush)
  {
    if(mParent) mParent->addChild(this);
  }
 
  GraphicsItem::~GraphicsItem() {
    qDeleteAll(mChildren);
  }

  Matrix GraphicsItem::getMatrix() const { 
    Matrix mat = Matrix::Identity;
    mat.translate(mTranslate);
    mat.rotateX(mRotationX*DEGTORAD);
    mat.rotateY(mRotationY*DEGTORAD);
    mat.rotateZ(mRotationZ*DEGTORAD);
    return mat;
  }
  
  void GraphicsItem::draw(QPainter* painter) {
    qDebug() << mItemType;
    if(mItemType == Box) {
      drawBox(painter);
    } else if ( mItemType == Line) {
      drawLine(painter);
    } else if( mItemType == Plane) {
      drawPlane(painter);
    }
  }

  QVector3D GraphicsItem::toScreenCoordinates(QVector3D v) {
    return mGraphicsWidget->toScreenCoordinates( (Matrix::Scale(mScale)*v).toVector3D());
  }

  void GraphicsItem::drawBox(QPainter* painter) {
    Q_ASSERT(mGraphicsWidget != 0);
    QVector3D v1 = toScreenCoordinates(QVector3D(-1.0, -1.0, -1.0));
    QVector3D v2 = toScreenCoordinates(QVector3D( 1.0, -1.0, -1.0));
    QVector3D v3 = toScreenCoordinates(QVector3D( 1.0, -1.0,  1.0));
    QVector3D v4 = toScreenCoordinates(QVector3D(-1.0, -1.0,  1.0));

    QVector3D v5 = toScreenCoordinates(QVector3D(-1.0, 1.0, -1.0));
    QVector3D v6 = toScreenCoordinates(QVector3D( 1.0, 1.0, -1.0));
    QVector3D v7 = toScreenCoordinates(QVector3D( 1.0, 1.0,  1.0));
    QVector3D v8 = toScreenCoordinates(QVector3D(-1.0, 1.0,  1.0));

    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawLine(v1.x(), v1.y(), v2.x(),v2.y());
    painter->drawLine(v2.x(), v2.y(), v3.x(),v3.y());
    painter->drawLine(v3.x(), v3.y(), v4.x(),v4.y());
    painter->drawLine(v4.x(), v4.y(), v1.x(),v1.y());

    painter->drawLine(v5.x(), v5.y(), v6.x(),v6.y());
    painter->drawLine(v6.x(), v6.y(), v7.x(),v7.y());
    painter->drawLine(v7.x(), v7.y(), v8.x(),v8.y());
    painter->drawLine(v8.x(), v8.y(), v5.x(),v5.y());

    painter->drawLine(v1.x(), v1.y(), v5.x(),v5.y());
    painter->drawLine(v2.x(), v2.y(), v6.x(),v6.y());
    painter->drawLine(v3.x(), v3.y(), v7.x(),v7.y());
    painter->drawLine(v4.x(), v4.y(), v8.x(),v8.y());

  }

  void GraphicsItem::drawLine(QPainter* painter) {
    Q_ASSERT(mGraphicsWidget != 0);
    QVector3D v1 = toScreenCoordinates(QVector3D(0.0, 0.0, 0.0));
    QVector3D v2 = toScreenCoordinates(QVector3D(1.0, 0.0, 0.0));

    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawLine(v1.x(), v1.y(), v2.x(),v2.y());

  }

  void GraphicsItem::drawPlane(QPainter* painter) {
    Q_ASSERT(mGraphicsWidget != 0);
    QVector3D v1 = toScreenCoordinates(QVector3D(-0.5, 0.5, 0.0));
    QVector3D v2 = toScreenCoordinates(QVector3D( 0.5, 0.5, 0.0));
    QVector3D v3 = toScreenCoordinates(QVector3D( 0.5,-0.5, 0.0));
    QVector3D v4 = toScreenCoordinates(QVector3D(-0.5,-0.5, 0.0));
    QPolygonF polygon;
    polygon << QPointF(v1.x(),v1.y())
	    << QPointF(v2.x(),v2.y())
	    << QPointF(v3.x(),v3.y())
	    << QPointF(v4.x(),v4.y());
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawPolygon(polygon);
  }

}
