#include <iostream>
#include <vector>
#include "User.h"
#include "Utils.h"
#include "StudentLogic.h"
#include "TeacherLogic.h"
#include "StaffLogic.h"
#include "StringHelper.h"

using namespace std;

int main() {
    vector<User> users = Utils::loadUserData("database/User.txt");
    vector<Module> modules = Utils::loadModuleData("database/Module.txt");

    string userInput;
    StringHelper::printFormatted("Welcome to the Management System");

    while (true) {
        cout << "Please choose your role: \n"
            << "1. Student \n"
            << "2. Teacher \n"
            << "3. Staff \n"
            << "0. Quit \n";

        StringHelper::delimiterLine();
        getline(cin, userInput);

        if (userInput == "0") {
            cout << "Exiting the system.\n";
            break;
        }
        else if (userInput == "1") {
            StudentLogic::startStudentLogic(users, modules);
        }
        else if (userInput == "2") {
            TeacherLogic::startTeacherLogic(users, modules);
        }
        else if (userInput == "3") {
            StaffLogic::startStaffLogic(users, modules);
        }
        else {
            cout << "Invalid input. Please try again with a valid option.\n";
        }
    }

    return 0;
}
