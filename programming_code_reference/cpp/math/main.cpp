
#include <limits>
#include <iostream>
#include "Reals.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "Matrix44.h"
#include "Quaternion.h"

int main(){
	float a = 0.0f;
	a = a <= 0.0f ? -a : a;
	std::cout << a << std::endl;
	std::cout << a << std::endl;

	ddd::Vector2 c{ 1.023f, 12312.0f};
	std::cout << c << std::endl;
	
	ddd::Vector3 d{0.0f, 90.0f, 0.0f};
	std::cout << ddd::Vector3::Zero << std::endl;
	std::cout << ddd::Vector3::One << std::endl;
	
	
	ddd::Matrix33 m3{};
	std::cout << m3 << std::endl;
	std::cout << ddd::Matrix33::Identity << std::endl;

	ddd::Matrix44 m4{};
	std::cout << m4 << std::endl;
	std::cout << ddd::Matrix44::Identity << std::endl;
	
	ddd::Quaternion q{d};
	q.SetFromEulerAngles(d);
	std::cout << q << std::endl;
	std::cout << q.GetInverted() << std::endl;
}
