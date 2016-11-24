#ifndef VECTOR_H
#define VECTOR_H

// Standard
#include <numeric>
#include <vector>
#include <list>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


using std::vector;
using std::list;
using std::set;
using std::runtime_error;

	typedef vector< double > DoubleVector;
	typedef vector< DoubleVector > DoubleVector2D;

	// DoubleVector Basic Operations
	DoubleVector operator *(const double & scalar, const DoubleVector vec);
	DoubleVector operator *(const DoubleVector vec, const double & scalar);
	DoubleVector operator -=( DoubleVector& v, const double& d );
	DoubleVector operator +=( DoubleVector& v, const double& d );
	void operator +=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator -=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator *=( DoubleVector& vec, const double& scalar );

	// DoubleVector2D Basic operations
	void operator +=( DoubleVector2D& mat1, const DoubleVector2D& mat2 );
	DoubleVector	operator *( const DoubleVector2D & A, const DoubleVector & vector );
	DoubleVector2D	operator *( const double& scalar, const DoubleVector2D & matrix );
	DoubleVector2D	operator *( const DoubleVector2D & A, const DoubleVector2D & B );

	// Vectorial Operations
	double innerProduct( const DoubleVector& vector1, const DoubleVector& vector2 );
	double norm( DoubleVector& vec );
	void normalize( DoubleVector& vec );

	DoubleVector nullVector(int dimension);


	template <class type> std::ostream & operator<<( std::ostream & out , vector<type> & v){
		for( int i = 0 ; i < v.size() ; ++i){
			out << v[i];
		}

		return out;
	}

	template <class type> void operator>>( std::istream & in , vector<type> & v){
		for( int i = 0 ; i < v.size() ; ++i){
			in >> v[i];
		}
	}

	template <class type> std::ofstream & operator<<( std::ofstream & out , vector<type> & v){
		for( int i = 0 ; i < v.size() ; ++i){
			out << v[i];
		}

		return out;
	}

	template <class type> void operator>>( std::ifstream & in , vector<type> & v){
		for( int i = 0 ; i < v.size() ; ++i){
			in >> v[i];
		}
	}
/*
	template <class type> std::ostream & operator<<( std::ostream & out , type & v){

	    typename type::iterator p = v.begin();
	    typename type::iterator end = v.end();
	    while( p!= end ) {
	        //Avoiding the Global Namespace << overloads - using std:: instead
	        std::operator << (out,*p);      
	        std::operator << (out, "    ");

        	++p;
    	}
    	return out;

	}*/

#endif
