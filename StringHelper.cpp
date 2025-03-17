#include <iostream>
#include <iomanip>
#include <sstream>
#include "StringHelper.h"
using namespace std;

void StringHelper::printFormatted(const string& input) {
    // Truncate or keep the string to a maximum of 30 characters.
    string truncated = input.substr(0, 100);

    // Calculate the padding length.
    int paddingLength = (100 - truncated.length()) / 2;

    // Print the formatted string.
    for (int i = 0; i < paddingLength; ++i) {
        cout << "-";
    }

    cout << " " << truncated << " ";

    for (int i = 0; i < paddingLength; ++i) {
        cout << "-";
    }

    cout << endl;
}

void StringHelper::delimiterLine() {
    for (int i = 0; i < 100; ++i) {
        cout << "-";
    }
    cout << endl;
}

void StringHelper::printStudentModule(const vector<Module>& modules, const string& studentId) {
    cout << std::left << setw(15) << "module_id"
        << setw(20) << "module_name"
        << setw(15) << "teacher_id"
        << setw(10) << "status"
        << endl;

    for (const Module& module : modules) {
        if (module.getStudentId() == studentId && module.getStatus() == "Released") {
            cout << std::left << setw(15) << module.getModuleId()
                << setw(20) << module.getModuleName()
                << setw(15) << module.getTeacherId()
                << setw(10) << module.getStatus()
                << endl;
        }
    }
}

void StringHelper::printTeacherModule(const vector<Module>& modules, const string& teacherId) {
    cout << std::left << setw(15)
        << "module_id" << setw(20)
        << "module_name" << setw(15)
        << endl;

    for (const Module& module : modules) {
        if (module.getTeacherId() == teacherId) {
            cout << std::left << setw(15) << module.getModuleId()
                << setw(20) << module.getModuleName()
                << endl;
        }
    }
}


