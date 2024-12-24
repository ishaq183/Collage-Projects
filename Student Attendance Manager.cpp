
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Student class
class Student {
public:
    string name;
    string className;
    string section;
    vector<bool> attendance;

    Student(string n, string c, string s) : name(n), className(c), section(s) {}

    void markAttendance(bool status) {
        attendance.push_back(status);
    }

    double getAttendancePercentage() {
        int presentDays = 0;
        for (bool status : attendance) {
            if (status) presentDays++;
        }
        return (double)presentDays / attendance.size() * 100;
    }
};

// Student Attendance Management System class
class StudentAttendanceManagementSystem {
private:
    vector<Student> students;

public:
    void addStudent(string name, string className, string section) {
        Student newStudent(name, className, section);
        students.push_back(newStudent);
    }

    void markAttendance(int studentIndex, bool status) {
        if (studentIndex >= 0 && studentIndex < students.size()) {
            students[studentIndex].markAttendance(status);
        } else {
            cout << "Invalid student index." << endl;
        }
    }

    void displayStudentInfo(int studentIndex) {
        if (studentIndex >= 0 && studentIndex < students.size()) {
            Student student = students[studentIndex];
            cout << "Name: " << student.name << endl;
            cout << "Class: " << student.className << endl;
            cout << "Section: " << student.section << endl;
            cout << "Attendance Percentage: " << student.getAttendancePercentage() << "%" << endl;
        } else {
            cout << "Invalid student index." << endl;
        }
    }

    void displayLowAttendanceStudents() {
        cout << "Low Attendance Students:" << endl;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getAttendancePercentage() < 75) {
                cout << "Name: " << students[i].name << endl;
                cout << "Class: " << students[i].className << endl;
                cout << "Section: " << students[i].section << endl;
                cout << "Attendance Percentage: " << students[i].getAttendancePercentage() << "%" << endl;
                cout << endl;
            }
        }
    }
};

int main() {
    StudentAttendanceManagementSystem system;

    while (true) {
        cout << "1. Add Student" << endl;
        cout << "2. Mark Attendance" << endl;
        cout << "3. Display Student Info" << endl;
        cout << "4. Display Low Attendance Students" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, className, section;
                cout << "Enter student name: ";
                cin >> name;
                cout << "Enter class name: ";
                cin >> className;
                cout << "Enter section: ";
                cin >> section;
                system.addStudent(name, className, section);
                break;
            }
            case 2: {
                int studentIndex;
                bool status;
                cout << "Enter student index: ";
                cin >> studentIndex;
                cout << "Enter attendance status (1 for present, 0 for absent): ";
                cin >> status;
                system.markAttendance(studentIndex, status);
                break;
            }
            case 3: {
                int studentIndex;
                cout << "Enter student index: ";
                cin >> studentIndex;
                system.displayStudentInfo(studentIndex);
                break;
            }
            case 4:
                system.displayLowAttendanceStudents();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
