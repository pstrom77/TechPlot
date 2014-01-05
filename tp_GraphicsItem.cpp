#include "tp_GraphicsItem.h"
#include "tp_Matrix.h"
#include "tp_GraphicsWidget.h"


namespace tp {

  GraphicsItem::GraphicsItem(QTreeWidget* parent):
    QTreeWidgetItem(parent),
    mMatrix(Matrix::Identity),
    mGraphicsWidget(0) {
  }

  GraphicsItem::GraphicsItem(QTreeWidgetItem* parent):
    QTreeWidgetItem(parent),
    mMatrix(Matrix::Identity),
    mGraphicsWidget(0) {
  }
 
  void GraphicsItem::draw(QPainter* painter) {
    QVector3D v1 = mGraphicsWidget->toScreenCoordinates(QVector3D(-1.0, -1.0, -1.0));
    QVector3D v2 = mGraphicsWidget->toScreenCoordinates(QVector3D( 1.0, -1.0, -1.0));
    QVector3D v3 = mGraphicsWidget->toScreenCoordinates(QVector3D( 1.0, -1.0,  1.0));
    QVector3D v4 = mGraphicsWidget->toScreenCoordinates(QVector3D(-1.0, -1.0,  1.0));

    QVector3D v5 = mGraphicsWidget->toScreenCoordinates(QVector3D(-1.0, 1.0, -1.0));
    QVector3D v6 = mGraphicsWidget->toScreenCoordinates(QVector3D( 1.0, 1.0, -1.0));
    QVector3D v7 = mGraphicsWidget->toScreenCoordinates(QVector3D( 1.0, 1.0,  1.0));
    QVector3D v8 = mGraphicsWidget->toScreenCoordinates(QVector3D(-1.0, 1.0,  1.0));

    painter->setPen(Qt::black);
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

}
