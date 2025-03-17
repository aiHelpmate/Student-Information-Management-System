#ifndef ASSIGNMENT_TEACHERLOGIC_H
#define ASSIGNMENT_TEACHERLOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Module.h"
using namespace std;


class TeacherLogic {
public:
    static bool startTeacherLogic(vector<User>& users,   vector<Module>& modules);
};

#endif // ASSIGNMENT_TEACHERLOGIC_H
