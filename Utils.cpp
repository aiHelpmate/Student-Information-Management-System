#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Utils.h"
using namespace std;

vector<User> Utils::loadUserData(const string& filename) {
    vector<User> userList; // Vector to store User objects
    string line;
    fstream inFile;
    inFile.open(filename, ios::in);


    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            // Split the line by commas
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // Check if there are enough tokens
            if (tokens.size() == 6) {
                // Create a User object and add it to the list
                User user(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
                userList.push_back(user);
            }
        }

        inFile.close(); // Close the file
    }
    else {
        cout << "Unable to open the file." << endl;
    }

    return userList;
}

vector<Module> Utils::loadModuleData(const string& filename) {
    vector<Module> moduleList; // Vector to store Module objects
    string line;

    ifstream inputFile(filename); // Open the file

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            // Split the line by commas
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            // Check if there are enough tokens
            if (tokens.size() == 6) {
                // Convert the student grades to double

                // Create a Module object and add it to the list
                Module module(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
                moduleList.push_back(module);
            }
        }

        inputFile.close(); // Close the file
    }
    else {
        cout << "Unable to open the file." << endl;
    }

    return moduleList;
}

string Utils::removeSpaces(const string& str) {
    string result;
    for (char ch : str) {
        if (!isspace(ch)) {
            result += ch;
        }
    }
    return result;
}
