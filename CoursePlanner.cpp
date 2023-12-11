//============================================================================
// Name        : CoursePlanner.cpp
// Date        : 12/4/2023
// Author      : Levi Winters
//============================================================================

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course() = default;
    
    // Constructor with parameters for Course class
    Course(string courseNumber, string name) : courseNumber(courseNumber), name(name) {}
};

map<string, Course> courseTable;

// Function to load courses from a file
void loadCourses(const string& inputFile) {
    ifstream file(inputFile);
    if (!file.is_open()) {
        cout << "Error opening file: " << inputFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, name, prerequisite;

        // Extract courseNumber and name from the input line
        getline(ss, courseNumber, ',');
        getline(ss, name, ',');

        // Create a Course object
        Course course(courseNumber, name);

        // Extract prerequisites and add them to the Course object
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        // Add the Course object to the courseTable
        courseTable[course.courseNumber] = course;
    }

    file.close();
}

// Function to print a list of all courses
void printCourses() {
    for (const auto& entry : courseTable) {
        cout << entry.second.courseNumber << ", " << entry.second.name << endl;
    }
}

// Function to print details of a specific course
void printCourse(const string& courseNumber) {
    // Convert the entered course number to uppercase
    string uppercaseCourseNumber = courseNumber;
    transform(uppercaseCourseNumber.begin(), uppercaseCourseNumber.end(), uppercaseCourseNumber.begin(), ::toupper);

    // Search for the course in the courseTable
    auto it = courseTable.find(uppercaseCourseNumber);
    if (it != courseTable.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.name << endl;

        // Check if the course has prerequisites
        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            auto prereqIt = course.prerequisites.begin();

            // Print the first prerequisite
            cout << *prereqIt;
            ++prereqIt;

            // Print the rest of the prerequisites with a comma before each
            for (; prereqIt != course.prerequisites.end(); ++prereqIt) {
                cout << ", " << *prereqIt;
            }
        } else {
            cout << "No prerequisites for this course.";
        }

        cout << endl;
    } else {
        cout << "Course not found." << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\nWelcome to the course planner.\n\n";
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "4. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Load courses from a file
                string inputFile = "ABCU_Advising_Program_Input.txt";
                loadCourses(inputFile);
                cout << "Data loaded successfully." << endl;
                break;
            }
            case 2: {
                // Print a list of all courses
                cout << "Here is a sample schedule:\n\n";
                printCourses();
                break;
            }
            case 3: {
                // Print details of a specific course
                cout << "What course do you want to know about?\n";
                string courseNumber;
                cin >> courseNumber;
                printCourse(courseNumber);
                break;
            }
            case 4: {
                cout << "Thank you for using the course planner!\n";
                break;
            }
            default: {
                cout << choice << " is not a valid option.\n";
            }
        }

    } while (choice != 4);

    return 0;
}