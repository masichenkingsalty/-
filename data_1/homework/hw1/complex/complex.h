#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;
class Complex {
private:


public:
	double real;
	double imag;
	double value;
	Complex()
	{
		real = 0;
		imag = 0;
	}
	void init(double r, double i)
	{
		real = r;
		imag = i;
	}
	double abscomplex();
	void random();




};

double Complex::abscomplex()
{
	double t;
	t = real * real + imag * imag;
	return sqrt(t);
}
void Complex::random() {
	real = pow(-1,(rand() % 2 + 1)) * (rand() % 20 + 1);
	imag = pow(-1, (rand() % 2 + 1)) * (rand() % 20 + 1);
}