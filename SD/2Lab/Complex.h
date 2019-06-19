#ifndef __COMPLEX_H
#define __COMPLEX_H

#include <iostream>

class Complex {
public:
    double re;
    double im;

    Complex(double real, double imag): re(real), im(imag) {};
	Complex() : re(0.0), im(0.0) {}

    /* TODO: Overload + operator
    Complex operator+... {
    }*/
	Complex operator+(const Complex c) {
		return Complex(re + c.re, im + c.im);
	}
    /* TODO: Overload - operator
    Complex operator-...{
    }*/
	Complex operator-(const Complex c) {
		return Complex(re - c.re, im - c.im);
	}

    /* TODO: Overload * operator
    Complex operator*
    }*/
	Complex operator*(const Complex c) {
		double real, imag;
		real = re * c.re - im * c.im;
		imag = re * c.im + im * c.re;
		return Complex(real, imag);
	}

    /* TODO: Implement Copy constructor method */
	Complex (const Complex& other) : re(other.re), im(other.im) {}

    /* TODO: Implement Copy assignment method */
	Complex& operator=(const Complex c) {
		re = c.re;
		im = c.im;
		return *this;
	}

    /* TODO: Implement Destructor method */
	~Complex() {}

    /* TODO: Overload << operator - Friend function declaration */
    friend std::ostream& operator<<(std::ostream &out, const Complex &complex);
};

/* TODO: Overload << operator - Friend function implementation 
		Complex number c should be printed as:
			Complex nr: Re(c.re)* Im(c.im)\n */
	std::ostream& operator<<(std::ostream &out, const Complex &complex) {
		out << "Complex nr: Re(" << complex.re << ") Im("
								<< complex.im << ")\n";
		return out;
	}

#endif
