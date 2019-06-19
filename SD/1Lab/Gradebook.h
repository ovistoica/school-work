#ifndef __GRADEBOOK_H__
#define __GRADEBOOK_H__

#include <stdlib.h>

class Gradebook {
private:
	double *grades;
	int capacity; // max number of grades
	int count;    // current number of grades

public:
	Gradebook(int capacity):capacity(capacity) {
		this->count = 0;
		grades = new double[10];
	}

	~Gradebook() {
		delete [] grades;
	}

	void addGrade(double grade) {
		grades[count++] = grade;
	}

	double average() {
		double sum = 0;
		for(int i = 0; i < count; i++) {
			sum += grades[i];
		}
		return sum / count;
	}
};

#endif // __GRADEBOOK_H__
