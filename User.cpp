#include "User.h"
#include <iostream>
#include <string>
#include <utility>
using namespace std;
#include <vector>
#include <fstream>


User::User(string id, string name, string password, const string& category, const string& phone,
    string address)
    : user_id(std::move(id)), user_name(std::move(name)), user_password(std::move(password)), user_category(category), user_phone(phone), user_address(std::move(address)) {
}


// Getter method to access user ID
string User::getUserId() const {
    return user_id;
}

// Getter method to access username
std::string User::getUserName() const {
    return user_name;
}

// Getter method to access user password
std::string User::getUserPassword() const {
    return user_password;
}

// Getter method to access user category
std::string User::getUserCategory() const {
    return user_category;
}

// Getter method to access user phone number
std::string User::getUserPhone() const {
    return user_phone;
}

// Getter method to access user address
std::string User::getUserAddress() const {
    return user_address;
}

User UserManager::login(const std::vector<User>& users, const std::string& userName, const std::string& userPassword) {
    for (const User& user : users) {
        if (user.getUserId() == userName && user.getUserPassword() == userPassword) {
            return user;
        }
    }
    return User("", "", "", "", "", ""); // Return a default user when no match is found
}

bool UserManager::update(std::vector<User>& users, const User& user)
{
    for (User& existingUser : users) {
        if (existingUser.getUserId() == user.getUserId()) {
            existingUser = user; // Update user information
            break;
        }
    }

    ofstream outFile("database/User.txt");
    if (!outFile) {
        cerr << "Error: Unable to open user.txt for writing." << endl;
        return false; // Unable to open file
    }

    for (const User& user : users) {
        outFile << user.getUserId() << "," << user.getUserName() << ","
            << user.getUserPassword() << "," << user.getUserCategory() << ","
            << user.getUserPhone() << "," << user.getUserAddress() << "\n";
    }

    outFile.close();

    return true;
}

