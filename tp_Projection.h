#ifndef __TP_PROJECTION_H__
#define __TP_PROJECTION_H__

#include "tp_Matrix.h"

namespace tp {

  class Projection {
  public:
    enum ProjectionType {
      ORTHO, 
      FRUSTUM
    } ;
    Projection();

    Matrix    getProjectionMatrix() const;
    void      setProjectionType(ProjectionType type);
    QVector3D getScreenCoordinates(QVector3D);
    void      setCameraMatrix(Matrix m) { mCameraMatrix = m; }
    void      setModelMatrix(Matrix m) { mModelMatrix = m; }
    void      setViewPort(int left, int right, int bottom, int top);

  private:
    void setOrtoProjection(double left, double right, double bottom, double top, double near, double far);
    void setFrustumProjection(double left, double right, double bottom, double top, double near, double far);
    QVector3D getScreenCoordinatesFromFrustum(const QVector3D& v);
    QVector3D getScreenCoordinatesFromOrtho(const QVector3D& v);
    Matrix mOrthographicProjectionMatrix;
    Matrix mFrustumProjectionMatrix;;
    Matrix mCameraMatrix;
    Matrix mModelMatrix;
    ProjectionType mProjectionType;

    double mWidth;
    double mHeight;
  };

}

#endif
