
#include "Vector3.h"

#ifdef WITH_VECTOR2_
	#include "Vector2.h"
#endif
#ifdef WITH_VECTOR4_
	#include "Vector4.h"
#endif

namespace ddd {
// ---------- static
	const Vector3 Vector3::Zero{};
	const Vector3 Vector3::One		{ float(1.0), float(1.0), float(1.0) };
	const Vector3 Vector3::VectorX	{ float(1.0), float(0.0), float(0.0) };
	const Vector3 Vector3::VectorY	{ float(0.0), float(1.0), float(0.0) };
	const Vector3 Vector3::VectorZ	{ float(0.0), float(0.0), float(1.0) };

// ---------- constructor
	Vector3::Vector3() noexcept
		: x(0), y(0), z(0)
	{}
	Vector3::Vector3(float x_, float y_) noexcept
		: x(x_), y(y_), z(0) 
	{}
	Vector3::Vector3(float x_, float y_, float z_ ) noexcept
		: x(x_), y(y_), z(z_) 
	{}
	
// ---------- getters
	Vector3 Vector3::Cross(const Vector3& rhs) const {
		return Vector3{
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x };
	}
	float Vector3::Dot(const Vector3& v_) const { 
		return x * v_.x + y * v_.y + z * v_.z;
	}
	Vector3 Vector3::GetAbsVector()	const {
		return Vector3{ std::fabs(x), std::fabs(y), std::fabs(z) };
	}
	int	Vector3::GetMinAxis() const {
		return (x < y ? (x < z ? 0 : 2) : (y < z ? 1 : 2));
	}
	int	Vector3::GetMaxAxis() const {
		return (x < y ? (y < z ? 2 : 1) : (x < z ? 2 : 0));
	}
	Vector3 Vector3::Normalized() const {
		float len = Length();
		len = len <= MACHINE_EPSILON ? float(0.0): (float(1.0) / len);
		return Vector3{ x * len, y * len, z * len };
	}
	Vector3 Vector3::GetUnitOrthogonalVector() const {
		// Get the minimum element of the vector
		Vector3 vectorAbs(std::fabs(x), std::fabs(y), std::fabs(z));
		int minElement = vectorAbs.GetMinAxis();
	
		if (minElement == 0) {
			return Vector3{0, -z, y} / std::sqrt(y*y + z*z);
		}
		else if (minElement == 1) {
			return Vector3{z, 0, x} / std::sqrt(x*x + z*z);
		}
		else {
			return Vector3{-y, x, 0} / std::sqrt(x*x + y*y);
		}
	}
	float Vector3::LengthSq() const { 
		return x * x + y * y + z * z; 
	}
	float Vector3::Length() const { 
		return sqrtf(LengthSq()); 
	}
	bool Vector3::IsNan() const {
		return (x != x) || (y != y) || (z != z);
	}
	bool Vector3::IsUnit() const {
		return ApproxEqual(LengthSq(), 1.0f);
	}
	bool Vector3::IsZero() const {
		return ApproxEqual(LengthSq(), 0.0f);
	}	
	
// ---------- setters
	float Vector3::Normalize() {
		float len = Length();
		float overlen = len <= MACHINE_EPSILON ? float(0.0) : (float(1.0) / len);
		x *= overlen;
		y *= overlen;
		z *= overlen;
		return len;
	}
	void Vector3::Set(float x_, float y_, float z_) {
		x = x_; y = y_; z = z_;
	}
	void Vector3::SetZero() { x = y = z = float(0.0); }
	void Vector3::Reset()	{ x = y = z = float(0.0); }
	
// ---------- operator
#ifdef WITH_VECTOR2_
	Vector3::Vector3(const Vector2& v_, float z_) noexcept
		: x(v_.x), y(v_.y), z(z_) 
	{}
	Vector3& Vector3::operator= (const Vector2& v)			{ x = v.x;  y = v.y;			return *this; }
	Vector3& Vector3::operator+=(const Vector2& v)			{ x += v.x; y += v.y;			return *this; }
	Vector3 operator-(const Vector3& l, const Vector2& r)	{ return Vector3{ l.x - r.x, l.y - r.y, l.z	};}  //minus
	Vector3 operator+(const Vector3& l, const Vector2& r)	{ return Vector3{ l.x + r.x, l.y + r.y, l.z	};}  //plus
#endif
#ifdef WITH_VECTOR4_
	Vector3::Vector3(const Vector4& v_) noexcept
		: x(v_.x), y(v_.y), z(v_.z)
	{}
	Vector3& Vector3::operator= (const Vector4& v)		{ x = v.x;  y = v.y;	z = v.z;	return *this; }
#endif
	Vector3& Vector3::operator+=(const Vector3& v)		{ x += v.x; y += v.y;	z += v.z;	return *this; }
	Vector3& Vector3::operator-=(const Vector3& v)		{ x -= v.x; y -= v.y;	z -= v.z;	return *this; }
	Vector3& Vector3::operator*=(float f)				{ x *= f;	y *= f;		z *= f;		return *this; }
	Vector3& Vector3::operator/=(float f)				{ x /= f;	y /= f;		z /= f;		return *this; }
	bool	 Vector3::operator==(const Vector3& v) const{ return ((x == v.x) && (y == v.y) && (z == v.z)); }
	float& 	 Vector3::operator[] (int index)			{ return (&x)[index]; }
	float  	 Vector3::operator[] (int index) const		{ return (&x)[index]; }

	Vector3 operator-(const Vector3& l)						{ return Vector3{ -l.x, -l.y, -l.z					}; }  //negate
	Vector3 operator-(const Vector3& l, const Vector3& r)	{ return Vector3{ l.x - r.x, l.y - r.y, l.z - r.z	}; }  //minus
	Vector3 operator-(const Vector3& l, float f)			{ return Vector3{ l.x - f,   l.y - f,   l.z - f		}; }  //minus
	Vector3 operator+(const Vector3& l, const Vector3& r)	{ return Vector3{ l.x + r.x, l.y + r.y, l.z + r.z	}; }  //plus
	Vector3 operator+(const Vector3& l, float f)			{ return Vector3{ l.x + f,   l.y + f,   l.z + f		}; }  //plus
	Vector3 operator*(const Vector3& l, const Vector3& r)	{ return Vector3{ l.x * r.x , l.y * r.y , l.z * r.z }; }  //multiply
	Vector3 operator*(const Vector3& l, float f)			{ return Vector3{ l.x * f, l.y * f, l.z * f			}; }  //multiply
	Vector3 operator/(const Vector3& l, float f)			{ return Vector3{ l.x / f, l.y / f, l.z / f			}; }  //division
	Vector3 operator^(const Vector3& l, const Vector3& r) {
		return Vector3{
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x };
	}
	Vector3 operator-(float f, const Vector3& r) { return Vector3{ f - r.x, f - r.y, f - r.z }; }
	Vector3 operator+(float f, const Vector3& r) { return Vector3{ f + r.x, f + r.y, f + r.z }; }
	Vector3 operator*(float f, const Vector3& r) { return Vector3{ f * r.x, f * r.y, f * r.z }; }
	Vector3 operator/(float f, const Vector3& r) { return Vector3{ f / r.x, f / r.y, f / r.z }; }
	std::ostream& operator<<(std::ostream& os, const Vector3& v){
		printf("{ %.6f %.6f %.6f }\n", v.x, v.y, v.z);
		//os << " {" << v.x << "," << v.y << "," << v.z << "}\n";
		return os;
	}
	
	float SmoothDampHelper(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		smoothTime = MAX2(0.0001f, smoothTime);
		float num = 2.0f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
		float num4 = current - target;
		float num5 = target;
		float num6 = maxSpeed * smoothTime;
		num4 = Clamp(num4, -num6, num6);
		target = current - num4;
		float num7 = (currentVelocity + num * num4) * deltaTime;
		currentVelocity = (currentVelocity - num * num7) * num3;
		float num8 = target + (num4 + num7) * num3;
		if (num5 - current > 0.0f == num8 > num5)
		{
			num8 = num5;
			currentVelocity = (num8 - num5) / deltaTime;
		}
		return num8;
	}
	Vector3 Vector3::SmoothDamp(const Vector3& start, const Vector3& end, Vector3& velocity, float smoothTime, float maxSpeed, float deltaTime) 
	{
		return Vector3
		{
			SmoothDampHelper(start.x, end.x, velocity.x, smoothTime, maxSpeed, deltaTime),
			SmoothDampHelper(start.y, end.y, velocity.y, smoothTime, maxSpeed, deltaTime),
			SmoothDampHelper(start.z, end.z, velocity.z, smoothTime, maxSpeed, deltaTime)
		};
	}

// ---------- extern function
#ifdef WITH_VECTOR2_
	float DistanceSq(const Vector2& v0_, const Vector3& v1_) {
		float a = v0_.x - v1_.x;
		float b = v0_.y - v1_.y;
		return a * a + b * b + (v1_.z * v1_.z);
	}
	float DistanceSq(const Vector3& v0_, const Vector2& v1_) {
		float a = v0_.x - v1_.x;
		float b = v0_.y - v1_.y;
		return a * a + b * b + (v0_.z * v0_.z);
	}
#endif
	Vector3 ABS(const Vector3 &v_) {
		return Vector3{ 
			v_.x < 0.0f ? -v_.x : v_.x, 
			v_.y < 0.0f ? -v_.y : v_.y,
			v_.z < 0.0f ? -v_.z : v_.z, };
	}

	bool ApproxEqual(const Vector3& v0_, const Vector3& v1_, float epsilon) {
		return ApproxEqual(v0_.x, v1_.x, epsilon)
			&& ApproxEqual(v0_.y, v1_.y, epsilon)
			&& ApproxEqual(v0_.z, v1_.z, epsilon);
	}

	float Angle(const Vector3& v0_, const Vector3& v1_) {
		float v = v0_.Dot(v1_) / (Length(v0_) * Length(v1_));
		v = MAX2(v, -1.0f);
		v = MIN2(v, 1.0f);
		return std::acos(v);
	}

	Vector3 ClampMagnitude(Vector3 vector, float maxLength) {
		float length = Length(vector);
		if (length > maxLength)
			vector *= maxLength / length;
		return vector;
	}

	void CopyVector3Array(Vector3* dest, const Vector3* source, size_t sz) {
		Vector3* c = dest;
		const Vector3* b = source;
		const Vector3* e = source + sz;
		while (b != e) {
			*c = *b; ++c; ++b;
		}
	}

	void CopyVector3Array(std::vector<Vector3>& dest, const Vector3* source, size_t sz) {
		auto c = dest.begin();
		const Vector3* b = source;
		const Vector3* e = source + sz;
		while (b != e) {
			*c = *b; ++c; ++b;
		}
	}

	Vector3 Cross(const Vector3& from_, const Vector3& to_) {
		return ddd::Vector3{
			from_.y * to_.z - from_.z * to_.y,
			from_.z * to_.x - from_.x * to_.z,
			from_.x * to_.y - from_.y * to_.x };
	}

	float Distance(const Vector3& v0_, const Vector3& v1_) {
		return std::sqrt(DistanceSq(v0_, v1_));
	}
	float DistanceSq(const Vector3& v0_, const Vector3& v1_) {
		float a = v0_.x - v1_.x;
		float b = v0_.y - v1_.y;
		float c = v0_.z - v1_.z;
		return a * a + b * b + c * c;
	}
	float Dot(const Vector3& v0_, const Vector3& v1_) { 
		return v0_.x * v1_.x + v0_.y * v1_.y + v0_.z * v1_.z; 
	}
	Vector3 FromSpherical(float r, float theta, float phi) {
		float sinTheta = std::sin(theta);
		Vector3 v {
			r * sinTheta * std::cos(phi),
			r * sinTheta * std::sin(phi),
			r * std::cos(theta)
		};
		return v;
	}

	bool IsParallel(const Vector3& v0_, const Vector3& v1_) {
		return v0_.Cross(v1_).LengthSq() < EPSILON;
	}

	bool IsOrthogonal(const Vector3& v0_, const Vector3& v1_) {
		return std::abs(v0_.Dot(v1_)) < EPSILON;
	}

	float Length	(const Vector3& v_) { return v_.Length();	}
	float LengthSq	(const Vector3& v_) { return v_.LengthSq();	}
	Vector3 Lerp(const Vector3& start_, const Vector3& end_, float time_) {
		// Imprecise method, which does not guarantee v = v1 when t = 1, due to floating-point arithmetic error.
		// This form may be used when the hardware has a native fused multiply-add instruction.
		//return start_ + float(time_) * (end_ - start_);

		// Precise method, which guarantees v = v1 when t = 1.
		Vector3 v0 = (float(1) - float(time_)) * start_;
		Vector3 v1 = float(time_) * end_;
		return v0 + v1;
	}
	Vector3 nLerp(const Vector3& start_, const Vector3& end_, float time_) {
		return Lerp(start_, end_, time_).Normalized();
	}
	Vector3	LerpDelta(const Vector3& start_, Vector3& deltaOf_end_start_, float time_) {
		return start_ + float(time_) * deltaOf_end_start_;
	}
	Vector3	nLerpDelta(const Vector3& start_, Vector3& deltaOf_end_start_, float time_) {
		return LerpDelta(start_, deltaOf_end_start_, time_).Normalized();
	}
	Vector3 LinearRand(const Vector3& v0_, const Vector3& v1_) {
		return Vector3(sfrand(v0_.x, v1_.x), sfrand(v0_.y, v1_.y), sfrand(v0_.z, v1_.z));
	}
	float Magnitude		(const Vector3& v_) { return v_.Length();	}
	float MagnitudeSq	(const Vector3& v_) { return v_.LengthSq();	}

	Vector3 MoveTowards(const Vector3& current, const Vector3&  target, float maxDistanceDelta) {
		Vector3 d = target - current;
		float m = Length(d);
		if (m < maxDistanceDelta || m == 0.0f)
			return target;
		return current + (d * maxDistanceDelta / m);
	}

	Vector3 Min(const Vector3& v0_, const Vector3& v1_) {
		return Vector3{	MIN2(v0_.x, v1_.x),
						MIN2(v0_.y, v1_.y),
						MIN2(v0_.z, v1_.z)
		};
	}
	Vector3 Max(const Vector3& v0_, const Vector3& v1_) {
		return Vector3{	MAX2(v0_.x, v1_.x),
						MAX2(v0_.y, v1_.y),
						MAX2(v0_.z, v1_.z)
		};
	}

	float Normalize	(Vector3& v_)		{ return v_.Normalize(); }
	Vector3  Normalized	(const Vector3& v_) { return v_.Normalized(); }

	Vector3 Project(const Vector3& v0_, const Vector3& v1_) {
		float m = Length(v1_);
		return v0_.Dot(v1_) / (m * m) * v1_;
	}

	Vector3 ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal) {
		return Reject(vector, planeNormal);
	}
	Vector3 Reflect(const Vector3& vector, const Vector3& planeNormal) {
		return vector - 2 * Project(vector, planeNormal);
	}
	Vector3 Reject(const Vector3& a, const Vector3& b) {
		return a - Project(a, b);
	}
	Vector3 Slerp(Vector3 v0_, Vector3 v1_, float time_) {
		float magA = v0_.Normalize();
		float magB = v1_.Normalize();
		float dot = v0_.Dot(v1_);
		dot = ddd::Clamp(dot, -1.0f, 1.0f);
		//dot = fmaxf(dot, -1.0);
		//dot = fminf(dot, 1.0);
		float theta = acos(dot) * time_;
		Vector3 relativeVec = (v1_ - v0_ * dot).Normalized();
		Vector3 newVec = v0_ * std::cos(theta) + relativeVec * std::sin(theta);
		return newVec * (magA + (magB - magA) * time_);
	}
	Vector3 SlerpClamp(Vector3 v0_, Vector3 v1_, float time_) {
		if (time_ < 0) return v0_;
		else if (time_ > 1) return v1_;
		return Slerp(v0_, v1_, time_);
	}
	void ToSpherical(const Vector3& vector, float &rad, float &theta, float &phi) {
		rad = Length(vector);
		float v = vector.z / rad;
		v = std::fmax(v, -1.0f);
		v = std::fmin(v, 1.0f);
		theta = acos(v);
		phi = atan2(vector.y, vector.x);
	}

	Vector3 Orthogonal(const Vector3& v) {
		return v.z < v.x ? Vector3(v.y, -v.x, 0) : Vector3(0, -v.z, v.y);
	}

	void BarycentricInTriangle(const Vector3& a, const Vector3& b, const Vector3& c,
		const Vector3& p, float& u, float& v, float& w) {
		const Vector3 v0 = b - a;
		const Vector3 v1 = c - a;
		const Vector3 v2 = p - a;

		float d00 = v0.Dot(v0);
		float d01 = v0.Dot(v1);
		float d11 = v1.Dot(v1);
		float d20 = v2.Dot(v0);
		float d21 = v2.Dot(v1);

		float denom = d00 * d11 - d01 * d01;
		v = (d11 * d20 - d01 * d21) / denom;
		w = (d00 * d21 - d01 * d20) / denom;
		u = float(1.0f) - v - w;
	}

	//Computes scalar triple product
	float ScalarTripleProduct(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
		return Dot(a, b.Cross(c));
	}
	//Barycentric Of Line, Triangle, Tetrahedron
	bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b, float& u, float& v, float epsilon) {
		Vector3 ba = a - b;
		Vector3 bp = point - b;
		float demo = ba.Dot(ba);
		if (demo == 0.0f || demo > -epsilon && demo < epsilon) {
			u = 0.0f;
			v = 1.0f;
			return false;
		}
		u = bp.Dot(ba) / ba.Dot(ba);
		v = 1.0f - u;
		if (v == 0.0f && u == 0.0f)
			return false;
		if (v < 0.0f)
			if (v < -epsilon) return false;
		if (u < 0.0f)
			if (u < -epsilon) return false;
		return true;
	}
	bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c, float& u, float& v, float& w, float epsilon) {
		Vector3 ap = point - a;
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 normal = ab.Cross(ac);
		float demo = normal.Dot(normal);
		if (demo == 0.0f || demo > -epsilon && demo < epsilon) {
			u = 0.0f;
			v = 0.0f;
			w = 1.0f;
			// v = u = w = 0.0f;
			return false;
		}
		w = normal.Dot(ab.Cross(ap)) / demo;
		v = normal.Dot(ap.Cross(ac)) / demo;
		u = 1.0f - w - v;

		if (v == 0.0f && u == 0.0f && w == 0.0f)
			return false;
		if (u < 0.0f)
			if (u < -epsilon) return false;
		if (v < 0.0f)
			if (v < -epsilon) return false;
		if (w < 0.0f)
			if (w < -epsilon) return false;
		return true;
	}
	bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d, float& u, float& v, float& w, float& t, float epsilon) {
		Vector3 ap{ point - a };
		Vector3 bp{ point - b };
		Vector3 ab{ b - a };
		Vector3 ac{ c - a };
		Vector3 ad{ d - a };
		Vector3 bc{ c - b };
		Vector3 bd{ d - b };
		//float a6 = ScalarTripleProduct(bp, bd, bc);
		//float b6 = ScalarTripleProduct(ap, ac, ad);
		//float c6 = ScalarTripleProduct(ap, ad, ab);
		//float d6 = ScalarTripleProduct(ap, ab, ac);
		float demo = 1.0f / ScalarTripleProduct(ab, ac, ad);
		if (demo > -epsilon && demo < epsilon) {
			//v = u = w = t = 0.0f;
			return false;
		}
		//u = ScalarTripleProduct(bp, bd, bc) * demo;
		v = ScalarTripleProduct(ap, ac, ad) * demo;
		w = ScalarTripleProduct(ap, ad, ab) * demo;
		t = ScalarTripleProduct(ap, ab, ac) * demo;
		u = 1.0f - w - v - t;
		if (v == 0.0f && u == 0.0f && w == 0.0f && t == 0.0f)
			return false;
		if (u < 0.0f)
			if (u < -epsilon) return false;
		if (v < 0.0f)
			if (v < -epsilon) return false;
		if (w < 0.0f)
			if (w < -epsilon) return false;
		if (t < 0.0f)
			if (t < -epsilon) return false;
		return true;
	}

	Vector3 ComputeClosestPointOnSegment(const Vector3& segPointA, const Vector3& segPointB, const Vector3& pointC) {

		const Vector3 vector{ segPointB - segPointA };

		float abLengthSquare = vector.LengthSq();

		// If the segment has almost zero length
		if (abLengthSquare < MACHINE_EPSILON) {

			// Return one end-point of the segment as the closest point
			return segPointA;
		}

		// Project point C onto "AB" line
		float t = (pointC - segPointA).Dot(vector) / abLengthSquare;

		// If projected point onto the line is outside the segment, clamp it to the segment
		if (t < float(0.0)) return segPointA;
		if (t > float(1.0)) return segPointB;

		// Return the closest point on the segment
		return segPointA + t * vector;
	}

	// Compute the intersection between a plane and a segment
	// Let the plane define by the equation planeNormal.dot(X) = planeD with X a point on the plane and "planeNormal" the plane normal. This method
	// computes the intersection P between the plane and the segment (segA, segB). The method returns the value "t" such
	// that P = segA + t * (segB - segA). Note that it only returns a value in [0, 1] if there is an intersection. Otherwise,
	// there is no intersection between the plane and the segment.
	float ComputePlaneSegmentIntersection(const Vector3& segA, const Vector3& segB, float planeD, const Vector3& planeNormal) {
		float t = float(-1);
		float nDotAB = planeNormal.Dot(segB - segA);

		// If the segment is not parallel to the plane
		if (std::abs(nDotAB) > EPSILON) {
			t = (planeD - planeNormal.Dot(segA)) / nDotAB;
		}

		return t;
	}

	float ComputePointToLineDistance(const Vector3& linePointA, const Vector3& linePointB, const Vector3& point) {

		float distAB = (linePointB - linePointA).Length();

		if (distAB < MACHINE_EPSILON) {
			return (point - linePointA).Length();
		}

		return ((point - linePointA).Cross(point - linePointB)).Length() / distAB;
	}

	//Generate Basis
	void GenerateOrthonormalBasis(const Vector3& w, Vector3* u, Vector3* v) {
		if ((std::abs(w.x) >= std::abs(w.y)) && (std::abs(w.x) >= std::abs(w.z))) {
			u->x = -w.y;
			u->y = w.x;
			u->z = 0.0f;
		}
		else {
			u->x = 0.0f;
			u->y = w.z;
			u->z = -w.y;
		}
		u->Normalize();
		*v = Cross(w, *u);
		v->Normalize();
	}
}	//namespace ddd
