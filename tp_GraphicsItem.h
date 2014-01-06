#ifndef __TP__GRAPHICS_ITEM_H__
#define __TP__GRAPHICS_ITEM_H__

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "tp_Matrix.h"


namespace tp {
  
  class GraphicsWidget;
  class GraphicsItem: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(double rotationX READ rotationX WRITE setRotationX)
    Q_PROPERTY(double rotationY READ rotationY WRITE setRotationY)
    Q_PROPERTY(double rotationZ READ rotationZ WRITE setRotationZ)
    Q_PROPERTY(double translateX READ translateX WRITE setTranslateX)
    Q_PROPERTY(double translateY READ translateY WRITE setTranslateY)
    Q_PROPERTY(double translateZ READ translateZ WRITE setTranslateZ)
    Q_PROPERTY(double scaleX READ scaleX WRITE setScaleX)
    Q_PROPERTY(double scaleY READ scaleY WRITE setScaleY)
    Q_PROPERTY(double scaleZ READ scaleZ WRITE setScaleZ)
    Q_PROPERTY(QVariant lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QVariant fillColor READ fillColor WRITE setFillColor)
    Q_PROPERTY(bool  brushStyle READ brushStyle WRITE setBrushStyle)
    Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int itemType READ itemType WRITE setItemType)

  public:
    GraphicsItem(QString name, GraphicsItem* parent=0);
    ~GraphicsItem();

    enum ItemType { Box=0, Line=1, Plane=2};

    int nrChildren() const {
      int nr = mChildren.count();
      for (int i = 0; i < mChildren.count(); i++) {
	nr+= mChildren[i]->nrChildren();
      }
      return nr;
    }

    bool removeChildren(int from, int to) { 
      if(from < 0 || to > mChildren.size()) 
	return false;
      
      for(int row = from; row < to; row++) 
	{
	  delete mChildren.takeAt(from);
	}
	return true;

    }
    
    bool insertChildren(int position, int count, int columns)
    {
      for (int row = 0; row < count; ++row) {
	GraphicsItem *item = new GraphicsItem("New Item", this);
      }

      return true;
    }

    void addChild(GraphicsItem* child) { mChildren.append(child); }
    GraphicsItem* child(int row) { return mChildren.value(row); }
    int childCount() const { return mChildren.count(); }
    int columnCount() const { return 1; }
    QVariant data(int column) const { 
      Q_UNUSED(column);
      return mName;
    }
    int row() const { 
      if(mParent) return mParent->mChildren.indexOf(const_cast<GraphicsItem*>(this)); 
      return 0;
    }

    GraphicsItem* parent() { return mParent; }

    Matrix getMatrix() const;
    void draw(QPainter* painter);
    void setGraphicsWidget(GraphicsWidget* gw) { mGraphicsWidget = gw; }
    
    void setName(QString name) {mName = name; }
    void setRotationX(double angle) { mRotationX=angle; }
    void setRotationY(double angle) { mRotationY=angle; }
    void setRotationZ(double angle) { mRotationZ=angle; }
    void setTranslateX(double v) {mTranslate.setX(v); }
    void setTranslateY(double v) {mTranslate.setY(v); }
    void setTranslateZ(double v) {mTranslate.setZ(v); }
    void setScaleX(double v) {mScale.setX(v); }
    void setScaleY(double v) {mScale.setY(v); }
    void setScaleZ(double v) {mScale.setZ(v); }
    void setTranslate(QVector3D v) {mTranslate = v; }
    void setPen(QPen pen) { mPen = pen; }
    void setLineColor(QVariant color) { mPen.setColor(color.value<QColor>());}
    void setFillColor(QVariant color) { mBrush.setColor(color.value<QColor>());}
    void setBrushStyle(bool fill) { 
      if(fill) 
	mBrush.setStyle(Qt::SolidPattern); 
      else  
	mBrush.setStyle(Qt::NoBrush);
    }
    void setLineWidth(double lineWidth) { mPen.setWidthF(lineWidth);} 
    void setItemType(int type) { mItemType = type; }

    QString name() const { return mName; }
    double rotationX() const { return mRotationX; }
    double rotationY() const { return mRotationY; }
    double rotationZ() const { return mRotationZ; }
    double translateX() const { return mTranslate.x(); }
    double translateY() const { return mTranslate.y(); }
    double translateZ() const { return mTranslate.z(); }
    double scaleX() const { return mScale.x(); }
    double scaleY() const { return mScale.y(); }
    double scaleZ() const { return mScale.z(); }
    QVector3D translate() { return mTranslate; }
    QPen pen() const { return mPen; }
    QVariant lineColor() const { return mPen.color(); }
    QVariant fillColor() const { return mBrush.color(); }
    bool brushStyle() const { return mBrush.style() == Qt::SolidPattern; }
    double lineWidth() const { return mPen.widthF(); }
    int itemType() const { return mItemType; }

  private:
    QVector3D toScreenCoordinates(QVector3D);
    void drawLine(QPainter*);
    void drawPlane(QPainter*);
    void drawBox(QPainter*);
		   
  private:
    QList<GraphicsItem*> mChildren;
    GraphicsItem* mParent;
    QString mName;
    
    GraphicsWidget* mGraphicsWidget;
    double mRotationX, mRotationY, mRotationZ;
    QVector3D mTranslate;
    QVector3D mScale;
    int mItemType;
    QBrush mBrush;
    QPen mPen;
  };
}
#endif
