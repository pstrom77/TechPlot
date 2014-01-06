#ifndef __TP_MATRIX_H__
#define __TP_MATRIX_H__

#include <QtCore>
#include <QVector3D>
#include <QVector4D>
#include <iostream>

namespace tp {

  static double PI = 3.1415926535;
  static double DEGTORAD = PI/180.0;
  static double RADTODEG = 180.00/PI;

  class Matrix {
  protected:
      double m[16];

  public:
    Matrix();
    Matrix(double m00, double m01, double m02, double m03,
	   double m10, double m11, double m12, double m13,
	   double m20, double m21, double m22, double m23,
	   double m30, double m31, double m32, double m33);

    /* Matrix(const Matrix& in){ */
    /*   Copy(in,this); */
    /* } */
    void clear() { for(int i = 0; i < 16;i++) m[i] = 0; }

    static Matrix RotationMatrix(double roll, double pitch, double yaw);
    static Matrix RotationX(double angle);
    static Matrix RotationY(double angle);
    static Matrix RotationZ(double angle);
    static Matrix Scale(const QVector3D& v);
    static Matrix Scale(double x, double y, double z);
    static Matrix Translation(double x,double y, double z);
    static Matrix Translation(const QVector3D& v);
    static void   Copy(const Matrix& from, Matrix* to); 
    static Matrix Mult(const Matrix& a, const Matrix&b);
    static Matrix Identity;

    QVector4D operator*(QVector4D v) { 
      return QVector4D(get(0,0)*v.x() + get(0,1)*v.y() + get(0,2)*v.z() + get(0,3),
		       get(1,0)*v.x() + get(1,1)*v.y() + get(1,2)*v.z() + get(1,3),
		       get(2,0)*v.x() + get(2,1)*v.y() + get(2,2)*v.z() + get(2,3), 
		       get(3,0)*v.x() + get(3,1)*v.y() + get(3,2)*v.z() + get(3,3)); 
    }

    Matrix operator*(Matrix v) { 
      return Mult(*this,v);
    }

    double& operator[](int i) { return m[i]; } 
    const double& operator[](int i) const { return m[i]; } 

    double& get(int row, int col) { return m[row+col*4]; }
    const double& get(int row, int col) const { return m[row+col*4]; }

    Matrix operator+(Matrix v) { 
      Matrix mat;
      for (int i = 0; i < 16; i++) mat[i] = m[i]+v[i];
      return mat;
    }

    Matrix operator-(Matrix v) { 
      Matrix mat;
      for (int i = 0; i < 16; i++) mat[i] = m[i]-v[i];
      return mat;
    }
    
    /* Matrix& operator=(const Matrix& in) { */
    /*   Copy(in,this); */
    /*   return *this; */
    /* } */


    void setTranslate(double x, double y, double z) { 
      get(0,3) = x;
      get(1,3) = y;
      get(2,3) = z;
    }


    
    Matrix& rotateX(double angle);
    Matrix& rotateY(double angle);
    Matrix& rotateZ(double angle);
    Matrix& translate(const QVector3D& v);
    Matrix& scale(const QVector3D& v);
    
    double roll() const;
    double pitch() const;
    double yaw() const;

    void setRotation(double roll, double pitch, double yaw) { 
      Matrix mat= RotationX(roll)*RotationY(pitch)*RotationZ(yaw); 
      for(int row = 0; row < 3; row++) {
	for (int col = 0; col < 3; col++) {
	  get(row,col) = mat.get(row,col);
	}
      }
    }

  };
  

  inline std::ostream& operator<<(std::ostream& stream, const Matrix& m) {
    stream << m.get(0,0) << " " << m.get(0,1) << " " << m.get(0,2)  << " " << m.get(0,3) << "\n";
    stream << m.get(1,0) << " " << m.get(1,1) << " " << m.get(1,2)  << " " << m.get(1,3) << "\n";
    stream << m.get(2,0) << " " << m.get(2,1) << " " << m.get(2,2)  << " " << m.get(2,3) << "\n";
    stream << m.get(3,0) << " " << m.get(3,1) << " " << m.get(3,2)  << " " << m.get(3,3) << "\n";
    return stream;
  }


}

#endif
