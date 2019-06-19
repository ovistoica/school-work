/**
 * LabSD 5
 * users_table.h
 * Purpose: Skeleton code for Users Table in exercise 3.
 *
 * @authors Razvan Radoi, Alex Selea
 * @changes Ioana Stefan
 */

#ifndef __USERS_TABLE__H
#define __USERS_TABLE__H
#include <iostream>
#include <iterator>
#include <list>
#include <string>

struct user_details {
	std::string name;
	std::string password;
	bool logged_in;
};

class UsersTable {
private:
	int HMAX; // number of buckets
	std::list<user_details> * H; // pointer to buckets
	unsigned int (*hash)(std::string); // pointer to hash function

public:
	UsersTable(int hmax, unsigned int (*h)(std::string)) {
		hash = h;
		HMAX = hmax;
		H = new std::list<user_details> [HMAX];
		//TODO: vezi daca size = 0;

	}

	~UsersTable() {
		// TODO 3: free memory
		delete [] H;
	}

	std::string signup(std::string name, std::string password) {
		// TODO 3
		int index = hash(name) % HMAX;
		typename std::list<user_details>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->name == name){
				return "User " + name + " already added";
			}
		}
		user_details user;
		user.name = name;
		user.password = password;
		user.logged_in = false;
		H[index].push_back(user);
		return "User " + name + " successfully added";
	}

	std::string login(std::string name, std::string password) {
		// TODO 3
		int index = hash(name) % HMAX;
		typename std::list<user_details>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->name == name && it->password == password){
				it->logged_in = true;
				return "User " + name + " logged in successfully";
			}
		}
		return "Username/Password incorrect";
	}

	std::string logout(std::string name) {
		int index = hash(name) % HMAX;
		typename std::list<user_details>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->name == name){
				it->logged_in = false;
				return "User " + name + " logged out";
			}
		}
		return "User does not exist";

	}

	std::string change_password(std::string name, std::string oldPass, std::string newPass) {
		int index = hash(name) % HMAX;
		typename std::list<user_details>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->name == name && it->password == oldPass){
				it->password = newPass;
				return "Password changed for user " + name;
			}
		}
		return "Could not change password";
	}
};

#endif // __USERS_TABLE__H
