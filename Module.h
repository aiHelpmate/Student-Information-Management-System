#ifndef ASSIGNMENT_MODULE_H
#define ASSIGNMENT_MODULE_H

#include <string>
#include <utility>

class Module {
private:
    std::string module_id;
    std::string module_name;
    std::string teacher_id;
    std::string student_id;
    std::string student_grades;
    std::string status;
    bool gradesPublished; // Indicates whether scores have been published

public:
    Module(std::string id, std::string name, std::string teacher, std::string student, std::string grades, std::string moduleStatus);

    std::string getModuleId() const;
    std::string getModuleName() const;
    std::string getTeacherId() const;
    std::string getStudentId() const;
    std::string getStudentGrades() const;
    std::string getStatus() const;
    bool isGradesPublished() const; 
    //void updateStudentGrade( const std::string& studentName, int newGrade) const;

};

#endif // ASSIGNMENT_MODULE_H
