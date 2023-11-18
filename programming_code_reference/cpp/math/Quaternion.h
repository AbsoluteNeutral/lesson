#ifndef DDD_QUATERNION_H_
#define DDD_QUATERNION_H_

#include "Vector3.h"

namespace ddd {
	class Matrix33;
	class Matrix44;

	class Quaternion
	{
	public:
		float x, y, z, w;
	
		// ---------- constructor
		Quaternion() noexcept;
		Quaternion(const Vector3& topurequaternion_) noexcept;
		Quaternion(float x_, float y_, float z_, float w_) noexcept;
		Quaternion(const Vector3& axis_, float degree_) noexcept;
	
		// ---------- setters
		void	AddScaledVector		(const Vector3& vector_, float f_);
		void	Conjugate			();
		void	Integrate			(const Vector3& vector_, float f_);
		void	Invert				();
		float	Normalize			();
		void	Set					(float x_, float y_, float z_, float w_);
		void	SetFromEulerAngles	(float RADIAN_x, float RADIAN_y, float RADIAN_z);
		void	SetFromEulerAngles	(const Vector3& degree_);
		void	Reset				();

		// ---------- getters 
		float		Dot					(const Quaternion& rhs) const;
		Vector3		GetAxis				()						const;
		Quaternion	GetRotationAngleAxis(float& angle, Vector3& axis) const;
		Quaternion	GetConjugated		()						const;
		Quaternion  GetExponent			()						const;
		Quaternion  GetInverted			()						const;
		Matrix33	GetMatrix33			()						const;
		Matrix44	GetMatrix44			()						const;
		Quaternion	Normalized			()						const;
		Vector3		GetRotatedVector	(const Vector3& v)		const;
		Vector3		GetVector3			()						const;
		float		LengthSq			()						const;
		float		Length				()						const;
		Vector3		ToEularDegree		()						const;
		bool		IsNan				()						const;
		bool		IsNearNan			()						const;
		
		// ---------- static
		static Quaternion Identity;
	
		// ---------- operator
		bool operator==			(const Quaternion& q2_)	const;
		Quaternion& operator-=	(const Quaternion& q2_);
		Quaternion& operator+=	(const Quaternion& q2_);
		Quaternion& operator*=	(float f_);
		Quaternion& operator*=	(const Quaternion& q2_);
		Quaternion& operator/=	(float f_);
		
		// ---------- friend
		friend Quaternion operator-(const Quaternion& q1_);							//Conjugate
		friend Quaternion operator-(const Quaternion& q1_, const Quaternion& q2_);
		friend Quaternion operator+(const Quaternion& q1_, const Quaternion& q2_);
		friend Quaternion operator*(const Quaternion& q1_, float f_);
		friend Quaternion operator*(float f_, const Quaternion& q1_);
		friend Vector3	 operator*(const Quaternion& q1_, const Vector3& v_);
		friend Vector3	 operator*(const Vector3& v_, const Quaternion& q1_);
		friend Quaternion operator*(const Quaternion& q1_, const Quaternion& q2_);
		friend Quaternion operator/(const Quaternion& lhs, float rhs);
		friend std::ostream& operator<<(std::ostream& os, const Quaternion& v_);
	};
	float		Dot				(const Quaternion& q0_, const Quaternion& q1_);
	Vector3		ToEularDegree	(const Quaternion& q_);
	Quaternion	FromToRotation	(const Vector3& fromVector, const Vector3& toVector);
	Quaternion	LookRotation	(const Vector3& forward, const Vector3& upwards, const Vector3& front);
	Quaternion	nLerp			(const Quaternion& start_, const Quaternion& end_, float time_);
	Quaternion	Slerp			(const Quaternion& q1_, const Quaternion& q2_, float time_);
	Quaternion	ToQuaternion	(const Matrix44& rot_matrix_);
	Quaternion	ToQuaternion	(float RADIAN_x, float RADIAN_y, float RADIAN_z);
	Quaternion	ToQuaternion	(const Vector3& DEGREE_);

} // namespace ddd

#endif // DDD_QUATERNION_H_
