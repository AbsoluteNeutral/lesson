
#ifndef _REALS_H
#define _REALS_H

#include <cmath>    //sin, cos, tan 
#include <stdio.h>	//printf
#include <limits>

namespace zg
{
	//using double or float for vector classes
  //this may not be necessary, but it is implemented in this class
#ifdef _DOUBLE_PRECISION
	typedef double realtype;
#else
	typedef float realtype;
#endif

  //this is useful for switching between OpenGL and directX
	//using ROW or COL major for matrix
	//#define ROW_MAJOR 1
	#define COL_MAJOR 1
}

//undef for min max in <cmath>
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

static const float DECIMAL_LARGEST		= std::numeric_limits<float>::max();
static const float MACHINE_EPSILON		= std::numeric_limits<float>::epsilon();
static const double MACHINE_EPSILON_D	= std::numeric_limits<double>::epsilon();

#define EPSILON 0.000001f

//math constant
//double
#define M_E         2.71828182845904523536   // e
#define M_LOG2E     1.44269504088896340736   // log2(e)
#define M_LOG10E    0.434294481903251827651  // log10(e)
#define M_LN2       0.693147180559945309417  // ln(2)
#define M_LN10      2.30258509299404568402   // ln(10)
#define M_PI        3.14159265358979323846   // pi
#define M_PI_2      1.57079632679489661923   // pi/2
#define M_PI_4      0.785398163397448309616  // pi/4
#define M_1_PI      0.318309886183790671538  // 1/pi
#define M_2_PI      0.636619772367581343076  // 2/pi
#define M_2_SQRTPI  1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2     1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2   0.707106781186547524401  // 1/sqrt(2)
#define D_TWOPI     6.28318530718
#define D_PI180     0.01745329251994329576924
#define D_INV_PI180 57.2957795130823208768

//float
#define PI          3.14159265358979323846f
#define TWOPI       6.28318530718f
#define PI2         1.57079632679489661923f
#define PI4         0.785398163397448309616f
#define PI180       0.01745329251994329576924f
#define INV_PI180   57.2957795130823208768f

//max min ternary
#define MAX2(a,b) (a > b ? a : b)
#define MIN2(a,b) (a < b ? a : b)
#define MAX3(a,b,c) (a < b ? (b < c ? c : b) : (a < c ? c : a))
#define MIN3(a,b,c) (a < b ? (a < c ? a : c) : (b < c ? b : c))


#define CHECK_NEG_ZERO(a) ((((a) > -EPSILON && (a) < EPSILON) ? 0.0f : (a)))
#define CHECK_NEG_ZERO2(a) ((((a) == -0.0f) ? 0.0f : (a)))

#define SMOOTHSTEP(x) ((x) * (x) * (3-2 * (x)))
#define SMOOTHERSTEP(x) ((x) * (x) * ((x) * ((x) * 6 - 15) + 10))

//floating point check isnan
#define ISNAN(f) (f != f)	

//convert degree to radian, vice versa
#define TO_RAD(a) ((a) * (PI180))
#define TO_DEG(a) ((a) * (INV_PI180))

namespace zg {
	ZG_API float	ToRad(float value);
	ZG_API float	ToDeg(float value);

	//float
	//Trigonometric 
	float sin(float x);
	float cos(float x);
	float tan(float x);
	float asin(float x);
	float acos(float x);
	float atan(float x);
	float atan2(float y, float x);
	//Hyperbolic 
	float sinh(float x);
	float cosh(float x);
	float tanh(float x);
	float asinh(float x);
	float acosh(float x);
	float atanh(float x);
	//Exponential and logarithmic

	//Power
	float pow(float x, float exp);
	float sqrt(float x);

	//double
	////Trigonometric 
	//double sin(double x);
	//double cos(double x);
	//double tan(double x);
	//double asin(double x);
	//double acos(double x);
	//double atan(double x);
	//double atan2(double y, double x);
	////Hyperbolic 
	//double sinh(double x);
	//double cosh(double x);
	//double tanh(double x);
	//double asinh(double x);
	//double acosh(double x);
	//double atanh(double x);
	////Exponential and logarithmic

	//Power
	double pow(double x, double exp);
	double sqrt(double x);

	template <typename T>
	inline T Max(const T lhs, const T rhs) {
		return lhs > rhs ? lhs : rhs;
	}
	template <typename T>
	inline T Min(const T lhs, const T rhs) {
		return lhs > rhs ? rhs : lhs;
	}
	template <typename T>
	inline T Clamp(const T value) {
		return Clamp(value, T(0), T(1));
	}
	template <typename T>
	inline T Clamp(const T value_, const T lowerLimit_, const T upperLimit_) {
		return MIN2(MAX2(value_, lowerLimit_), upperLimit_);
	}

	template <typename T>
	T Loop(T value_, T lowerLimit_, T upperLimit_) {
		while (value_ > upperLimit_)
			value_ -= upperLimit_;
		while (value_ < lowerLimit_)
			value_ += lowerLimit_;
		return value_;
	}
	template <typename T>
	T LoopInclude(T value_, T lowerLimit_, T upperLimit_) {
		while (value_ >= upperLimit_)
			value_ -= upperLimit_;
		while (value_ <= lowerLimit_)
			value_ += lowerLimit_;
		return value_;
	}

	template <typename T>
	inline void Swap(T& a, T& b) {
		T temp(a);
		a = b;
		b = temp;
	}

  //write your own power 
	template <typename T>
	float pow(T value, unsigned int pow_) {
		T temp;
		if (pow_ == 0)
			return 1;
		temp = pow(value, pow_ >> 1);
		if (pow_ % 2 == 0)
			return temp * temp;
		else
			return value * temp * temp;
	}
#pragma region __________________________________________________ExtraExternal	
	ZG_API float	Absolute		(float val);
	ZG_API double	Absolute		(double val);
	ZG_API bool		ApproxEqual		(float a, float b, float epsilon = MACHINE_EPSILON);
	ZG_API bool		ApproxEqual		(double a, double b, double epsilon = MACHINE_EPSILON_D);
	ZG_API float	Lerp			(float start_, float end_, float time_);
	ZG_API double	Lerp			(double start_, double end_, double time_);

	//random
	ZG_API float	randomf			(float value);
	ZG_API float	randomRangef	(float min, float max);
	ZG_API int		random1ToMax	(int max);
	ZG_API int		randomRange		(int min, int max);
	ZG_API float	sfrand			();
	ZG_API float	sfrand			(float min, float max);

	ZG_API float	BounceIn		(float time, float begin, float final, float duration);
	ZG_API float	BounceOut		(float time, float begin, float final, float duration);
	ZG_API float	QuinIn			(float time, float begin, float final, float duration);
	ZG_API float	QuinOut			(float time, float begin, float final, float duration);

	ZG_API float	SmoothDampf		(float current, float target, float currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

#pragma endregion

}

#endif
