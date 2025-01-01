#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> // for max function
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int attendanceCount;
    int presentDays;

    Student() : rollNo(0), attendanceCount(0), presentDays(0) {}

    void markAttendance(bool status) {
        attendanceCount++;
        if (status) presentDays++;
    }

    double getAttendancePercentage() const {
        if (attendanceCount == 0) return 0.0;
        return (double)presentDays / attendanceCount * 100;
    }

    void saveToFile(ofstream &file) const {
        file << rollNo << endl;
        file << name << endl;
        file << attendanceCount << endl;
        file << presentDays << endl;
    }

    void loadFromFile(ifstream &file) {
        file >> rollNo;
        file.ignore();
        getline(file, name);
        file >> attendanceCount >> presentDays;
        file.ignore();
    }
};

class AttendanceSystem {
private:
    int nextRollNo;

    void updateNextRollNo(const string &className) {
        ifstream file(className + ".txt");
        Student temp;
        int maxRollNo = 0;

        if (file.is_open()) {
            while (!file.eof()) {
                temp.loadFromFile(file);
                if (file.eof()) break;
                maxRollNo = max(maxRollNo, temp.rollNo);
            }
            file.close();
        }
        nextRollNo = maxRollNo + 1; // Update the next roll number
    }

public:
    AttendanceSystem() : nextRollNo(1) {}

    void addClass() {
        string className;
        cout << "Enter class name: ";
        cin >> className;
        ofstream file(className + ".txt", ios::app);
        if (file.is_open()) {
            cout << "Class " << className << " created successfully!" << endl;
        } else {
            cout << "Error creating class." << endl;
        }
    }

    void deleteClass() {
        string className;
        cout << "Enter class name to delete: ";
        cin >> className;
        if (remove((className + ".txt").c_str()) == 0) {
            cout << "Class " << className << " deleted successfully!" << endl;
        } else {
            cout << "Error deleting class or class not found." << endl;
        }
    }

    void manageClass() {
        string className;
        cout << "Enter class name to manage: ";
        cin >> className;

        ifstream file(className + ".txt");
        if (!file.is_open()) {
            cout << "Class not found!" << endl;
            return;
        }
        file.close();

        updateNextRollNo(className); // Ensure the next roll number is correct

        while (true) {
            cout << "\n1. Add Student\n2. Mark Attendance\n3. Display Attendance\n4. Back\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    addStudent(className);
                    break;
                case 2:
                    markAttendance(className);
                    break;
                case 3:
                    displayAttendance(className);
                    break;
                case 4:
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    }

private:
    void addStudent(const string &className) {
        Student student;
        student.rollNo = nextRollNo++; // Assign the next available roll number
        cin.ignore();
        cout << "\nEnter name: ";
        getline(cin, student.name);

        ofstream file(className + ".txt", ios::app);
        if (file.is_open()) {
            student.saveToFile(file);
            file.close();
            cout << "\nStudent added successfully with Roll No: " << student.rollNo << endl;
        } else {
            cout << "\nError saving student." << endl;
        }
    }

    void markAttendance(const string &className) {
        ifstream inputFile(className + ".txt");
        ofstream tempFile("temp.txt");
        if (!inputFile.is_open() || !tempFile.is_open()) {
            cout << "\nError accessing class file." << endl;
            return;
        }

        Student student;
        bool dataFound = false;
        while (!inputFile.eof()) {
            student.loadFromFile(inputFile);
            if (inputFile.eof()) break;

            dataFound = true;
            cout << "\n\nRoll#: " << student.rollNo << " Name: " << student.name << endl;
            cout << "Enter 1 for present or 0 for absent: ";
            int status;
            while (true) {
                cin >> status;
                if (status == 0 || status == 1) {
                    student.markAttendance(status);
                    break;
                } else {
                    cout << "Invalid input. Enter 1 for present or 0 for absent: ";
                }
            }
            student.saveToFile(tempFile);
        }

        inputFile.close();
        tempFile.close();

        remove((className + ".txt").c_str());
        rename("temp.txt", (className + ".txt").c_str());

        if (!dataFound) {
            cout << "No students found." << endl;
        } else {
            cout << "Attendance marked successfully!" << endl;
        }
    }

    void displayAttendance(const string &className) {
        ifstream file(className + ".txt");
        if (!file.is_open()) {
            cout << "Error reading class file." << endl;
            return;
        }

        Student student;
        while (!file.eof()) {
            student.loadFromFile(file);
            if (file.eof()) break;

            cout << "\n\nRoll#: " << student.rollNo << " Name: " << student.name << endl;
            cout << "Attendance Percentage: " << student.getAttendancePercentage() << "%" << endl;
        }
        file.close();
    }
};

int main() {
    AttendanceSystem system;
    while (true) {
        cout << "\n1. Add Class\n2. Delete Class\n3. Manage Class\n4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                system.addClass();
                break;
            case 2:
                system.deleteClass();
                break;
            case 3:
                system.manageClass();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
