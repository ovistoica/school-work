#ifndef __FRACTION_H__
#define __FRACTION_H__

class Fraction {
private:
	double num;
	double denom;

public:
	Fraction(double num, double denom): num(num), denom(denom) {
	}

	double getNum() {
		return this->num;
	}

	double getDenom() {
		return this->denom;
	}

	double decimal() {
		return this->num / this->denom;
	}

	Fraction multiply(Fraction f) {
		double num, denom;
		num = this->num * f.num;
		denom = this->denom * f.denom;
		return Fraction(num, denom);
	}

	Fraction divide(Fraction f) {
		double num, denom;
		num = this->num * f.denom;
		denom = this->denom * f.num;
		return Fraction(num, denom);
	}
};

#endif // __FRACTION_H__
