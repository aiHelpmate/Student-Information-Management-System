//
// Created by 刘一航 on 2023/10/20.
//

#include "Module.h"
#include <string>
#include <utility>
using namespace std;

Module::Module(string id, string name, string teacher, string student, string grades, string  moduleStatus)
    : module_id(std::move(id)), module_name(std::move(name)), teacher_id(std::move(teacher)), student_id(std::move(student)), student_grades(std::move(grades)), status(std::move(moduleStatus)) {
}

// Getter methods to access module information
string Module::getModuleId() const {
    return module_id;
}

string Module::getModuleName() const {
    return module_name;
}

string Module::getTeacherId() const {
    return teacher_id;
}

string Module::getStudentId() const {
    return student_id;
}

string Module::getStudentGrades() const {
    return student_grades;
}

string Module::getStatus() const {
    return status;
}

bool Module::isGradesPublished() const
{
    return false;
}




    // 在这里实现更新学生成绩的逻辑
  // 例如，可以将学生的成绩存储在类的私有成员中
  // 或者将其存储在一个关联数组或其他数据结构中
  // 
//void Module::setStudentGrade(const std::string& student, int newgrade)
//{
//}
//
//bool Module::isGradesPublished() const
//{
//    return false;
//}
