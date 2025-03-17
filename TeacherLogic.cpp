#include "TeacherLogic.h"
#include <iostream>
#include <fstream>
#include "StringHelper.h"
#include <iomanip>
#include <cstdlib>
#include "User.h"
#include "StaffLogic.h"

using namespace std;

// Function to find a specific module from the vector of modules
Module findModule(const vector<Module>& modules, const string& moduleId, const string& studentId) {
    for (const Module& module : modules) {
        if (module.getModuleId() == moduleId && module.getStudentId() == studentId) {
            return module;
        }
    }
    return Module("", "", "", "", "", "");
}

// Function to update the student's grade in a specific module
bool updateStudentGrade(vector<Module>& modules, const Module& updatedModule) {
    try {
        for (Module& module : modules) {
            if (module.getModuleId() == updatedModule.getModuleId()) {
                module = updatedModule;
                break;
            }
        }
        ofstream outFile("database/Module.txt");
        if (!outFile) {
            throw runtime_error("Error: Unable to open Module.txt for writing."); // Throw a runtime error
        }

        for (const Module& module : modules) {
            outFile << module.getModuleId() << "," << module.getModuleName() << ","
                << module.getTeacherId() << "," << module.getStudentId() << ","
                << module.getStudentGrades() << "," << module.getStatus() << "\n";
        }

        outFile.close();
        return true;
    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl; // Catch and print the exception
        return false;
    }
}


// Function to start the teacher's logic for the management system
bool TeacherLogic::startTeacherLogic(vector<User>& users, vector<Module>& modules) {
    UserManager userManager;
    string userId;
    string userPassword;
    string quit;
    string userInput;
    bool loggedIn = false; // Flag to indicate whether the user has logged in successfully
    while (!loggedIn) {
        cout << "Please enter your id: " << std::endl;
        getline(cin, userId);
        cout << "Please enter your password: " << std::endl;
        getline(cin, userPassword);
        const User& loggedInUser = userManager.login(users, userId, userPassword); // Calling the encapsulated login function


        // Checking if the user is a teacher and has successfully logged in
        if (loggedInUser.getUserName() != "" && loggedInUser.getUserCategory() == "teacher") {
            loggedIn = true; // User successfully logged in, set the flag to true
            system("cls");
            while (true) {
                string welcomeMessage = "Welcome " + loggedInUser.getUserName();
                StringHelper::printFormatted(welcomeMessage);
                cout << "\n1. Modify your information."
                    << "\n2. List teaching modules."
                    << "\n3. Enter and modify the student grades"
                    << "\n0. quit" << endl;
                StringHelper::delimiterLine();
                getline(cin, userInput);
                system("cls");
                if (userInput == "0") {
                    cout << "Exiting the system..." << endl;
                    exit(0);
                }
                else if (userInput == "1") {
                    // Modify user information based on the user's choice
                    string updateInput, address, phone;
                    StringHelper::delimiterLine();
                    cout << "username: " << loggedInUser.getUserName()
                        << "user phone: " << loggedInUser.getUserPhone()
                        << "user address: " << loggedInUser.getUserAddress() << endl;
                    StringHelper::delimiterLine();
                    cout << "Which information you want to update? \n1. Phone \n2. Address" << endl;
                    getline(cin, updateInput);
                    if (updateInput == "1") {
                        cout << "Please enter your new phone number: ";
                        getline(cin, phone);
                    }
                    else if (updateInput == "2") {
                        cout << "Please enter your new address: ";
                        getline(cin, address);
                    }
                    else { // Prompt the user to try again if the username or password is incorrect
                        cout << "Invalid Input. Please try again.\n ";
                        continue;
                    }
                    cout << "Please press S to save the change \n";
                    getline(cin, userInput);
                    if (userInput == "s" || userInput == "S") {
                        if (updateInput == "1") {
                            User updateUser(loggedInUser.getUserId(), loggedInUser.getUserName(), loggedInUser.getUserPassword(), loggedInUser.getUserCategory(), phone, loggedInUser.getUserAddress());
                            if (update(users, updateUser)) {
                                cout << "User information updated successfully." << endl;
                            }
                            else {
                                cout << "Failed to update user information." << endl;
                            }
                            cout << "Press B to go back to the previous menu" << endl;
                            getline(cin, userInput);
                            system("cls");
                            if (userInput == "b" || userInput == "B") {
                                continue;
                            }
                        }
                        else {
                            User updateUser(loggedInUser.getUserId(), loggedInUser.getUserName(), loggedInUser.getUserPassword(), loggedInUser.getUserCategory(), loggedInUser.getUserPhone(), address);
                            if (update(users, updateUser)) {
                                cout << "Updated successfully" << endl;
                                cout << "Press B to go back to the previous menu" << endl;
                                getline(cin, userInput);
                                system("cls");
                                if (userInput == "b" || userInput == "B") {
                                    continue;
                                }
                            }
                        }
                    }
                    else { // Prompt the user to try again if the username or password is incorrect
                        cout << "Invalid Input. Please try again.\nPress Q to quit, any other key to continue: ";
                        getline(cin, quit);
                        if (quit == "q" || quit == "Q") {
                            break;
                        }
                    }
                }
                else if (userInput == "2") {        // List teaching modules for the teacher
                    string user_id = loggedInUser.getUserId();
                    vector<Module> teachingModules;
                    for (const Module& module : modules) {
                        if (module.getTeacherId() == user_id) {
                            bool moduleExists = false;
                            for (const Module& existingModule : teachingModules) {
                                if (existingModule.getModuleId() == module.getModuleId()) {
                                    moduleExists = true;
                                    break;
                                }
                            }
                            if (!moduleExists) {
                                teachingModules.push_back(module);
                            }
                        }
                    }

                    StringHelper::printFormatted("Teaching Modules");
                    for (Module& module : teachingModules) {
                        StringHelper::printTeacherModule(modules, loggedInUser.getUserId());
                        //cout << " Module ID: " << module.getModuleId() << endl;
                        //cout << " Module Name: " << module.getModuleName() << endl;
                        StringHelper::delimiterLine();
                    }
                    cout << "Press any other key to go back to the previous menu" << endl;
                    getline(cin, userInput);
                    system("cls");
                    if (userInput == "b" || userInput == "B") {
                        continue; // 返回上一个页面
                    }
                }
                else if (userInput == "3") {// Display the teaching modules list with relevant information
                    StringHelper::printFormatted("Your Teaching Modules List");
                    cout << std::left << setw(15) << "Module Id"
                        << setw(20) << "Module Name"
                        << setw(15) << "Teacher Id"
                        << setw(20) << "Module Status"
                        << setw(20) << "Student Id"
                        << setw(20) << "Student Grade"
                        << endl;
                    StringHelper::delimiterLine();
                    for (const Module& module : modules) {
                        if (module.getTeacherId() == userId) {
                            cout << std::left << setw(15) << module.getModuleId()
                                << setw(20) << module.getModuleName()
                                << setw(15) << module.getTeacherId()
                                << setw(20) << module.getStatus()
                                << setw(20) << module.getStudentId()
                                << setw(30) << module.getStudentGrades()
                                << endl;
                        }

                    }
                    StringHelper::delimiterLine();// Add a delimiter after displaying the list
                    while (true) {
                        try {
                            // Prompt the user to select a module for grade modification
                            cout << "Please select a module to modify grades: " << endl;
                            string moduleId;
                            getline(cin, moduleId);
                            cout << "Enter student id: ";
                            string studentId;
                            getline(cin, studentId);
                            // Check if the selected module has released grades
                            bool foundReleasedModule = false;
                            for (Module& module : modules) {
                                if (module.getModuleId() == moduleId && module.getStudentId() == studentId && module.getStatus() == "Released") {
                                    cout << "Grades have already been published. You cannot modify student grades for this module." << endl;
                                    foundReleasedModule = true;
                                    break;
                                }
                            }

                            // If the module has released grades, let the user choose again
                            if (foundReleasedModule) {
                                continue;
                            }

                            // Find the module with the given module and student IDs

                            const Module& foundModule = findModule(modules, moduleId, studentId);
                            string newGrade;
                            bool isModuleIdCorrect = true; //  used to track whether the module ID is correct
                            if (foundModule.getModuleId() != moduleId) {
                                isModuleIdCorrect = false; // unmatched moduleid，false
                            }
                            if (foundModule.getModuleId() != "") {
                                cout << "Enter new grade: ";
                                getline(cin, newGrade);

                                // Checking if the input is a number
                                bool isNumber = true;
                                for (char c : newGrade) {
                                    if (!std::isdigit(c) && c != '.') { // allow to use decimal
                                        isNumber = false;
                                        break;
                                    }
                                }

                                if (!isNumber) {    // Check that the input is a valid numeric value
                                    cout << "Invalid input. Please enter a valid numeric value." << endl;
                                    continue;
                                }
                                system("cls");

                                // Output the corresponding message outside the exception handling block
                                if (!isModuleIdCorrect) {
                                    cout << "Invalid Module ID. Please enter a valid Module ID." << endl;
                                    continue; // Let the user choose again
                                }
                                else {
                                    // Creates an update module object with modified scores
                                    Module updatedModule(foundModule.getModuleId(), foundModule.getModuleName(), foundModule.getTeacherId(), foundModule.getStudentId(), newGrade, foundModule.getStatus());
                                    // Update student grades for selected modules
                                    if (updateStudentGrade(modules, updatedModule)) {
                                        // If the update is successful, a success message is displayed
                                        cout << "Updated successfully" << endl;
                                        cout << "Updated Module Information:" << endl;
                                        StringHelper::delimiterLine();
                                        cout << std::left << setw(15) << updatedModule.getModuleId()
                                            << setw(20) << updatedModule.getModuleName()
                                            << setw(15) << updatedModule.getTeacherId()
                                            << setw(20) << updatedModule.getStatus()
                                            << setw(20) << updatedModule.getStudentId()
                                            << setw(30) << updatedModule.getStudentGrades()
                                            << endl;
                                        StringHelper::delimiterLine();
                                        break;
                                    }
                                    else {  // If update false,output false information
                                        throw runtime_error("Failed to update student grades. Please check your input.");
                                    }
                                }
                            }
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Invalid argument: " << e.what() << endl;
                            // Code that handles invalid parameter exceptions
                        }
                        catch (const runtime_error& e) {
                            cerr << "Runtime error: " << e.what() << endl;
                            // Code that handles runtime errors
                        }
                        cout << "Press Q to quit, any other key to continue: ";
                        getline(cin, quit);
                        if (quit == "q" || quit == "Q") { // If the user input is q or Q, exit the program
                            break;
                        }
                    }
                }
                else { // Prompt the user to try again if the username or password is incorrect
                    cout << "Wrong username or password, please try again.\nPress Q to quit, any other key to continue: ";
                    getline(cin, quit);
                    if (quit == "q" || quit == "Q") {
                        break;
                    }
                }
            }
            return false;
        }
        else { // Prompt the user to try again if the username or password is incorrect
            cout << "Wrong username or password, please try again. \nPress any key for retry Q for quit";
            getline(cin, quit);
            if (quit == "q" || quit == "Q") {
                break;
            }
            continue;
        }
    }
}