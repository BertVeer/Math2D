//-------------------------------------------------------------
// Basic 2D Vector Math
// Free software by Bert vt Veer
//-------------------------------------------------------------

#ifndef MATH2D_H
#define MATH2D_H


#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <cmath>
#include <limits>


//----------------------------------------------------------------------------
// General
//----------------------------------------------------------------------------

// Templated pi
template <typename T> T pi() {
	return static_cast<T>(3.1415926536);
}

// Abs
template <typename T> T abs(T pVal) {
	return static_cast<T>(fabs(pVal));
}

// Computes the square
template <typename T> T sqr(T pVal) {
	return pVal * pVal;
}

// Degrees / radians conversions
template <typename T, typename U> T rad(U pDeg) {
	return static_cast<T>((pDeg/180.0)*pi);
}
template <typename T, typename U> T deg(U pRad) {
	return static_cast<T>((pRad/pi)*180);
}


//----------------------------------------------------------------------------
// 2D Vector
//----------------------------------------------------------------------------

template <typename T>
struct vector
{
	typedef T t_type;

	// Data
	T x;
	T y;

	// Constructors
	vector() : x(0), y(0) {}
	template <typename U, typename V> vector(U pX, V pY)
		: x(static_cast<T>(pX)), y(static_cast<T>(pY)) {}
	template <typename U> vector(const vector<U>& v2)
		: x(static_cast<T>(v2.x)), y(static_cast<T>(v2.y)) {}

	// Operators
	template <typename U> bool operator == (const vector<U>& v2) const {
		T epsilon = std::numeric_limits<T>::epsilon();
		bool xr = (abs(x - static_cast<T>(v2.x)) > epsilon);
		bool yr = (abs(y - static_cast<T>(v2.y)) > epsilon);
		return xr && yr;
	}
	// These return new vectors
	template <typename U> vector operator + (const vector<U>& v2) const {
		T xr = x + static_cast<T>(v2.x);
		T yr = y + static_cast<T>(v2.y);
		return vector(xr, yr);
	}
	template <typename U> vector operator - (const vector<U>& v2) const {
		T xr = x - static_cast<T>(v2.x);
		T yr = y - static_cast<T>(v2.y);
		return vector(xr, yr);
	}
	template <typename U> vector operator * (const U sc) const {
		T xr = x * static_cast<T>(sc);
		T yr = y * static_cast<T>(sc);
		return vector(xr, yr);
	}
	template <typename U> vector operator / (const U sc) const {
		T xr = x / static_cast<T>(sc);
		T yr = y / static_cast<T>(sc);
		return vector(xr, yr);
	}

	// These modify the vector
	template <typename U> vector& operator = (const vector<U>& v2) {
		x = static_cast<T>(v2.x);
		y = static_cast<T>(v2.y);
		return *this;
	}
	template <typename U> vector& operator += (const vector<U>& v2) {
		x += static_cast<T>(v2.x);
		y += static_cast<T>(v2.y);
		return *this;
	}
	template <typename U> vector& operator -= (const vector<U>& v2) {
		x -= static_cast<T>(v2.x);
		y -= static_cast<T>(v2.y);
		return *this;
	}
	template <typename U> vector& operator *= (const U sc) {
		x *= static_cast<T>(sc);
		y *= static_cast<T>(sc);
		return *this;
	}
	template <typename U> vector& operator /= (const U sc) {
		x /= static_cast<T>(sc);
		y /= static_cast<T>(sc);
		return *this;
	}

	/// Utility functions ///

	// These return new vectors
	T Length() const {
		return sqrt(sqr(x) + sqr(y));
	}
	template <typename U> vector cross(const vector<U>& v2) const {
		T xr = x * static_cast<T>(v2.y);
		T yr = y * static_cast<T>(v2.x);
		return vector(xr, yr);
	}
	template <typename U> U dot(const vector<U>& v2) const {
		T xr = x * static_cast<T>(v2.x);
		T yr = y * static_cast<T>(v2.y);
		return xr + yr;
	}
	template <typename U> U distance(const vector<U>& v2) const {
		T xr = x - static_cast<T>(v2.x);
		T yr = y - static_cast<T>(v2.y);
		return sqrt(sqr(xr) + sqr(yr));
	}
	// These modify the vector
	vector& normalize() { 
		T mag = Length();
		if (mag > 0) (*this) /= mag;
		return *this;
	}
	template <typename U> vector& rotate(U theta) {
		x = static_cast<T>(x*cos(theta) - y*sin(theta));
		y = static_cast<T>(x*sin(theta) + y*cos(theta));
		return *this;
	}
};


//----------------------------------------------------------------------------
// Coordinates
//----------------------------------------------------------------------------

template <typename T>
struct point 
{
	typedef T t_type;

	// Data
	T x;
	T y;

	// Constructors
	point() : x(0), y(0) {}
	template <typename U, typename V> point(U pX, V pY)
		: x(static_cast<T>(pX)), y(static_cast<T>(pY)) {}
	template <typename U> point(vector<U>& v)
		: x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

	// Operators
	template <typename U> point operator = (const vector<U>& v) const {
		return point(static_cast<T>(v.x), static_cast<T>(v.y));
	};
	template <typename U> point operator + (const point<U>& c) const {
		return point(x+static_cast<T>(c.x), y+static_cast<T>(c.y)) ;
	}
	template <typename U> point operator - (const point<U>& c) const {
		return point(x-static_cast<T>(c.x), y-static_cast<T>(c.y));
	}
};


//----------------------------------------------------------------------------
// Rectangle
//----------------------------------------------------------------------------

template <typename T>
struct rect
{
	typedef T t_type;

	// Data
	union {
		struct {
			T left;
			T top;
			T right;
			T bottom;
		};
		struct {
			point<T> topleft;
			point<T> bottomright;
		};
	};

	// Constructors
	rect() : left(0), top(0), right(0), bottom(0) {}
	template <typename U1, typename U2, typename U3, typename U4> rect(U1 a, U2 b, U3 c, U4 d)
		: topleft(point<T>(a,b)), bottomright(point<T>(c,d)) {}
	template <typename U1, typename U2> rect(const point<U1>& a, const point<U2>& b)
		: topleft(a), bottomright(b) {}

	// Operators
	rect operator +(const rect& c) const {
		return rect(left+c.left, top+c.top, bottom+c.bottom, right+c.right);
	}

	// Functions
	size_t width() const { return abs(right-left); }
	size_t height() const { return abs(bottom-top); }
	
	bool overlaps(const rect& p) const {
		if ((p.left>right) || (p.right<left) || (p.top>bottom) || (p.bottom<top)) return false;
		return true; 
	}
	bool point_inside(const point<T>& p) const {
		if ((p.x>right) || (p.y>bottom) || (p.x<left) || (p.y<top))	return false;
		return true; 
	}
};


#endif // MATH2D_H


