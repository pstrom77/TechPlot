#include "tp_Projection.h"

namespace tp {

  Projection::Projection() :
    mProjectionType(ORTHO),
    mWidth(400.0),
    mHeight(400.0),
    mCameraMatrix(Matrix::Identity),
    mModelMatrix(Matrix::Identity)
  {
  }
    
  void Projection::setViewPort(int left, int right, int bottom, int top) {
    mHeight = static_cast<double>(top-bottom);
    mWidth  = static_cast<double>(right-left);

    const double zNear = 0.01;
    const double zFar = 1000.0;
    
    setOrtoProjection(0.0,   mWidth,mHeight,0.0,zNear,zFar);
    
    double aspect = mWidth/mHeight;
    double fW = tan(25*DEGTORAD)*zNear;
    double fH = fW/aspect;;
    setFrustumProjection(-fW,fW,-fH,fH,zNear,zFar);      
  }

  Matrix Projection::getProjectionMatrix() const {
    if(mProjectionType == ORTHO) 
      return mOrthographicProjectionMatrix;
    else 
      return mFrustumProjectionMatrix;	
  }

  void Projection::setProjectionType(ProjectionType type ) { 
    mProjectionType = type;
  }

  void Projection::setOrtoProjection(double left, double right, double bottom, double top, double near, double far) {
    double* m = &mOrthographicProjectionMatrix.get(0,0);
    m[0] = 2.0/(right-left); m[1] = 0.0;              m[2]  = 0.0;             m[3] = -(right+left)/(right-left);
    m[4] = 0.0;              m[5] = 2.0/(top-bottom); m[6] = 0.0;              m[7] = -(top+bottom)/(top-bottom);
    m[8] = 0.0;              m[9] = 0.0;              m[10] = -2.0/(far-near); m[11] = -(far+near)/(far-near);
    m[12] = 0.0;             m[13] = 0.0;             m[14] = 0.0;             m[15] = 1.0;
  }


  void Projection::setFrustumProjection(double left, double right, double bottom, double top, double near, double far) {
    Matrix* m = &mFrustumProjectionMatrix;
    m->get(0,0) = 2.0*near/(right-left); m->get(0,1) = 0.0;                   m->get(0,2) = (right+left)/(right-left);  m->get(0,3) = 0.0;
    m->get(1,0) = 0.0;                   m->get(1,1) = 2.0*near/(top-bottom); m->get(1,2) = (top+bottom)/(top-bottom);  m->get(1,3) = 0.0;
    m->get(2,0) = 0.0;                   m->get(2,1) = 0.0;                   m->get(2,2) = -(far+near)/(far-near);     m->get(2,3) = -(2*far*near)/(far-near);
    m->get(3,0) = 0.0;                   m->get(3,1) = 0.0;                   m->get(3,2) = -1.0;                       m->get(3,3) = 0.0;
  }

  QVector3D Projection::getScreenCoordinates(const QVector3D v) {
    if(mProjectionType == ORTHO) 
      return getScreenCoordinatesFromOrtho(v); 
    else  
      return getScreenCoordinatesFromFrustum(v); 
  }

  QVector3D Projection::getScreenCoordinatesFromOrtho(const QVector3D& v) {
    QVector3D v1 = (mOrthographicProjectionMatrix*mCameraMatrix*QVector4D(v)).toVector3D();
    v1.setX( (v1.x()*0.5 +0.5)*mWidth);
    v1.setY( mHeight- (v1.y()*0.5 + 0.5)*mHeight);   
    return v1;
  }

  QVector3D Projection::getScreenCoordinatesFromFrustum(const QVector3D& vec) {
    std::cout << mCameraMatrix << std::endl;
    QVector4D g  = (mFrustumProjectionMatrix*(mCameraMatrix*(mModelMatrix*vec))).toVector3DAffine();
    return QVector3D( (g.x()*0.5+0.5)*mWidth, mHeight - (g.y()*0.5+0.5)*mHeight,  (1.0+g.z())*0.5);
  }

  
}
