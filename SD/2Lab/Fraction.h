#ifndef __FRACTION_H
#define __FRACTION_H

#include<iostream>

class Fraction {
public:
	double num;
	double denom;

	Fraction(double n, double d): num(n), denom(d) {};

    /* TODO: Overload * operator
    Fraction operator*...{
    }*/
	Fraction operator*(const Fraction f) {
		return Fraction(num * f.num, denom * f.denom);
	}


	/* TODO: Overload / operator 
	Fraction operator/...{ 
	}*/
	Fraction operator/(const Fraction f) {
		return Fraction(num * f.denom, denom * f.num);
	}

	/* TODO: Get actual value of this fraction
	double getValue...{
	}*/
	double getValue() {
		return (double) num / denom;
	}

	/* TODO: Overload << operator - Friend function declaration */
    friend std::ostream& operator<<(std::ostream &out, const Fraction &fraction);
};

/* TODO: Overload << operator - Friend function implementation 
		Fraction f should be printed as:
			f.num/f.denom\n*/
    std::ostream& operator<<(std::ostream &out, const Fraction &fraction){
		out << fraction.num << "/" << fraction.denom << "\n";
		return out;
	}


#endif
