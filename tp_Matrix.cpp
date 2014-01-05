#include "tp_Matrix.h"


namespace tp {


  Matrix Matrix::Identity(1.0,0.0,0.0,0.0,
			  0.0,1.0,0.0,0.0,
			  0.0,0.0,1.0,0.0,
			  0.0,0.0,0.0,1.0);
  
  Matrix::Matrix() {
    clear();  
  }
  Matrix::Matrix(double m00, double m01, double m02, double m03,
		 double m10, double m11, double m12, double m13,
		 double m20, double m21, double m22, double m23,
		 double m30, double m31, double m32, double m33) {
    get(0,0) = m00; get(0,1) = m01; get(0,2) = m02; get(0,3) = m03;
    get(1,0) = m10; get(1,1) = m11; get(1,2) = m12; get(1,3) = m13;
    get(2,0) = m20; get(2,1) = m21; get(2,2) = m22; get(2,3) = m23;
    get(3,0) = m30; get(3,1) = m31; get(3,2) = m32; get(3,3) = m33;

  }

  Matrix Matrix::RotationX(double angle) {
    Matrix mat;
    mat.get(0,0) = 1.0; mat.get(0,1) = 0.0;         mat.get(0,2) = 0.0;         mat.get(0,3) = 0.0;
    mat.get(1,0) = 0.0; mat.get(1,1) = cos(angle);  mat.get(1,2) = -sin(angle); mat.get(1,3) = 0.0;
    mat.get(2,0) = 0.0; mat.get(2,1) = sin(angle);  mat.get(2,2) = cos(angle);  mat.get(2,3) = 0.0;
    mat.get(3,0) = 0.0; mat.get(3,1) = 0.0;         mat.get(3,2) = 0.0;         mat.get(3,3) = 1.0;    
    return mat;
  }

  Matrix Matrix::RotationY(double angle) {
    Matrix mat; 
    mat.get(0,0) = cos(angle);  mat.get(0,1) = 0.0; mat.get(0,2) = sin(angle); mat.get(0,3) = 0.0;
    mat.get(1,0) = 0.0;         mat.get(1,1) = 1.0; mat.get(1,2) = 0.0;        mat.get(1,3) = 0.0;
    mat.get(2,0) = -sin(angle); mat.get(2,1) = 0;   mat.get(2,2) = cos(angle); mat.get(2,3) = 0.0;
    mat.get(3,0) = 0.0;         mat.get(3,1) = 0.0; mat.get(3,2) = 0.0;        mat.get(3,3) = 1.0;    
   return mat;
  }

  Matrix Matrix::RotationZ(double angle) {
    Matrix mat;
    mat.get(0,0) = cos(angle); mat.get(0,1) = -sin(angle);  mat.get(0,2) = 0.0; mat.get(0,3) = 0.0;
    mat.get(1,0) = sin(angle);  mat.get(1,1) = cos(angle);  mat.get(1,2) = 0.0; mat.get(1,3) = 0.0;
    mat.get(2,0) = 0.0;        mat.get(2,1) = 0;            mat.get(2,2) = 1.0; mat.get(2,3) = 0.0;
    mat.get(3,0) = 0.0;        mat.get(3,1) = 0.0;          mat.get(3,2) = 0.0; mat.get(3,3) = 1.0;    

    return mat;
  }

  Matrix Matrix::RotationMatrix(double roll, double pitch, double yaw) {
    return RotationX(roll)*RotationY(pitch)*RotationZ(yaw);
  }

  Matrix Matrix::Translation(double x,double y,double z) {
    Matrix mat = Matrix::Identity;
    // mat.clear();
    mat.get(0,3) = x;
    mat.get(1,3) = y;
    mat.get(2,3) = z;
    return mat;
  }

  Matrix Matrix::Translation(const QVector3D& v){
    return Translation(v.x(),v.y(),v.z());
  }

  Matrix  Matrix::Mult(const Matrix& a, const Matrix& b) {
    Matrix mat;
    for(int i = 0; i < 4; i++) {      
      for (int j= 0; j < 4; j++) {
	mat.get(i,j) = a.get(i,0)*b.get(0,j) + a.get(i,1)*b.get(1,j) + a.get(i,2)*b.get(2,j) + a.get(i,3)*b.get(3,j);
      }
    }
    return mat;    
  }


  void Matrix::Copy(const Matrix& from, Matrix* to) {
    for(int i = 0; i < 16; i++) {
      to->m[i] = from[i];
    }
  }

  Matrix& Matrix::rotateX(double angle) {
    Matrix mat = Mult(*this,RotationX(angle));
    Copy(mat,this);
    return *this;
  }

  Matrix& Matrix::rotateY(double angle) {
    Matrix mat = Mult(*this,RotationY(angle));
    Copy(mat,this);
    return *this;
  }

  Matrix& Matrix::Matrix::rotateZ(double angle) {
    Matrix mat = Mult(*this,RotationZ(angle));
    Copy(mat,this);
    return *this;
  }

  Matrix& Matrix::translate(QVector3D v) {
    Matrix mat = *this * Translation(v);
    Copy(mat,this);
    return *this;
  }


  
}
