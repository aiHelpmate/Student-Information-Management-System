#ifndef ASSIGNMENT_USERLOGIC_H
#define ASSIGNMENT_USERLOGIC_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "User.h"
#include "Module.h"
#include <cctype> // For std::tolower

class StudentLogic {
public:
	static bool startStudentLogic(vector<User>& users, const vector<Module>& modules);
	static void StudentMenu(vector<User>& users, User& curUser, const vector<Module>& modules);
};


#endif //ASSIGNMENT_USERLOGIC_H
