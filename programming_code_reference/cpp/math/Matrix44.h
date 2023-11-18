
#ifndef DDD_MATRIX44_H_
#define DDD_MATRIX44_H_

#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

#pragma warning(disable : 4201) //nameless struct union

namespace ddd {
	class Matrix44
	{
	public:
		union {
			struct
			{
				float m00, m01, m02, m03,
					  m10, m11, m12, m13,
					  m20, m21, m22, m23,
					  m30, m31, m32, m33;
			};
			float m[16];
			float md[4][4];
		};
		
		// ---------- ctor
		Matrix44() noexcept;
		Matrix44(float _00, float _01, float _02, float _03,
				 float _10, float _11, float _12, float _13,
				 float _20, float _21, float _22, float _23,
				 float _30, float _31, float _32, float _33) noexcept;
	
		// ---------- static
		static const Matrix44 Identity;
		static const Matrix44 Zero;

		// ---------- setters
		void SetIdentity	();
		void SetZero		();
		void Transpose		();

		// ---------- getters
		float*		GetPtr		();
		Vector4		GetCol		(unsigned index_) const;
		Vector4		GetRow		(unsigned index_) const;
		float		Trace		() const;
		Matrix44	Transposed	() const;

		// ---------- operator
		operator float*();
		Matrix44& operator*=(float f_);
		Matrix44& operator-=(const Matrix44& matrix_);
		Matrix44& operator+=(const Matrix44& matrix_);

		// ---------- friend
		friend Matrix44	operator-	(const Matrix44& lhs, const Matrix44& rhs);
		friend Matrix44	operator+	(const Matrix44& lhs, const Matrix44& rhs);
		friend Matrix44	operator*	(const Matrix44& lhs, const Matrix44& rhs);
		friend Vector2	operator*	(const Matrix44& lhs, const Vector2& pt_);
		friend Vector3	operator*	(const Matrix44& lhs, const Vector3& pt_);
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix44& matrix_);
	};

	// ---------- extern
	Matrix44 BuildTranslate4x4	(float x_, float y_, float z_);
	Matrix44 BuildTranslate4x4	(const Vector3& v_);
	Matrix44 BuildRotation4x4	(float degree_, const Vector3& axis_);
	Matrix44 BuildRotation4x4	(const Quaternion& q_);
	Matrix44 BuildRotation4x4	(const Quaternion& q_, const Vector3& translation_);
	Matrix44 BuildScale4x4		(float x_);
	Matrix44 BuildScale4x4		(float x_, float y_, float z_);
	Matrix44 BuildScale4x4		(const Vector3& scale_);
			 
	void	 BuildTRS			(Matrix44& m, const Vector3& translation_, const Vector3& scale_, float angleZ_);
	void	 BuildTRS			(Matrix44& m, const Vector3& translation_, const Vector3& scale_, const Vector3& angle_);
	void	 BuildTRS			(Matrix44& m, const Vector3& translation_, const Vector3& scale_, const Vector3& axis_, float angle_);
	Matrix44 BuildTRS4x4		(const Vector3& translation_, const Quaternion& quaternion_, const Vector3& scale_);
	Matrix44 BuildSkew4x4		(const Vector3& v_);
	// ---------- ETC
	Matrix44 LookAtRH			(const Vector3& eye, const Vector3& target, const Vector3& up);
	Matrix44 LookAtRHDir		(const Vector3& eye, const Vector3& direction, const Vector3& up);
	Matrix44 LookAtLH			(const Vector3& eye, const Vector3& target, const Vector3& up);
	Matrix44 OrthRH				(float left, float right, float bottom, float top, float near_, float far_);
	Matrix44 Orth				(float left, float right, float bottom, float top);
	Matrix44 PerspectiveRH		(float fovRAD_, float aspect_, float near_, float far_);
	Matrix44 FrustumRH			(float left_, float right_, float bottom_, float top_, float near_, float far_);
	Matrix44 ViewPortTransform	(int width_, int height_);
	
	float Determinant			(const Matrix44& matrix_, int dimension_);
	
	Matrix44	GaussJordanInverse	(const Matrix44& matrix_);
	Vector3		GetPosition			(const Matrix44& matrix_);
	Vector3		GetScale			(const Matrix44& matrix_);
	Quaternion	GetRotation			(const Matrix44& matrix_);
	Vector3		TransformPoint		(const Matrix44& matrix_, const Vector3& point_);
	Vector3		TransformVector		(const Matrix44& matrix_, const Vector3& vector_);
	
#pragma region Hardcoded Inverse
	Matrix44	Inverse				(const Matrix44& mat);
#pragma endregion

}//namespace ddd

#endif // DDD_MATRIX44_H_
