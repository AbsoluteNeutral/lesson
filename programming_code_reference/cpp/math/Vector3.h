#ifndef DDD_VECTOR3_H_
#define DDD_VECTOR3_H_

#include <ostream>
#include <vector>
#include "Reals.h"

#define WITH_VECTOR2_
#define WITH_VECTOR4_

namespace ddd {
#ifdef WITH_VECTOR2_
	class Vector2;
#endif
#ifdef WITH_VECTOR4_
	class Vector4;
#endif
	class Vector3
	{
	public:
		float x, y, z;
	
		// ---------- constructor
		Vector3	()									noexcept;
		Vector3	(float x_, float y_)				noexcept;
		Vector3	(float x_, float y_, float z_) 		noexcept;
	
		// ---------- getters
		Vector3		Cross					(const Vector3& rhs)const;
		float		Dot						(const Vector3& v_)	const;
		Vector3		GetAbsVector			()					const;
		int			GetMinAxis				()					const;
		int			GetMaxAxis				()					const;
		Vector3		GetUnitOrthogonalVector	()					const;
		float		LengthSq				()					const;
		float		Length					()					const;
		bool		IsNan					()					const;
		bool		IsUnit					()					const;
		bool		IsZero					()					const;
		Vector3		Normalized				()					const;

		// ---------- setters
		float	Normalize	();
		void	Set			(float x_, float y_, float z_);
		void	SetZero		();
		void	Reset();
		
		// ---------- operator
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float f);
		Vector3& operator/=(float f);
		bool	 operator==(const Vector3& v) const;
		float& 	 operator[](int index);
		float 	 operator[](int index) const;
	
		// ---------- static	
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 VectorX;
		static const Vector3 VectorY;
		static const Vector3 VectorZ;
		static Vector3 SmoothDamp(const Vector3& start, const Vector3& end, Vector3& velocity, float smoothTime, float maxSpeed, float deltaTime);
		
		// ---------- friend	
		friend Vector3 operator-(const Vector3& l);
		friend Vector3 operator-(const Vector3& l, const Vector3& r);
		friend Vector3 operator-(const Vector3& l, float f);
		friend Vector3 operator+(const Vector3& l, const Vector3& r);
		friend Vector3 operator+(const Vector3& l, float f);
		friend Vector3 operator*(const Vector3& l, const Vector3& r);
		friend Vector3 operator*(const Vector3& l, float f);
		friend Vector3 operator/(const Vector3& l, float f);
		friend Vector3 operator^(const Vector3& l, const Vector3& r); // cross product

		friend Vector3 operator-(float f, const Vector3& r);
		friend Vector3 operator+(float f, const Vector3& r);
		friend Vector3 operator*(float f, const Vector3& r);
		friend Vector3 operator/(float f, const Vector3& r);
		friend std::ostream& operator<<(std::ostream& os, const Vector3& m);
		
#ifdef WITH_VECTOR2_
		explicit Vector3(const Vector2& v_, float z_ = 0) noexcept;
		Vector3& operator= (const Vector2& v);
		Vector3& operator+=(const Vector2& v);
		friend Vector3 operator-(const Vector3& l, const Vector2& r);
		friend Vector3 operator+(const Vector3& l, const Vector2& r);
#endif
#ifdef WITH_VECTOR4_
		explicit Vector3(const Vector4& v_)	noexcept;
		Vector3& operator= (const Vector4& v);
#endif
	}; // Vector3

// ---------- extern function
#ifdef WITH_VECTOR2_
	float	DistanceSq		(const Vector2& v0_, const Vector3& v1_);	// distanceSq of Vector 2 and Vector 3
	float	DistanceSq		(const Vector3& v0_, const Vector2& v1_);	// distanceSq of Vector 3 and Vector 2
#endif

	Vector3	ABS				(const Vector3& v_);
	bool	ApproxEqual		(const Vector3& v0_, const Vector3& v1_, float epsilon);
	float	Angle			(const Vector3& v0_, const Vector3& v1_);
	Vector3	ClampMagnitude	(Vector3 vector, float maxLength);
	void	CopyVector3Array(Vector3* dest_, const Vector3* source_, size_t sz_);
	void	CopyVector3Array(std::vector<Vector3>& dest_, const Vector3* source_, size_t sz_);
	Vector3	Cross			(const Vector3& from_, const Vector3& to_);
	float	Distance		(const Vector3& v0_, const Vector3& v1_);	// distance of Vector 3 and Vector 3
	float	DistanceSq		(const Vector3& v0_, const Vector3& v1_);	// distanceSq of Vector 3 and Vector 3
	float	Dot				(const Vector3& v0_, const Vector3& v1_);
	Vector3	FromSpherical	(float r, float theta, float phi);
	bool	IsParallel		(const Vector3& v0_, const Vector3& v1_);	// Return true if two vectors are parallel
	bool	IsOrthogonal	(const Vector3& v0_, const Vector3& v1_);	// Return true if two vectors are Orthogonal
	float	Length			(const Vector3& v_);
	float	LengthSq		(const Vector3& v_);
	Vector3	Lerp			(const Vector3& start_, const Vector3& end_, float time_);
	Vector3	nLerp			(const Vector3& start_, const Vector3& end_, float time_);
	Vector3	LerpDelta		(const Vector3& start_, Vector3& deltaOf_end_start_, float time_);
	Vector3	nLerpDelta		(const Vector3& start_, Vector3& deltaOf_end_start_, float time_);
	Vector3	LinearRand		(const Vector3& v0_, const Vector3& v1_);
	float	Magnitude		(const Vector3& v_);
	float	MagnitudeSq		(const Vector3& v_);
	Vector3	MoveTowards		(const Vector3& current, const Vector3& target, float maxDistanceDelta);
	Vector3	Min				(const Vector3& v0_, const Vector3& v1_);
	Vector3	Max				(const Vector3& v0_, const Vector3& v1_);
	float	Normalize		(Vector3& v_);
	Vector3	Normalized		(const Vector3& v_);
	Vector3	Project			(const Vector3& v0_, const Vector3& v1_);
	Vector3	ProjectOnPlane	(const Vector3& vector, const Vector3& planeNormal);
	Vector3	Reflect			(const Vector3& vector, const Vector3& planeNormal);
	Vector3	Reject			(const Vector3& a, const Vector3& b);
	Vector3	Slerp			(Vector3 v0_, Vector3 v1_, float time_);
	Vector3	SlerpClamp		(Vector3 v0_, Vector3 v1_, float time_);
	void	ToSpherical		(const Vector3& vector, float &rad, float &theta, float &phi);
	Vector3	Orthogonal		(const Vector3& v);

	
	//Computes scalar triple product
	float	ScalarTripleProduct		(const Vector3& a, const Vector3& b, const Vector3& c);	
	//Barycentric Of Line, Triangle, Tetrahedron
	bool	BarycentricCoordinates	(const Vector3& point, const Vector3& a, const Vector3& b, float& u, float& v, float epsilon);
	bool	BarycentricCoordinates	(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c, float& u, float& v, float& w, float epsilon);
	bool	BarycentricCoordinates	(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, float& u, float& v, float& w, float& t, float epsilon = 0.0f);

	Vector3	ComputeClosestPointOnSegment	(const Vector3& segPointA,	const Vector3& segPointB,	const Vector3& pointC);
	float	ComputePlaneSegmentIntersection (const Vector3& segA,		const Vector3& segB,		float planeD, const Vector3& planeNormal);
	float	ComputePointToLineDistance		(const Vector3& linePointA, const Vector3& linePointB,	const Vector3& point);

	//Generate Basis
	void	GenerateOrthonormalBasis	(const Vector3& w, Vector3* u, Vector3* v);

}	//namespace ddd

#endif //DDD_VECTOR3_H_
