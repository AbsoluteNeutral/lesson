#ifndef DDD_MATRIX33_H_
#define DDD_MATRIX33_H_

#include "matrix.h"
#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"

#pragma warning(disable : 4201) // nameless struct union

namespace ddd {
	class Matrix33
	{
	public:
		union {
			struct {
				float m0, m1, m2,
					  m3, m4, m5,
					  m6, m7, m8;
			};
			struct {
				float m00, m01, m02,
					  m10, m11, m12,
					  m20, m21, m22;
			};
			float m[9];
			float md[3][3];
		};
		
		// ---------- ctor  
		Matrix33() noexcept;
		Matrix33(float _00, float _01, float _02,
				 float _10, float _11, float _12,
				 float _20, float _21, float _22) noexcept;
	
		// ---------- static  
		static const Matrix33 Identity;
		static const Matrix33 Zero;

		// ---------- setters
		void Set(float _00, float _01, float _02, 
				 float _10, float _11, float _12, 
				 float _20, float _21, float _22);
		void SetIdentity();
		void SetZero	();
		void Transpose	();
	
		// ---------- getters
		Matrix33 GetAbsouleMatrix() const;
		float	 GetDeterminant	() const;
		Vector3	 GetCol			(unsigned index_) const;
		Vector3	 GetRow			(unsigned index_) const;
		float	 Trace			() const;
		Matrix33 Transposed		() const;

		// ---------- operator
		operator float*();
		Matrix33& operator*=(float f_);
		Matrix33& operator+=(const Matrix33& matrix_);
		Matrix33& operator-=(const Matrix33& matrix_);
		
		// ---------- friend
		friend Matrix33 operator*(const Matrix33& matrix_, const Matrix33& rhs);
		friend Vector2  operator*(const Matrix33& matrix_, const Vector2& v_);
		friend Vector3  operator*(const Matrix33& matrix_, const Vector3& v_);
		friend std::ostream& operator<<(std::ostream& os, const Matrix33& m);
	}; // Matrix33

	// ---------- extern
	void BuildScale		(Matrix33& matrix_, float x_, float y_);
	void BuildScale		(Matrix33& matrix_, Vector2& v_);
	void BuildScale		(Matrix33& matrix_, Vector3& v_);
	void BuildTranslate	(Matrix33& matrix_, float x_, float y_);
	void BuildTranslate	(Matrix33& matrix_, const Vector2& v_);
	void BuildTranslate	(Matrix33& matrix_, const Vector3& v_);
	void BuildTRS		(Matrix33& matrix_, const Vector3& translation_, const Vector3& scale_, float degree_angleZ_);

	Matrix33 BuildRotation3x3	(const Quaternion& q);
	Matrix33 BuildScale3x3		(float x_, float y_);
	Matrix33 BuildScale3x3		(const Vector2& v_);
	Matrix33 BuildScale3x3		(const Vector3& v_);
	Matrix33 BuildTranslate3x3	(float x_, float y_);
	Matrix33 BuildTranslate3x3	(const Vector2& v_);
	Matrix33 BuildTranslate3x3	(const Vector3& v_);
			 
	void	 BuildSkew			(Matrix33& matrix_, const Vector3& v_);
	Matrix33 BuildSkew3x3		(const Vector3& v_);
	Matrix33 GaussJordanInverse	(const Matrix33& mat);
	Vector2	 TransformPoint		(const Matrix33& matrix_, const Vector2& v_);
	Vector2	 TransformVector	(const Matrix33& matrix_, const Vector2& v_);

} // namespace ddd
#endif // DDD_MATRIX33_H_
