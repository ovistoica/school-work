#ifndef __PERSON_H
#define __PERSON_H

#include <stdio.h>
#include <string.h>
#include <iostream>

class Person {
public:
	char* name = NULL;
	int age;

	/* TODO: Implement constructor method 
	Person(char* newName, int newAge) {
	}*/
	Person(char* newName, int newAge) : age(newAge) {
		if (name) {
			delete [] name;
		}
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
	}


	/* TODO: Add copy constructor method */
	Person(const Person& other) : age(other.age) {
		if (name) {
			delete [] name;
		}
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
	}

	/* TODO: Overload copy assignment operator */
	Person& operator=(const Person& p) {
		if (name) {
			delete [] name;
		}
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);
		age = p.age;
		return *this;
	}

	/* TODO: Add destructor method */
	~Person() {
		if(name) {
			delete [] name;
		}
	}
	
	/* TODO: Overload << operator - Friend function declaration */
    friend std::ostream &operator<<(std::ostream &out, const Person& person);
};

/* TODO: Overload << operator - Friend function implementation 
		Person p should be printed as:
			p.name's age is p.age\n */
std::ostream &operator<<(std::ostream &out, const Person& person) {
	out << person.name << "'s age is " << person.age << "\n";
	return out;
}

#endif
