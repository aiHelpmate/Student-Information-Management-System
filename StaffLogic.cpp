#include "StaffLogic.h"
#include "User.h"
#include "Module.h"
#include "StringHelper.h"
#include <cstdlib>
#include "User.h"


// Update the information
bool updateUser(vector<User>& users, const User& user) {
    for (User& existingUser : users) {
        if (existingUser.getUserId() == user.getUserId()) {
            // Update the user's information with the new user data
            existingUser = user;
            break;
        }
    }

    ofstream outFile("database/User.txt");
    if (!outFile) {
        cerr << "Error: Unable to open User.txt for writing." << endl;
        return false; // Failed to open the file
    }

    for (const User& u : users) {
        outFile << u.getUserId() << "," << u.getUserName() << ","
            << u.getUserPassword() << "," << u.getUserCategory() << ","
            << u.getUserPhone() << "," << u.getUserAddress() << "\n";
    }

    outFile.close();

    return true;
}

bool updateModule(vector<Module>& modules, const Module& module) {
    for (Module& existingModule : modules) {
        if (existingModule.getModuleId() == module.getModuleId()) {
            // Update the module's information with the new module data
            existingModule = module;
            break;
        }
    }

    ofstream outFile("database/Module.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open Module.txt for writing." << endl;
        return false; // Failed to open the file
    }

    for (const Module& m : modules) {
        outFile << m.getModuleId() << "," << m.getModuleName() << ","
            << m.getTeacherId() << "," << m.getStudentId() << ","
            << m.getStudentGrades() << "," << m.getStatus() << "\n";
    }

    outFile.close();

    return true;
}


// Delete all information
bool deleteUserById(vector<User>& users, const string& id) {
    // Find the users you want to delete in the Users container
    auto it = find_if(users.begin(), users.end(), [&](const User& user) {
        return user.getUserId() == id;
        });

    if (it != users.end()) {
        // Locate the user and delete it
        users.erase(it);
        return true;
    }

    return false; // User not found
}

bool deleteModule(vector<Module>& modules, const string& moduleId, const string& teacherId, const string& studentId) {
    // Find the modules to delete in the modules container
    auto it = remove_if(modules.begin(), modules.end(), [&](const Module& module) {
        return (module.getModuleId() == moduleId) &&
            (module.getTeacherId() == teacherId) &&
            (module.getStudentId() == studentId);
        });

    if (it != modules.end()) {
        // Locate the module and delete it
        modules.erase(it, modules.end());
        return true;
    }

    return false; // Module not found
}


// Publishes the module score function
void updateModuleStatus(const string& moduleId, const string& teacherId) {
    // Open the module information file
    ifstream inputFile("database/Module.txt");
    ofstream outputFile("database/Module_tmp.txt");

    string line;

    // Flags whether a matching record was found
    bool found = false;

    // Walk through each line in the file
    while (getline(inputFile, line)) {
        // Each row of data is parsed using a string stream
        stringstream ss(line);
        string currentModuleId, currentModuleName, currentTeacherId, currentStudentId, currentGrades, currentStatus;

        // Extract module ID, module name, teacher ID, student ID, grade, and status from the current row
        if (getline(ss, currentModuleId, ',') &&
            getline(ss, currentModuleName, ',') &&
            getline(ss, currentTeacherId, ',') &&
            getline(ss, currentStudentId, ',') &&
            getline(ss, currentGrades, ',') &&
            getline(ss, currentStatus)) {

            // Check that the target module ID and teacher ID match
            if (currentModuleId == moduleId && currentTeacherId == teacherId) {
                // Update the status to "Released"
                currentStatus = "Released";
                found = true;
            }

            // Write data to a new file
            outputFile << currentModuleId << ',' << currentModuleName << ',' << currentTeacherId << ',' << currentStudentId << ',' << currentGrades << ',' << currentStatus << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    // Delete original file
    remove("database/Module.txt");

    // Rename the new file to the original file
    rename("database/Module_tmp.txt", "database/Module.txt");

    // Output prompt message
    if (found) {
        cout << "Module status updated successfully for Module ID: " << moduleId << ", Teacher ID: " << teacherId << endl;
    }
    else {
        cout << "No matching record found for Module ID: " << moduleId << ", Teacher ID: " << teacherId << endl;
    }
}


// Retrieves the module score function
vector<pair<string, double>> retrieveModuleGrades(const string& moduleId, const string& teacherId) {
    vector<pair<string, double>> moduleGrades;

    // Open the module information file
    ifstream file("database/Module.txt");
    string line;

    // Walk through each line in the file
    while (getline(file, line)) {
        // Each row of data is parsed using a string stream
        stringstream ss(line);
        string currentModuleId, currentModuleName, currentTeacherId, currentStudentId, currentGrades, currentStatus;

        // Extract module ID, module name, teacher ID, student ID, grade, and status from the current row
        if (getline(ss, currentModuleId, ',') &&
            getline(ss, currentModuleName, ',') &&
            getline(ss, currentTeacherId, ',') &&
            getline(ss, currentStudentId, ',') &&
            getline(ss, currentGrades, ',') &&
            getline(ss, currentStatus)) {

            // Check that the target module ID and teacher ID match and the status is not "Not Released"
            if (currentModuleId == moduleId && currentTeacherId == teacherId && currentStatus != "Not Released") {
                // Add the student ID and grade to the result vector
                double grades = stod(currentGrades);
                moduleGrades.push_back(make_pair(currentStudentId, grades));
            }
        }
    }

    file.close();

    return moduleGrades;
}

bool StaffLogic::startStaffLogic(vector<User>& users, vector<Module>& modules) {
    UserManager userManager;
    string userId;
    string userPassword;
    string quit;
    string userInput;
    bool loggedIn = false; // Indicates whether the user has successfully logged in

    while (!loggedIn) {
        cout << "Please enter your id: " << std::endl;
        getline(cin, userId);
        cout << "Please enter your password: " << std::endl;
        getline(cin, userPassword);
        const User& loggedInUser = userManager.login(users, userId, userPassword);
        if (loggedInUser.getUserName() != "" && loggedInUser.getUserCategory() == "staff") {
            loggedIn = true; // The user successfully logged in. Set the flag to true
            system("cls");
            while (true) {
                string welcomeMessage = "Welcome " + loggedInUser.getUserName();
                StringHelper::printFormatted(welcomeMessage);
                cout << "\n1. Manage the information in user table.";
                cout << "\n2. Manage module information in the module table.";
                cout << "\n3. Publish or retrieve module grades on the module interface.";
                cout << "\n0. quit" << std::endl;
                StringHelper::delimiterLine();
                getline(cin, userInput);

                if (userInput == "0") {
                    //clear screen
                    system("cls");
                    cout << "Exiting the system..." << endl;
                    exit(0); // This will exit the program
                    //clear screen
                    system("cls");
                }
                if (userInput == "1") {
                    //clear screen
                    system("cls");
                    string updateInput;
                    string id;
                    string name;
                    string password;
                    string category;
                    string phone;
                    string address;

                    // Print the entire contents of User.txt
                    ifstream inFile("database/User.txt");
                    if (!inFile) {
                        std::cerr << "Error: Unable to open User.txt for reading." << std::endl;
                        return 0; // Failed to open the file
                    }

                    string line;
                    while (getline(inFile, line)) {
                        cout << line << endl;
                    }
                    inFile.close();


                    cout << "\nSelect the content to manage. \n1. Modify Id \n2. Modify Name \n3. Modify Password \n4. Modify Category \n5. Modify Phone \n6. Modify Address \n7. Modify user" << std::endl;
                    getline(cin, updateInput);
                    string newId;
                    string newName;
                    string newPassword;
                    string newCategory;
                    string newPhone;
                    string newAddress;
                    string userChoice;


                    if (updateInput == "1") {
                        cout << "Please enter the id you want to change: " << endl;
                        getline(cin, id);

                        cout << "Please enter a new id: " << endl;
                        getline(cin, newId);
                    }
                    else if (updateInput == "2") {
                        cout << "Please enter the name you want to change: " << endl;
                        getline(cin, name);

                        cout << "Please enter a new name: " << endl;
                        getline(cin, newName);
                    }
                    else if (updateInput == "3") {
                        cout << "Please enter the password you want to change: " << endl;
                        getline(cin, password);

                        cout << "Please enter a new password: " << endl;
                        getline(cin, newPassword);
                    }
                    else if (updateInput == "4") {
                        cout << "Please enter the category you want to change: " << endl;
                        getline(cin, category);

                        cout << "Please enter a new category: " << endl;
                        getline(cin, newCategory);
                    }
                    else if (updateInput == "5") {
                        cout << "Please enter the phone you want to change: " << endl;
                        getline(cin, phone);

                        cout << "Please enter a new phone: " << endl;
                        getline(cin, newPhone);
                    }
                    else if (updateInput == "6") {
                        cout << "Please enter the address you want to change: " << endl;
                        getline(cin, address);

                        cout << "Please enter a new address: " << endl;
                        getline(cin, newAddress);
                    }
                    else if (updateInput == "7") {
                        cout << "Please select add or delete. \n1. Add user \n2. Delete user " << endl;
                        getline(cin, userChoice);

                        if (userChoice == "1") {
                            cout << "Please enter the following information:" << endl;
                            cout << "Name: ";
                            getline(cin, name);
                            cout << "Password: ";
                            getline(cin, password);
                            cout << "Category: ";
                            getline(cin, category);
                            cout << "Phone: ";
                            getline(cin, phone);
                            cout << "Address: ";
                            getline(cin, address);

                            // Generate a unique ID
                            bool idExists = true;
                            while (idExists) {
                                cout << "ID: ";
                                getline(cin, newId);

                                // Check whether the new ID already exists
                                idExists = false;
                                for (const User& user : users) {
                                    if (user.getUserId() == newId) {
                                        idExists = true;
                                        break;
                                    }
                                }

                                if (idExists) {
                                    cout << "ID " << newId << " already exists. Please choose a different ID." << endl;
                                }
                            }

                        }
                        else if (userChoice == "2") {
                            cout << "Please enter an id to delete: ";
                            getline(cin, id);
                            bool deleteResultId = deleteUserById(users, id); // Call the delete function and get the result

                            if (deleteResultId) {
                                cout << "User with ID " << id << " has been deleted." << endl;
                            }
                            else {
                                cout << "User with ID " << id << " not found." << endl;
                            }

                        }
                    }

                    cout << "Please press S to save the change" << endl;
                    getline(cin, userInput);


                    if (userInput == "s" || userInput == "S") {

                        if (updateInput == "1") {
                            // Update the user's ID in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserId() == id) {
                                    user = User(newId, user.getUserName(), user.getUserPassword(),
                                        user.getUserCategory(), user.getUserPhone(), user.getUserAddress());
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with id: " << id << endl;
                            }
                            else {
                                cout << "ID updated successfully." << endl;


                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;

                            }
                        }
                        else if (updateInput == "2") {
                            // Update the user's name in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserName() == name) {
                                    user = User(user.getUserId(), newName, user.getUserPassword(),
                                        user.getUserCategory(), user.getUserPhone(), user.getUserAddress());
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with name: " << name << endl;
                            }
                            else {
                                cout << "Name updated successfully." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInput == "3") {
                            // Update the user's password in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserPassword() == password) {
                                    user = User(user.getUserId(), user.getUserName(), newPassword,
                                        user.getUserCategory(), user.getUserPhone(), user.getUserAddress());
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with password: " << password << endl;
                            }
                            else {
                                cout << "Password updated successfully." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInput == "4") {
                            // Update the user's category in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserCategory() == category) {
                                    user = User(user.getUserId(), user.getUserName(), user.getUserPassword(),
                                        newCategory, user.getUserPhone(), user.getUserAddress());
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with category: " << id << endl;
                            }
                            else {
                                cout << "Category updated successfully." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInput == "5") {
                            // Update the user's phone in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserPhone() == phone) {
                                    user = User(user.getUserId(), user.getUserName(), user.getUserPassword(),
                                        user.getUserCategory(), newPhone, user.getUserAddress());
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with phone: " << id << endl;
                            }
                            else {
                                cout << "Phone updated successfully." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInput == "6") {
                            // Update the user's address in the users vector
                            bool found = false;
                            for (User& user : users) {
                                if (user.getUserAddress() == address) {
                                    user = User(user.getUserId(), user.getUserName(), user.getUserPassword(),
                                        user.getUserCategory(), user.getUserPhone(), newAddress);
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                cout << "User not found with address: " << id << endl;
                            }
                            else {
                                cout << "Address updated successfully." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInput == "7") {
                            if (userChoice == "1") {
                                // Create a new user and add it to the user table
                                User newUser(newId, name, password, category, phone, address);
                                users.push_back(newUser);

                                cout << "New user with ID " << newId << " has been added." << endl;

                                // Update the User.txt file
                                ofstream outFile("database/User.txt", ios::app); // Append mode
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                // Append the new user to the file
                                outFile << newUser.getUserId() << "," << newUser.getUserName() << "," << newUser.getUserPassword()
                                    << "," << newUser.getUserCategory() << "," << newUser.getUserPhone() << "," << newUser.getUserAddress() << endl;

                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;

                            }
                            else if (userChoice == "2") {
                                // Update the User.txt file
                                ofstream outFile("database/User.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open User.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const User& user : users) {
                                    outFile << user.getUserId() << "," << user.getUserName() << "," << user.getUserPassword()
                                        << "," << user.getUserCategory() << "," << user.getUserPhone() << "," << user.getUserAddress() << endl;
                                }
                                outFile.close();

                                cout << "User.txt file updated successfully." << endl;

                            }
                        }
                    }
                }
                else if (userInput == "2") {
                    //clear screen
                    system("cls");
                    string updateInfo;
                    string moduleId;
                    string moduleName;
                    string teacherId;
                    string studentId;
                    string grades;
                    string moduleStatus;

                    // Print the entire contents of Module.txt
                    ifstream inFile("database/Module.txt");
                    if (!inFile) {
                        cerr << "Error: Unable to open Module.txt for reading." << endl;
                        return 0; // Failed to open the file
                    }

                    string line;
                    while (getline(inFile, line)) {
                        cout << line << endl;
                    }
                    inFile.close();


                    cout << "\nSelect the content to manage. \n1. Modify Module Id \n2. Modify Module Name \n3. Modify Teacher Id \n4. Modify Student Id \n5. Modify Grades \n6. Modify Module Information" << std::endl;
                    getline(cin, updateInfo);
                    string newModuleId;
                    string newModuleName;
                    string newTeacherId;
                    string newStudentId;
                    string newGrades;
                    string moduleChoice;

                    if (updateInfo == "1") {
                        cout << "Please enter the module id you want to change: " << endl;
                        getline(cin, moduleId);

                        cout << "Please enter a new module id: " << endl;
                        getline(cin, newModuleId);
                    }
                    else if (updateInfo == "2") {
                        cout << "Please enter the module name you want to change: " << endl;
                        getline(cin, moduleName);

                        cout << "Please enter a new module name: " << endl;
                        getline(cin, newModuleName);
                    }
                    else if (updateInfo == "3") {
                        cout << "Please enter the teacher id you want to change: " << endl;
                        getline(cin, teacherId);

                        cout << "Please enter a new teacher id: " << endl;
                        getline(cin, newTeacherId);
                    }
                    else if (updateInfo == "4") {
                        cout << "Please enter the student id you want to change: " << endl;
                        getline(cin, studentId);

                        cout << "Please enter a new student id: " << endl;
                        getline(cin, newStudentId);
                    }
                    else if (updateInfo == "5") {
                        cout << "Please enter the grade you want to change: " << endl;
                        getline(cin, grades);

                        cout << "Please enter a new grade: " << endl;
                        getline(cin, newGrades);
                    }
                    else if (updateInfo == "6") {
                        cout << "Please select add or delete. \n1. Add module \n2. Delete module " << endl;
                        getline(cin, moduleChoice);

                        if (moduleChoice == "1") {
                            cout << "Please enter the following information:" << endl;
                            cout << "Module Name: ";
                            getline(cin, moduleName);
                            cout << "Teacher ID: ";
                            getline(cin, teacherId);
                            cout << "Student ID: ";
                            getline(cin, studentId);
                            cout << "Grades: ";
                            getline(cin, grades);
                            cout << "Status: ";
                            getline(cin, moduleStatus);

                            // Generate a unique ID
                            bool idExists = true;
                            while (idExists) {
                                cout << "ID: ";
                                getline(cin, newModuleId);

                                // Check whether the new ID already exists
                                idExists = false;
                                for (const Module& module : modules) {
                                    if (module.getModuleId() == newModuleId) {
                                        idExists = true;
                                        break;
                                    }
                                }

                                if (idExists) {
                                    cout << "ID " << newModuleId << " already exists. Please choose a different ID." << endl;
                                }
                            }

                        }
                        else if (moduleChoice == "2") {
                            cout << "Please enter the moduleId: ";
                            string moduleId;
                            getline(cin, moduleId);

                            cout << "Please enter the teacherId: ";
                            string teacherId;
                            getline(cin, teacherId);

                            cout << "Please enter the studentId: ";
                            string studentId;
                            getline(cin, studentId);

                            bool deleteResult = deleteModule(modules, moduleId, teacherId, studentId); // Call the delete function and get the result

                            if (deleteResult) {
                                cout << "Module: " << moduleId << " " << teacherId << " " << studentId << " has been deleted." << endl;
                            }
                            else {
                                cout << "Module: " << moduleId << " " << teacherId << " " << studentId << " not found." << endl;
                            }

                        }
                    }


                    cout << "Please press S to save the change" << endl;
                    getline(cin, userInput);

                    if (userInput == "s" || userInput == "S") {
                        if (updateInfo == "1") {
                            // Update the module's ID in the modules vector
                            bool found = false;
                            for (Module& module : modules) {
                                if (module.getModuleId() == moduleId) {
                                    module = Module(newModuleId, module.getModuleName(), module.getTeacherId(),
                                        module.getStudentId(), module.getStudentGrades(), module.getStatus());
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "No modules found with module id: " << moduleId << endl;
                            }
                            else {
                                cout << "Module IDs updated successfully." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInfo == "2") {
                            // Update the module's name in the modules vector
                            bool found = false;
                            for (Module& module : modules) {
                                if (module.getModuleName() == moduleName) {
                                    module = Module(module.getModuleId(), newModuleName, module.getTeacherId(),
                                        module.getStudentId(), module.getStudentGrades(), module.getStatus());
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "No modules found with module name: " << moduleId << endl;
                            }
                            else {
                                cout << "Module name updated successfully." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInfo == "3") {
                            // Update the teacher's id in the modules vector
                            bool found = false;
                            for (Module& module : modules) {
                                if (module.getTeacherId() == teacherId) {
                                    module = Module(module.getModuleId(), module.getModuleName(), newTeacherId,
                                        module.getStudentId(), module.getStudentGrades(), module.getStatus());
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "No modules found with teacher id: " << teacherId << endl;
                            }
                            else {
                                cout << "Teacher id updated successfully." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInfo == "4") {
                            // Update the student id in the modules vector
                            bool found = false;
                            for (Module& module : modules) {
                                if (module.getStudentId() == studentId) {
                                    module = Module(module.getModuleId(), module.getModuleName(), module.getTeacherId(),
                                        newStudentId, module.getStudentGrades(), module.getStatus());
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "No modules found with student ID: " << studentId << endl;
                            }
                            else {
                                cout << "Student ID updated successfully." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInfo == "5") {
                            // Update the grades in the modules vector
                            bool found = false;
                            for (Module& module : modules) {
                                if (module.getStudentGrades() == grades) {
                                    module = Module(module.getModuleId(), module.getModuleName(), module.getTeacherId(),
                                        module.getStudentId(), newGrades, module.getStatus());
                                    found = true;
                                }
                            }

                            if (!found) {
                                cout << "No modules found with grades: " << grades << endl;
                            }
                            else {
                                cout << "Grades updated successfully." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;
                            }
                        }
                        else if (updateInfo == "6") {

                            if (moduleChoice == "1") {
                                // Create a new module and add it to the module table
                                Module newModule(newModuleId, moduleName, teacherId, studentId, grades, moduleStatus);
                                modules.push_back(newModule);

                                cout << "New module with ID " << newModuleId << " has been added." << endl;

                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt", ios::app); // Append mode
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                // Append the new module to the file
                                outFile << newModule.getModuleId() << "," << newModule.getModuleName() << "," << newModule.getTeacherId()
                                    << "," << newModule.getStudentId() << "," << newModule.getStudentGrades() << "," << newModule.getStatus() << endl;

                                outFile.close();

                                cout << "module.txt file updated successfully." << endl;


                            }
                            else if (moduleChoice == "2") {
                                // Update the Module.txt file
                                ofstream outFile("database/Module.txt");
                                if (!outFile) {
                                    cerr << "Error: Unable to open Module.txt for writing." << endl;
                                    return false; // Failed to open the file
                                }

                                for (const Module& module : modules) {
                                    outFile << module.getModuleId() << "," << module.getModuleName() << "," << module.getTeacherId()
                                        << "," << module.getStudentId() << "," << module.getStudentGrades() << "," << module.getStatus() << endl;
                                }
                                outFile.close();

                                cout << "Module.txt file updated successfully." << endl;

                            }
                        }

                    }
                }
                else if (userInput == "3") {
                    //clear screen
                    system("cls");
                    StringHelper::delimiterLine();
                    cout << "1. Publish module grades" << endl;
                    cout << "2. Retrieve module grades" << endl;
                    StringHelper::delimiterLine();

                    string moduleId;
                    string teacherId;
                    string studentId;

                    cout << "Enter your choice: " << endl;
                    cin >> userInput;

                    if (userInput == "1") {

                        string moduleId;
                        string teacherId;

                        cout << "Enter module ID: " << endl;
                        cin >> moduleId;
                        cout << "Enter teacher ID: " << endl;
                        cin >> teacherId;

                        // Calls the function that updates the status of the module
                        updateModuleStatus(moduleId, teacherId);

                    }
                    else if (userInput == "2") {
                        string moduleId;
                        string teacherId;

                        cout << "Enter module ID: " << endl;
                        cin >> moduleId;
                        cout << "Enter teacher ID: " << endl;
                        cin >> teacherId;

                        // Calls a function that retrieves module grades
                        vector<pair<string, double>> retrievedGrades = retrieveModuleGrades(moduleId, teacherId);

                        // Output the retrieved results
                        if (retrievedGrades.empty()) {
                            cout << "No matching records found for Module ID: " << moduleId << ", Teacher ID: " << teacherId << endl;
                        }
                        else {
                            cout << "Retrieved grades:" << endl;
                            for (const auto& grade : retrievedGrades) {
                                cout << "Student ID: " << grade.first << ", Grades: " << grade.second << endl;
                            }
                        }
                    }
                    else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
        }
        else {
             cout << "Wrong username or password, please try again. \nPress any key for retry Q for quit";
             getline(cin, quit);
             if (quit == "q" || quit == "Q") {
                 break;
             }
             continue;
        }
    }
        return false;
}