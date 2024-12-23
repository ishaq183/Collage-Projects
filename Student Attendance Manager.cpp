#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

class Registration {
    string name1, name2, email, username, password;

public:
    bool isValidEmail(const string &email);
    bool isEmpty(const string &str);
    bool isExistUsername(const string &username);
    void signUp();
    static bool signIn(const string &u, const string &p);
};

// Main Function
int main() {
    int choice;
    Registration reg;

    do {
        cout << "\nRegistration Form\n";
        cout << "1. Sign In\n2. Sign Up\n0. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string username, password;
            cout << "Enter your Username: ";
            cin >> username;
            cout << "Enter your Password: ";
            cin >> password;
            Registration::signIn(username, password);
            break;
        }
        case 2:
            reg.signUp();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

bool Registration::isEmpty(const string &str) {
    return str.empty();
}

bool Registration::isValidEmail(const string &email) {
    const regex pattern(
        R"((^[\w.%+-]+@(gmail|yahoo|hotmail|outlook|icloud|edu|gov|tech)\.(com|pk|io|org|net|edu|gov|tech)$))"
    );
    return regex_match(email, pattern);
}

bool Registration::isExistUsername(const string &username) {
    ifstream file("Registration.txt");
    string storedUsername, temp;

    if (file.is_open()) {
        while (getline(file, temp, '*')) { 
            getline(file, temp, '*');   
            getline(file, storedUsername, '*');
            getline(file, temp, '\n');   
            if (storedUsername == username) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void Registration::signUp() {
    cout << "Enter your First Name: ";
    cin >> name1;
    if (isEmpty(name1)) {
        cout << "Empty Field. Try again.\n";
        return;
    }

    cout << "Enter your Last Name: ";
    cin >> name2;

    cout << "Enter your Email Address: ";
    cin >> email;
    if (isEmpty(email)) {
        cout << "Empty Field. Try again.\n";
        return;
    }

    if (!isValidEmail(email)) {
        cout << "Invalid Email Address. Try again.\n";
        return;
    }

    cout << "Enter your Username: ";
    cin >> username;
    if (isEmpty(username)) {
        cout << "Empty Field. Try again.\n";
        return;
    }

    if (isExistUsername(username)) {
        cout << "Username already exists. Try a different username.\n";
        return;
    }

    cout << "Enter your Password: ";
    cin >> password;
    if (isEmpty(password)) {
        cout << "Empty Field. Try again.\n";
        return;
    }

    ofstream file("Registration.txt", ios::app); // Append mode
    if (file.is_open()) {
        file << name1 << " " << name2 << "*" << email << "*" << username << "*" << password << "\n";
        file.close();
        cout << "Sign Up Successful!\n";
    } else {
        cerr << "Error opening file for writing!\n";
    }
}

bool Registration::signIn(const string &u, const string &p) {
    ifstream file("Registration.txt");
    string storedName, storedEmail, storedUsername, storedPassword;

    if (file.is_open()) {
        while (getline(file, storedName, '*')) { 
            getline(file, storedEmail, '*');  
            getline(file, storedUsername, '*');  
            getline(file, storedPassword, '\n');  

            if (storedUsername == u && storedPassword == p) {
                cout << "Login Successful! Welcome, " << storedName << "!\n";
                file.close();
                return true;
            }
        }
        file.close();
        cout << "Invalid Username or Password.\n";
    } else {
        cerr << "Error opening file for reading!\n";
    }

    return false;
}
