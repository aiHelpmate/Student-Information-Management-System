#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "User.h"
#include "Module.h"
#include <cctype> // For std::tolower#include "user.h"
#include<sstream>
#include <fstream>

// Declared as an inline function
inline bool update(vector<User>& users, const User& user);
inline User login(const vector<User>& users, const string& username, const string& password);

class StaffLogic {
public:
    static bool startStaffLogic(vector<User>& users, vector<Module>& modules);
};