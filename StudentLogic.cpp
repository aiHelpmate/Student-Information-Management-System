#include "StudentLogic.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "StringHelper.h"
#include "User.h" 
using namespace std;

UserManager userManager;


bool update(vector<User>& users, const User& user) {
    for (User& existingUser : users) { // Note the "&" for reference
        if (existingUser.getUserId() == user.getUserId()) {
            // Update the user's information with the new user data
            existingUser = user;
            break;
        }
    }
    ofstream outFile("database/User.txt");
    if (!outFile) {
        cerr << "Error: Unable to open user.txt for writing." << endl;
        return false; // Failed to open the file
    }

    for (const User& user : users) {
        outFile << user.getUserId() << "," << user.getUserName() << ","
            << user.getUserPassword() << "," << user.getUserCategory() << ","
            << user.getUserPhone() << "," << user.getUserAddress() << "\n";
    }

    outFile.close();


    return true;
}

void StudentLogic::StudentMenu(vector<User>& users, User& curUser, const vector<Module>& modules)
{
    string userInput;
    while (true)
    {
        string welcomeMessage = "Welcome " + curUser.getUserName();
        StringHelper::printFormatted(welcomeMessage);
        cout << "\n1. Modify your information.";
        cout << "\n2. List elective modules.";
        cout << "\n3. view your grade";
        cout << "\n0. quit" << std::endl;
        StringHelper::delimiterLine();
        getline(cin, userInput);

        if (userInput == "0") {
            cout << "Exiting the system..." << endl;
            exit(0); // This will exit the program
        }
        else if (userInput == "1") {
            system("cls");
            string updateInput;
            string address;
            string phone;
            cout << "username: " << curUser.getUserName()
                << "\nuser phone: " << curUser.getUserPhone()
                << "\nuser address: " << curUser.getUserAddress() << std::endl;

            cout << "Which information you want to update? \n1. Phone \n2. Address" << std::endl;
            getline(cin, updateInput);
            if (updateInput == "1") {
                cout << "Please enter your new phone number: ";
                getline(cin, phone);
            }
            else if (updateInput == "2") {
                system("cls");
                cout << "Please enter your new address: ";
                getline(cin, address);
            }
            else
            {
                cout << "Invalid choice!" << endl;
                continue;
            }
            cout << "Please press S to save the change";
            getline(cin, userInput);
            if (userInput == "s" || userInput == "S") {
                if (updateInput == "1") {
                    curUser = User(curUser.getUserId(), curUser.getUserName(), curUser.getUserPassword()
                        , curUser.getUserCategory(), phone, curUser.getUserAddress());
                    if (update(users, curUser)) {
                        cout << "Updated successfully\n";
                    }
                }
                else {
                    curUser = User(curUser.getUserId(), curUser.getUserName(), curUser.getUserPassword()
                        , curUser.getUserCategory(), curUser.getUserPhone(),
                        address);
                    if (update(users, curUser)) {
                        cout << "Updated successfully\n";
                    }
                }

            }
        }
        else if (userInput == "2")
        {
            system("cls");
            StringHelper::printFormatted("Elective Modules");
            StringHelper::printStudentModule(modules, curUser.getUserId());
            StringHelper::delimiterLine();
            break;

        }
        else if (userInput == "3")
        {
            system("cls");
            bool find = false;
            cout << "All elective modules id lists:" << endl;
            for (size_t i = 0; i < modules.size(); i++)
            {
                if (modules[i].getStudentId() == curUser.getUserId())
                {
                    cout << modules[i].getModuleId() << endl;
                }
            }
            cout << "Plese input your module id choice: ";
            getline(cin, userInput);
            for (size_t i = 0; i < modules.size(); i++)
            {
                if (modules[i].getStudentId() == curUser.getUserId() && modules[i].getModuleId() == userInput && modules[i].getStatus() == "Released")
                {
                    cout << "Your module grade: " << modules[i].getStudentGrades() << endl;
                    find = true;
                }
                else if (modules[i].getStudentId() == curUser.getUserId() && modules[i].getModuleId() == userInput && modules[i].getStatus() != "Released")
                {
                    cout << "Your module grade: Not Released" << endl;
                    find = true;
                    system("cls");
                }
            }
            if (!find)
            {
                cout << "invalid module" << endl;
            }
            cout << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}


bool StudentLogic::startStudentLogic(vector<User>& users, const vector<Module>& modules) {
    string userName;
    string userPassword;
    string quit;
    string userInput;
    while (true) {
        cout << "Please enter your id: " << std::endl;
        getline(cin, userName);
        cout << "Please enter your password: " << std::endl;
        getline(cin, userPassword);

        // Calls the wrapped login function
        User loggedInUser = userManager.login(users, userName, userPassword);
        
        //student login
        if (loggedInUser.getUserName() != "" && loggedInUser.getUserCategory() == "student") {
            system("cls");

            StudentMenu(users, loggedInUser, modules);
           
            // Call the wrapped update function
            if (userManager.update(users, loggedInUser)) {
                cout << "User information updated successfully." << endl;
                
            }
            else {
                cout << "Failed to update user information." << endl;
            }
            continue;
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
