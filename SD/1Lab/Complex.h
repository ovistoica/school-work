#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <math.h>
#include<stdlib.h>

class Complex {
private:
	double re;
	double im;

public:
	Complex(double re, double im): re(re), im(im) {
	}

	double getRe() {
		return this->re;
	}

	double getIm() {
		return this->im;
	}

	double modulus() {
		return sqrt(re * re + im * im);
	}

	Complex add(Complex c) {
		return Complex(c.re + this->re, c.im + this->im);
	}

	Complex multiply(Complex c) {
		double real, imag;
		real = (this->re * c.re - this->im * c.im);
		imag = (this->re * c.im + this->im * c.re);

		return Complex(real, imag);
	}
};

#endif // __COMPLEX_H__
