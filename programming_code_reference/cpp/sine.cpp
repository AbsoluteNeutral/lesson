
#include <limits>
#include <iostream>

double Factorial(int n)
{
	double value = 1;
	while(n)
		value *= n--;
	
	//std::cout << value << std::endl;
	return value;
}

double Pow(double v, int n)
{
	if(n == 0) return 1;
	double b = v;
	while(--n){
		v *= b;
	}
	//std::cout << v << std::endl;
	return v;
}

double sine(double v){
	double n = 0;
	double total = v;
	
	while(++n < 10)
	{	
		double a = (Pow(-1, n) * Pow(v, 2*n+1)) / double(Factorial(2*n + 1));
		total += a;
	}
	return total;
	
}

double sine2 (double v){
	double n = 0.0;
	double total = v;
	
	double x = v * v * v;
	double sign = -1.0;
	double f = 1.0 * 2.0 * 3.0;
	double finc = 3.0;
	while(++n < 10)
	{	
		double a = (sign * x) / f;
		total += a;
		
		x *= v * v;
		sign *= -1.0;
		double tmpf1 = finc + 1.0;
		double tmpf2 = finc + 2.0;
		f *= tmpf1 * tmpf2;
		finc = tmpf2;
	}
	return total;
}

int main(){
	
	//printf("%.25f\n",sine(0));
	//printf("%.25f\n",sine(1));
	printf("%.25f\n",sine(1.57));
	
	printf("%.25f\n",sine2(1.57));

}











