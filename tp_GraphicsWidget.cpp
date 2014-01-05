#include "tp_GraphicsWidget.h"
#include "tp_GraphicsItem.h"

namespace tp {

  GraphicsWidget::GraphicsWidget(QWidget* parent): 
    QWidget(parent), 
    mRoll(0.0), 
    mPitch(0.0), 
    mYaw(0.0),
    mCameraPosition(0,0,-10) {

    
    QFont font("Helvetica");
    font.setPixelSize(10);
    setFont(font);

    mProjection.setProjectionType(Projection::FRUSTUM);
    // mProjection.setProjectionType(Projection::ORTHO);

    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
  }


  QVector3D GraphicsWidget::toScreenCoordinates(QVector3D v) {
    mCameraMatrix = Matrix::RotationMatrix(mRoll*DEGTORAD,mPitch*DEGTORAD,mYaw*DEGTORAD) +  Matrix::Translation(mCameraPosition);
    mProjection.setCameraMatrix(mCameraMatrix);
    mProjection.setModelMatrix(mModelMatrix);
    return mProjection.getScreenCoordinates(v);
  }



  void GraphicsWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    paintOrigin();
    paintTree();
    paintInfo();
  }


  void GraphicsWidget::paintTree() {

    QPainter painter(this);

    for (int i = 0; i < mTree->topLevelItemCount(); i++) {
      GraphicsItem* topItem = dynamic_cast<GraphicsItem*>(mTree->topLevelItem(i));
      mModelMatrix = topItem->getMatrix();
      topItem->draw(&painter);
      for(int j = 0; j < topItem->childCount(); j++) {
	GraphicsItem* item = dynamic_cast<GraphicsItem*>(topItem->child(j));
	mModelMatrix = mModelMatrix*item->getMatrix();
	item->draw(&painter);
      }
    }


    
    painter.end();

  }

  void GraphicsWidget::paintOrigin() {
    QPainter painter(this);
    QVector3D origin = toScreenCoordinates( QVector3D( 0.0, 0.0, 0.0));
    QVector3D xAxis  = toScreenCoordinates( QVector3D( 1.0, 0.0, 0.0));
    QVector3D yAxis  = toScreenCoordinates( QVector3D( 0.0, 1.0, 0.0));
    QVector3D zAxis  = toScreenCoordinates( QVector3D( 0.0, 0.0, 1.0));

    painter.setPen(Qt::red);
    painter.drawLine(origin.x(), origin.y(), xAxis.x(), xAxis.y());

    painter.setPen(Qt::green);
    painter.drawLine(origin.x(), origin.y(), yAxis.x(), yAxis.y());

    painter.setPen(Qt::blue);
    painter.drawLine(origin.x(), origin.y(), zAxis.x(), zAxis.y());

    
    painter.end();
  }

  void GraphicsWidget::paintInfo() {
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawText(10,height()-30,QString("Roll: %1 Pitch: %2 Yaw:%3").arg(mRoll,3,'f',1).arg(mPitch,3,'f',1).arg(mYaw,3,'f',1));
    painter.drawText(10,height()-15,QString("X: %1 Y: %2 Z:%3").arg(mCameraPosition.x(),3,'f',1).arg(mCameraPosition.y(),3,'f',1).arg(mCameraPosition.z(),3,'f',1));
    painter.end();
    
  }


  void GraphicsWidget::mousePressEvent(QMouseEvent *event)
  {
    mLastMousePos = event->pos();
  }

  void GraphicsWidget::mouseMoveEvent(QMouseEvent *event)
  {
    int dx = event->x() - mLastMousePos.x();
    int dy = event->y() - mLastMousePos.y();
  
    if (event->buttons() & Qt::LeftButton) {
    
      if(event->modifiers() == Qt::ControlModifier) {
	mYaw   += dy;	
      } else if ( event->modifiers() == Qt::AltModifier) {
	mCameraPosition.setX( mCameraPosition.x() + dx/32.0);
	mCameraPosition.setY( mCameraPosition.y() - dy/32.0);
      } else {
	mPitch += dx;
	mRoll +=dy;     
      }
    }
    mLastMousePos = event->pos();
    update();
  }


  void GraphicsWidget::wheelEvent(QWheelEvent* event) 
  {
    event->accept();  
    mCameraPosition.setZ( mCameraPosition.z() +  event->delta()/32.0);
    update();
  }

}
