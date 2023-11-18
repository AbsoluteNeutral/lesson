#ifndef DDD_VECTOR4_H_
#define DDD_VECTOR4_H_

#include <ostream>
#include <vector>
#include "Reals.h"

#define WITH_VECTOR2_
#define WITH_VECTOR3_

namespace ddd {
#ifdef WITH_VECTOR2_
	class Vector2;
#endif
#ifdef WITH_VECTOR3_
	class Vector3;
#endif

	class Vector4
	{
	public:
		float x, y, z, w;
		Vector4	()										noexcept;
		Vector4	(float x_, float y_, float z_, float w_)noexcept;
	
		// ---------- static
		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 VectorX;
		static const Vector4 VectorY;
		static const Vector4 VectorZ;
		static const Vector4 VectorW;
		static Vector4 Min(const Vector4& v1, const Vector4& v2);
		static Vector4 Max(const Vector4& v1, const Vector4& v2);

		// ---------- getters
		float	Dot(const Vector4& v_)	const;
		bool	IsUnit()			const;
		bool	IsZero()			const;
		float	LengthSq()			const;
		float	Length()			const;
		Vector4	Normalized()		const;
		
		// ---------- setters
		float	Normalize();
		void	SetZero();
		void	SetOne();
		
		// ---------- operator
		Vector4& operator+=(const Vector4& v_);
		Vector4& operator-=(const Vector4& v_);
		Vector4& operator*=(const Vector4& v_);
		Vector4& operator*=(float f);
		Vector4& operator/=(float f);
		bool	 operator==(const Vector4& v_) const;
		float& operator[]  (int index);
		float  operator[]  (int index) const;
		
		// ---------- friend
		friend Vector4 operator- (const Vector4 &l);
		friend Vector4 operator- (const Vector4 &l, const Vector4 &r);
		friend Vector4 operator- (const Vector4 &l, float f);
		friend Vector4 operator+ (const Vector4 &l, const Vector4 &r);
		friend Vector4 operator+ (const Vector4 &l, float f);
		friend Vector4 operator* (const Vector4 &l, const Vector4 &r);
		friend Vector4 operator* (const Vector4 &l, float f);
		friend Vector4 operator/ (const Vector4 &l, float f);

		friend Vector4 operator- (float f, const Vector4 &r);
		friend Vector4 operator+ (float f, const Vector4 &r);
		friend Vector4 operator* (float f, const Vector4 &l);
		friend std::ostream& operator<<(std::ostream& os, const Vector4& m);
		
#ifdef WITH_VECTOR2_
	explicit Vector4	(const Vector2 &v) noexcept;
	Vector4& operator=	(const Vector2& v_);
#endif
#ifdef WITH_VECTOR3_
	Vector4				(const Vector3& vector3, float w_ = 0)	noexcept;
	Vector4& operator=	(const Vector3& v_);
#endif
	}; // Vector4
	
	// ---------- extern function
	Vector4	ABS				(const Vector4& v_);
	bool	ApproxEqual		(const Vector4& v0_, const Vector4& v1_, float epsilon);
	float	DistanceSq		(const Vector4& v0_, const Vector4& v1_);
	float	Dot				(const Vector4& v0_, const Vector4& v1_);
	float 	Length			(const Vector4& v_);
	float 	LengthSq		(const Vector4& v_);
	Vector4	Lerp			(const Vector4& start_, const Vector4& end_, float time_);
	Vector4	nLerp			(const Vector4& start_, const Vector4& end_, float time_);
	Vector4	LinearRand		(const Vector4& v0_, const Vector4& v1_);
	float 	Magnitude		(const Vector4& v_);
	float 	MagnitudeSq		(const Vector4& v_);
	float 	Normalize		(Vector4& v_);
	Vector4	Normalized		(const Vector4& v_);

} // namespace ddd

#endif // DDD_VECTOR4_H_
