#ifndef ASSIGNMENT_USER_H
#define ASSIGNMENT_USER_H

#include <vector>
#include <string>
using namespace std;

class User {
private:
    string user_id;
    std::string user_name;
    std::string user_password;
    std::string user_category;
    std::string user_phone;
    std::string user_address;

public:
    User(string id, std::string name, std::string password, const std::string& category, const std::string& phone, std::string address);

    string getUserId() const;
    string getUserName() const;
    string getUserPassword() const;
    string getUserCategory() const;
    string getUserPhone() const;
    string getUserAddress() const;
};

class UserManager {
public:
    User login(const std::vector<User>& users, const std::string& userName, const std::string& userPassword);
    bool update(std::vector<User>& users, const User& user);
    // Add additional member functions and member variables
};

#endif //ASSIGNMENT_USER_H
