
#include "Vector2.h"

#ifdef WITH_VECTOR3_
	#include "Vector3.h"
#endif

namespace ddd {
// ---------- static
	const Vector2 Vector2::Zero{};
	const Vector2 Vector2::VectorX = Vector2{ float(1.0), float(0.0) };
	const Vector2 Vector2::VectorY = Vector2{ float(0.0), float(1.0) };
	Vector2 Vector2::Min(const Vector2& v1, const Vector2& v2) {
		return Vector2{
			MIN2(v1.x, v2.x),
			MIN2(v1.y, v2.y)
		};
	}
	Vector2 Vector2::Max(const Vector2& v1, const Vector2& v2) {
		return Vector2{
			MAX2(v1.x, v2.x),
			MAX2(v1.y, v2.y)
		};
	}

// ---------- constructor
	Vector2::Vector2()  noexcept
		:x(0), y(0)
	{}
	Vector2::Vector2(float x_, float y_ )  noexcept
		:x(x_), y(y_) 
	{}
	
// ---------- getters
	float Vector2::Dot(const Vector2 &v_) const { 
		return x * v_.x + y * v_.y; 
	}
	Vector2 Vector2::GetAbsVector()	const {
		return Vector2{ 
			x < float(0.0) ? -x : x,
			y < float(0.0) ? -y : y
		};
	}
	int	Vector2::GetMinAxis() const {
		return (x < y) ? 0 : 1;
	}	
	int	Vector2::GetMaxAxis() const {
		return (x < y) ? 1 : 0;
	}
	Vector2 Vector2::GetUnitOrthogonalVector() const {
		float len = Length();
		len = len <= MACHINE_EPSILON ? float(0.0) : (float(1.0) / len);
		return Vector2(-y * len, x * len);
	}
	bool Vector2::IsUnit() const {
		return ApproxEqual(LengthSq(), 1.0f);
	}
	bool Vector2::IsZero() const {
		return ApproxEqual(LengthSq(), 0.0f);
	}
	float Vector2::LengthSq() const { 
		return x * x + y * y; 
	}
	float Vector2::Length()	const { 
		return sqrtf(LengthSq()); 
	}
	Vector2 Vector2::Normalized() const {
		float len = Length();
		len = len <= MACHINE_EPSILON ? float(0.0): (float(1.0) / len);
		return Vector2{ x * len, y * len };
	}
	void Vector2::Print() const{
		printf("{ %.6f %.6f }\n", x, y);
	}
			
// ---------- setters
	float Vector2::Normalize() {
		float len = Length();
		float overlen = len <= MACHINE_EPSILON ? float(0.0) : (float(1.0) / len);
		x *= overlen;
		y *= overlen;
		return len;
	}
	void Vector2::Set(float x_, float y_) {
		x = x_; y = y_;
	}
	void Vector2::SetZero() { 
		x = y = float(0.0); 
	}
	
// ---------- operator
	Vector2& Vector2::operator+=(const Vector2& v_)		{ x += v_.x;  y += v_.y;  return *this; }
	Vector2& Vector2::operator-=(const Vector2& v_)		{ x -= v_.x;  y -= v_.y;  return *this; }
	Vector2& Vector2::operator*=(float f)				{ x *= f;    y *= f;	return *this; }
	Vector2& Vector2::operator/=(float f)				{ x /= f;    y /= f;	return *this; }
	bool Vector2::operator==(const Vector2& v_) const	{ return ((x == v_.x) && (y == v_.y)); }
	bool Vector2::operator!=(const Vector2& v_) const	{ return !operator==(v_); }
	float& Vector2::operator[] (int index)				{ return (&x)[index]; }
	const float& Vector2::operator[] (int index) const	{ return (&x)[index]; }
	
#ifdef WITH_VECTOR3_
  	Vector2::Vector2(const Vector3& r_) noexcept
		:x(r_.x), y(r_.y)
	{}
	Vector2& Vector2::operator=(const Vector3& v){ 
		x = v.x;  
		y = v.y;   
		return *this; 
	}
#endif

// ---------- friend
	Vector2 operator-(const Vector2& l)						{ return Vector2{ -l.x,		-l.y		}; } // negate
	Vector2 operator-(const Vector2& l, const Vector2& r)	{ return Vector2{ l.x - r.x,l.y - r.y	}; } // minus
	Vector2 operator-(const Vector2& l, float f)			{ return Vector2{ l.x - f,	l.y - f		}; } // minus
	Vector2 operator+(const Vector2& l, const Vector2& r)	{ return Vector2{ l.x + r.x,l.y + r.y	}; } // plus
	Vector2 operator+(const Vector2& l, float f)			{ return Vector2{ l.x + f,	l.y + f		}; } // plus
	Vector2 operator*(const Vector2& l, const Vector2& r)	{ return Vector2{ l.x* r.x,	l.y * r.y	}; } // multiply
	Vector2 operator*(const Vector2& v, float f)			{ return Vector2{ v.x* f,	v.y * f		}; } // multiply
	Vector2 operator/(const Vector2& v, float f)			{ return Vector2{ v.x / f,  v.y / f		}; } // division

	Vector2 operator-(float f, const Vector2& r) 			{ return Vector2{ f - r.x, f - r.y		}; } // minus
	Vector2 operator+(float f, const Vector2& r) 			{ return Vector2{ f + r.x, f + r.y 		}; } // plus
	Vector2 operator*(float f, const Vector2& r) 			{ return Vector2{ f * r.x, f * r.y 		}; } // multiply	

	// Returns the direction vector from pointA to point B
	Vector2 getDirection(const Vector2& pointA, const Vector2& pointB) {
		float oppOverAdj = (pointB.y - pointA.y) / (pointB.x - pointA.x);
		float angle = atanf(oppOverAdj);
	
		// Calculate direction vector
		Vector2 dir = { std::cos(angle), std::sin(angle) };
	
		// 90 deg = 1.5708 rad
		if ((angle <= 0.0f && angle > -1.5708f && pointB.x < pointA.x)
		|| (angle >= 0.0f && angle <  1.5708f && pointB.y < pointA.y))
		{
			dir.x *= -1;
			dir.y *= -1;
		}
		return dir;
	}
	
	std::ostream& operator<<(std::ostream& os, const Vector2& v) {
		printf("{ %.6f %.6f }\n", v.x, v.y);
		// os << " {" << v.x << "," << v.y << "} " << std::endl;
		return os;
	}

// ---------- extern function
	Vector2 ABS(const Vector2& v_) {
		return Vector2{ 
			v_.x < float(0.0) ? -v_.x : v_.x, 
			v_.y < float(0.0) ? -v_.y : v_.y 
		};
	}
	bool ApproxEqual(const Vector2& l_, const Vector2& r_, float epsilon) {
		return ApproxEqual(l_.x, r_.x, epsilon)
			&& ApproxEqual(l_.y, r_.y, epsilon);
	}
	
	Vector2 Direction(float y_dir, float x_dir) {
		return Normalized(Vector2{ std::cos(y_dir), std::sin(x_dir) });
	}
	
	float DistanceSq(const Vector2& l_, const Vector2& r_) {
		float a = l_.x - r_.x;
		float b = l_.y - r_.y;
		return a * a + b * b;
	}
	float Distance(const Vector2& l_, const Vector2& r_) {
		return sqrtf(DistanceSq(l_, r_));
	}
	float Dot		(const Vector2& l_, const Vector2& r_) 	 { return l_.Dot(r_);		}
	float Length	(const Vector2& v_)						 { return v_.Length();		}
	float LengthSq	(const Vector2& v_)						 { return v_.LengthSq();	}

	Vector2 Lerp(const Vector2& start_, const Vector2& end_, float time_) {
		/* 
		Imprecise method, which does not guarantee v = v1 when t = 1, 
		due to floating-point arithmetic error.
		This form may be used when the hardware has a native fused multiply-add instruction.
		*/
		// return start_ + float(time_) * (end_ - start_);

		// Precise method, which guarantees v = v1 when t = 1.
		Vector2 v0 = (float(1) - float(time_)) * start_;
		Vector2 v1 = float(time_) * end_;
		return v0 + v1;
	}
	Vector2 nLerp(const Vector2& start_, const Vector2& end_, float time_) {
		return Lerp(start_, end_, time_).Normalized();
	}

	Vector2 LinearRand(const Vector2& l_, const Vector2& r_) {
		return Vector2(sfrand(l_.x, r_.x), sfrand(l_.y, r_.y));
	}

	float	Magnitude	(const Vector2& v_)	{ return Length(v_);		}
	float	MagnitudeSq	(const Vector2& v_)	{ return LengthSq(v_);		}
	float	Normalize	(Vector2& v)		{ return v.Normalize();		}
	Vector2	Normalized	(const Vector2& v)	{ return v.Normalized();	}

} // namespace ddd
