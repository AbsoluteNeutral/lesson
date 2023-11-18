#ifndef DDD_VECTOR2_H_
#define DDD_VECTOR2_H_

#include <ostream>
#include "Reals.h"

#define WITH_VECTOR3_

namespace ddd {
#ifdef WITH_VECTOR3_
	class Vector3;
#endif
	class Vector2
	{
	public:
		float x, y;
	
		// ---------- constructor
		Vector2	()					noexcept;
		Vector2 (float x_, float y_)noexcept;
	
		// ---------- getters
		float	Dot						(const Vector2& v_) const;  // dot product
		Vector2	GetAbsVector			()					const;
		int		GetMinAxis				()					const;
		int		GetMaxAxis				()					const;
		Vector2	GetUnitOrthogonalVector	()					const;
		bool	IsUnit	 	() const;
		bool	IsZero	 	() const;
		float	LengthSq 	() const;  
		float	Length	 	() const;
		Vector2	Normalized	() const;
		void 	Print	 	() const;
		
		// ---------- setters
		float	Normalize	();
		void	Set			(float x_, float y_);
		void	SetZero		();
	
		// ---------- operator
		Vector2& 	 operator+= (const Vector2 &v);
		Vector2& 	 operator-= (const Vector2 &v);
		Vector2& 	 operator*= (float f);
		Vector2& 	 operator/= (float f);
		bool     	 operator== (const Vector2 &r) const;
		bool     	 operator!= (const Vector2 &r) const;
		float& 	 	 operator[] (int index);
		const float& operator[] (int index)	const;

#ifdef WITH_VECTOR3_
		explicit Vector2	(const Vector3& r_)	noexcept;
		Vector2& operator=	(const Vector3& v);
#endif

		// ---------- static
		static const Vector2 Zero;
		static const Vector2 VectorX;
		static const Vector2 VectorY;
		static Vector2 Min(const Vector2& v1, const Vector2& v2);
		static Vector2 Max(const Vector2& v1, const Vector2& v2);
		
		// ---------- friend
		friend Vector2 operator- (const Vector2 &l);
		friend Vector2 operator- (const Vector2 &l, const Vector2 &r);
		friend Vector2 operator- (const Vector2 &l, float f);
		friend Vector2 operator+ (const Vector2 &l, const Vector2 &r);
		friend Vector2 operator+ (const Vector2 &l, float f);
		friend Vector2 operator* (const Vector2 &l, const Vector2 &r);
		friend Vector2 operator* (const Vector2 &v, float f);
		friend Vector2 operator/ (const Vector2 &v, float  f);
		friend Vector2 operator- (float f, const Vector2 &r);
		friend Vector2 operator+ (float f, const Vector2 &r);
		friend Vector2 operator* (float f, const Vector2 &v);
		friend Vector2 getDirection(const Vector2& pointA, const Vector2& pointB);
		friend std::ostream& operator<<(std::ostream& os, const Vector2& m);

	}; // Vector2
	
	// ---------- extern function
	Vector2	ABS				(const Vector2& v_);
	bool	ApproxEqual		(const Vector2& l_, const Vector2& r_, float epsilon);
	Vector2 Direction		(float y_dir, float x_dir);
	float	DistanceSq		(const Vector2& l_, const Vector2& r_);
	float	Distance		(const Vector2& l_, const Vector2& r_);
	float	Dot				(const Vector2& l_, const Vector2& r_);
	float 	Length			(const Vector2& v_);
	float 	LengthSq		(const Vector2& v_);
	Vector2	Lerp			(const Vector2& start_, const Vector2& end_, float time_);
	Vector2	nLerp			(const Vector2& start_, const Vector2& end_, float time_);
	Vector2	LinearRand		(const Vector2& l_, const Vector2& r_);
	float 	Magnitude		(const Vector2& v_);
	float 	MagnitudeSq		(const Vector2& v_);
	float 	Normalize		(Vector2& v_);
	Vector2	Normalized		(const Vector2& v_);
} // namespace ddd

#endif // DDD_VECTOR2_H_
