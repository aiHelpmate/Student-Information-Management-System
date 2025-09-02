# Information Management System

## Overview

This project is a comprehensive Student Information Management System developed in C++. It integrates user management, module management, and grade tracking functionalities, providing a robust platform for both students and staff to manage and interact with academic data effectively. 

## Functions

1. **Students object**:
   - Students can securely log in using their username and password through the login interface.
   - Students can update their personal information, including phone number and address, by navigating to the profile settings.
   - On their personal homepage, students can view a comprehensive list of all available elective modules.
   - Students can select a specific module to view their final grade for that module.

2. **Teachers object**:
   - Teachers can log in to the system using their account and password on the login interface.
   - Teachers can modify their phone number and address by selecting personal information.
   - Teachers can view a list of all modules they are teaching on their personal homepage.
   - Teachers can select a module to enter and modify students’ grades. Once grades are published, they cannot be modified for that module.

3. **Staff object**:
   - Staff can log in to the system using their account and password on the login interface.
   - Staff can add, modify, and delete information in the user table, including personal information about staff, students, and teachers.
   - Staff can add, modify, and delete module information in the module table, including module ID, module name, user name, category, and grades.
   - Staff can publish or retrieve module grades on the module interface.

## Code Structure

- **User.h / User.cpp**: Defines the `User` class and its functionalities, including user management and data handling.
- **Module.h / Module.cpp**: Implements the `Module` class, encapsulating module-related data and operations.
- **Utils.h / Utils.cpp**: Provides utility functions for loading user and module data from files and processing strings.
- **StudentLogic.h / StudentLogic.cpp**: Contains the logic specific to student interactions, including menu navigation and grade management.
- **TeacherLogic.h / TeacherLogic.cpp**: Manages the functionalities available to teachers, such as updating grades and module information.
- **StaffLogic.h / StaffLogic.cpp**: Facilitates staff operations for managing users and modules.
- **StringHelper.h / StringHelper.cpp**: Offers formatting and display functions to enhance console output readability.

## Conclusion

This Student Information Management System represents a methodologically rigorous implementation of object-oriented programming principles within the C++ paradigm, demonstrating effective application of structured software engineering practices for educational data management. For further inquiries or contributions, feel free to reach out or create a pull request. Thank you for exploring my project!
