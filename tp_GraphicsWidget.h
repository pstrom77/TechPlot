#ifndef __TP__GRAPHICS_WIDGET_H__
#define __TP__GRAPHICS_WIDGET_H__

#include <QtGui>
#include <QWidget>
#include <QTreeWidget>

#include "tp_Projection.h"
#include "tp_Matrix.h"

namespace tp {

  class GraphicsItem;

  class GraphicsWidget: public QWidget {
    Q_OBJECT
  public:
    GraphicsWidget(QWidget* parent=0);

    //TODO: Change to model view control...setModel
    void setTree(QTreeWidget* tree) { mTree = tree; }

    QVector3D toScreenCoordinates(QVector3D);

  protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent* event) { mProjection.setViewPort(0,event->size().width(),0,event->size().height()); }

  private:
    void paintOrigin();
    void paintTree();
    void paintChildren(GraphicsItem* item);
    void paintInfo();

  private:    
    Matrix mCameraMatrix;
    Matrix mModelMatrix;
    Projection mProjection;
    double mRoll, mPitch, mYaw;
    QVector3D mCameraPosition;
    QPointF mLastMousePos;

    QTreeWidget* mTree;
    
  };

}

#endif
