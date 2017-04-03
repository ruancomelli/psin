#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <vector>

#define VECTOR_3D_EQUAL_TOLERANCE 1e-12

enum Axis{
	X, Y, Z, N_AXIS = 3
};
typedef std::vector< Axis > AxisArray;

class Vector3D{
public:
	Vector3D( void );
	explicit Vector3D( const double& x, const double& y=0.0, const double& z=0.0 );

	double x() const;
	double y() const;
	double z() const;
	double& x();
	double& y();
	double& z();
	double getComponent( const int pos ) const;
	double length() const;
	double squaredLength() const;
	void normalize();
	Vector3D normalized() const;
	double dist( const Vector3D& v ) const;
	Vector3D operator +=( const Vector3D& v );
	Vector3D operator -=( const Vector3D& v );
	Vector3D operator *=( const double scalar );
	Vector3D operator /=( const double scalar );
	void print();

	virtual ~Vector3D(){}

protected:
	double components[ N_AXIS ];
}; //class Vector3D;

Vector3D cross( const Vector3D& v0, const Vector3D& v1 );
double dot( const Vector3D& v0, const Vector3D& v1 );
double triple( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 );
Vector3D operator -( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator +( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator *( const double scalar, const Vector3D& v );
Vector3D operator *( const Vector3D& v, const double scalar );
Vector3D operator /( const Vector3D& v, const double scalar );
Vector3D operator - (const Vector3D& v);
bool operator == ( const Vector3D & v1 , const Vector3D & v2 );//tol=1e-12
bool operator != ( const Vector3D & v1 , const Vector3D & v2 );//tol=1e-12

inline Vector3D nullVector3D(void){ return Vector3D(); }


#endif