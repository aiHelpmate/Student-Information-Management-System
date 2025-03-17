#ifndef UNTITLED_STRINGHELPER_H
#define UNTITLED_STRINGHELPER_H

#include <string>
#include "Module.h"
#include <vector>

class StringHelper {
public:
    static void delimiterLine();
    static void printFormatted(const std::string& input);
    static void printStudentModule(const std::vector<Module>& modules, const std::string& studentId);
    static void printTeacherModule(const std::vector<Module>& modules, const std::string& teacherId);

};


#endif //UNTITLED_STRINGHELPER_H