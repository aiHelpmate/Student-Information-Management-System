# Student Information Management System

## Overview

This project is a comprehensive Student Information Management System developed in C++. It integrates user management, module management, and grade tracking functionalities, providing a robust platform for both students and staff to manage and interact with academic data effectively. 

## Features

- **User Management**: 
  - Allows for the registration and management of users, including students and staff.
  - Supports login functionality with secure password handling.

- **Module Management**:
  - Users can view, add, update, and delete course modules.
  - Modules can be associated with teachers and students, facilitating a clear structure for educational content.

- **Grade Tracking**:
  - Teachers can publish and modify student grades.
  - Students can view their grades and associated modules.

- **Flexible User Interface**:
  - Console-based UI that guides users through various functionalities.
  - Clear prompts and structured outputs for user interactions.

## Technologies Used

- **C++**: The core programming language used for implementing the system, showcasing proficiency in object-oriented programming.
- **File I/O**: Utilizes file handling to store and retrieve user and module data.
- **Standard Template Library (STL)**: Employs vectors and other STL components for efficient data management.

## Code Structure

- **User.h / User.cpp**: Defines the `User` class and its functionalities, including user management and data handling.
- **Module.h / Module.cpp**: Implements the `Module` class, encapsulating module-related data and operations.
- **Utils.h / Utils.cpp**: Provides utility functions for loading user and module data from files and processing strings.
- **StudentLogic.h / StudentLogic.cpp**: Contains the logic specific to student interactions, including menu navigation and grade management.
- **TeacherLogic.h / TeacherLogic.cpp**: Manages the functionalities available to teachers, such as updating grades and module information.
- **StaffLogic.h / StaffLogic.cpp**: Facilitates staff operations for managing users and modules.
- **StringHelper.h / StringHelper.cpp**: Offers formatting and display functions to enhance console output readability.

## Getting Started

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/Student-Information-Management-System.git
   ```

2. **Compile the Code**:
   Use a C++ compiler to compile the code files.
   ```bash
   g++ main.cpp User.cpp Module.cpp StaffLogic.cpp StudentLogic.cpp TeacherLogic.cpp Utils.cpp StringHelper.cpp -o StudentManagementSystem
   ```

3. **Run the Program**:
   Execute the compiled program.
   ```bash
   ./StudentManagementSystem
   ```

## Conclusion

This Student Information Management System demonstrates my ability to design and implement a structured C++ application, utilizing object-oriented principles and efficient data management techniques. The project reflects my proficiency in C++ programming, problem-solving skills, and commitment to creating user-friendly applications.

For further inquiries or contributions, feel free to reach out or create a pull request. Thank you for exploring my project!
