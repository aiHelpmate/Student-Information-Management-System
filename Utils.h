#ifndef ASSIGNMENT_UTILS_H
#define ASSIGNMENT_UTILS_H


#include "User.h"
#include "Module.h"
#include <vector>
using namespace std;
#include <string>
class Utils {
public:
    static vector<User> loadUserData(const string& filename);
    static vector<Module> loadModuleData(const string& filename);
    static string removeSpaces(const string& value);
};


#endif //ASSIGNMENT_UTILS_H
