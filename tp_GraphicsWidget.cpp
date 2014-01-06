#include "tp_GraphicsWidget.h"
#include "tp_GraphicsItem.h"

namespace tp {

  GraphicsWidget::GraphicsWidget(QWidget* parent): 
    QWidget(parent)
  {

    mCameraMatrix = Matrix::Translation(0,0,-100);

    QFont font("Helvetica");
    font.setPixelSize(10);
    setFont(font);

    mProjection.setProjectionType(Projection::FRUSTUM);
    // mProjection.setProjectionType(Projection::ORTHO);

    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));
  }


  QVector3D GraphicsWidget::toScreenCoordinates(QVector3D v) {
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
    paintChildren(mTree->getRoot());
  }

  void GraphicsWidget::paintChildren(GraphicsItem* item) {
    
    mModelMatrix = mModelMatrix*item->getMatrix();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    item->setGraphicsWidget(this);
    item->draw(&painter);
    painter.end();

    if(item->childCount() < 1) return;

    for(int j = 0; j < item->childCount(); j++) {
      mModelMatrixStack.push(mModelMatrix);
      GraphicsItem* child = dynamic_cast<GraphicsItem*>(item->child(j));
      paintChildren(child);
      mModelMatrix=mModelMatrixStack.pop();    }
    
  }
  
  void GraphicsWidget::paintOrigin() {
    mModelMatrix = Matrix::Identity;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QVector3D origin = toScreenCoordinates( QVector3D( 0.0, 0.0, 0.0));
    QVector3D xAxis  = toScreenCoordinates( QVector3D( 10.0, 0.0, 0.0));
    QVector3D yAxis  = toScreenCoordinates( QVector3D( 0.0, 10.0, 0.0));
    QVector3D zAxis  = toScreenCoordinates( QVector3D( 0.0, 0.0, 10.0));

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
    painter.drawText(10,height()-30,QString("Roll: %1 Pitch: %2 Yaw:%3").arg(mCameraMatrix.roll()*RADTODEG,3,'f',1).arg(mCameraMatrix.pitch()*RADTODEG,3,'f',1).arg(mCameraMatrix.yaw()*RADTODEG,3,'f',1));
    painter.drawText(10,height()-15,QString("X: %1 Y: %2 Z:%3").arg(mCameraMatrix.get(0,3),3,'f',1).arg(mCameraMatrix.get(1,3),3,'f',1).arg(mCameraMatrix.get(2,3),3,'f',1));
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
    mYaw = 0;
    mRoll = 0;
    mPitch = 0;
    if (event->buttons() & Qt::LeftButton) {
    
      if(event->modifiers() == Qt::ControlModifier) {
	mYaw   += dy;	
      } else if ( event->modifiers() == Qt::AltModifier) {
	mCameraMatrix = Matrix::Translation(dx/32.0,-dy/32.0,0)*mCameraMatrix ;
      } else {
	mPitch += dx;
	mRoll +=dy;     
      }
    }
    mLastMousePos = event->pos();
    mCameraMatrix = mCameraMatrix*Matrix::RotationMatrix(mRoll*DEGTORAD,mPitch*DEGTORAD,mYaw*DEGTORAD);
    update();
  }


  void GraphicsWidget::wheelEvent(QWheelEvent* event) 
  {
    event->accept();  
    mCameraMatrix =  Matrix::Translation(0,0,event->delta()/32.0)*mCameraMatrix;
    update();
  }

}
