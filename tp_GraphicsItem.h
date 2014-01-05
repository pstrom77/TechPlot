#ifndef __TP__GRAPHICS_ITEM_H__
#define __TP__GRAPHICS_ITEM_H__

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "tp_Matrix.h"
#include "tp_GraphicsWidget.h"

namespace tp {


  class GraphicsItem: public QTreeWidgetItem {
  public:
    GraphicsItem(QTreeWidget* parent=0);
    GraphicsItem(QTreeWidgetItem* parent=0);

    Matrix getMatrix() const { return mMatrix; }
    void draw(QPainter* painter);
    void setGraphicsWidget(GraphicsWidget* gw) { mGraphicsWidget = gw; }
    
    void rotateX(double angle) { mMatrix.rotateX(angle); }
    void rotateY(double angle) { mMatrix.rotateY(angle); }
    void rotateZ(double angle) { mMatrix.rotateZ(angle); }
    void translate(QVector3D v) { mMatrix.translate(v); }
    
  private:
    Matrix mMatrix;
    GraphicsWidget* mGraphicsWidget;

  };
}
#endif
