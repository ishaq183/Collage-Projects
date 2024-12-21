#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

class Registration{
    fstream file;
    string name,email,username,password;
    public:
        bool isValidEmail(const string& email);
        bool isempty(const string& string);
        bool isExistUsername(const string& username);
        void openfile();
        void signUp();
        void signIn();
};

int main(){
    int choice;
    Registration reg;
    do{
    cout<<"Registration Form\n"<<endl;
    cout<<"1. Sign In\n2. Sign Up\n0. Exist\nEnter your choice: ";
    cin>>choice;
    switch(choice){
        case 1:
            reg.signIn();
            break;
        case 2:
            reg.signUp();
            break;
        case 0:
            break;    
        default:
            cout<<"Invalid Choice!!!!";
    }
    }while(choice!=0);
    return 0;
}

void Registration::openfile(){
     file.open("Registration.txt",ios::in);
     while(!file.eof()){
        getline(file,name,'*');
        getline(file,email,'*');
        getline(file,username,'*');
        getline(file,password,'*');
     }
}

bool Registration::isValidEmail(const string& email) {
    const regex pattern(
        R"((^[\w.%+-]+@(gmail|yahoo|hotmail|outlook|icloud|edu|gov|tech)\.(com|pk|io|org|net|edu|gov|tech)$))"
    );
    return regex_match(email, pattern);
}

bool Registration::isExistUsername(const string& username){
    file.open("Registration.txt",ios::in);
    string existingUsername;
    while(!file.eof()){
        getline(file,name,'*');
        getline(file,email,'*');
        getline(file,existingUsername,'*');
        getline(file,password,'*');
        if(existingUsername==username){
            return true;
        }
    }
    file.close();
    return false;
}

bool Registration::isempty(const string& string){
    if(string==""){
        return true;
    }
    return false;
}

void Registration::signUp(){
    cin.ignore();
    cout<<"Enter your Name:\n";
    getline(cin,name);
    if(isempty(name)){
        cout << "Empty Field.\nTry again." << endl;
        
        return;
    }
    cout<<"Enter your Email address:\n";
    getline(cin,email);
    if(isempty(email)){
        cout << "Empty Field.\nTry again" << endl;
        return;
    }
    if (!isValidEmail(email)) {
        cout << "The email address is invalid.\n";
        cout<<"Please try again with a valid Email:\n";
        return;
    } 

    cout<<"Enter your username:\n";
    getline(cin,username);
    if(isempty(username)){
        cout << "Empty Field.\nTry again" << endl;
        return;
    }
    if(isExistUsername(username)){
        cout << "Your entered Username is already exist." << endl;
        cout << "Please try again with another Username." << endl;
        return;
    }
    cout<<"Enter your Password:\n";
    getline(cin,password);
    if(isempty(password)){
        cout << "Empty Field.\nTry again" << endl;
        return;
    }
    file.open("Registration.txt",ios::out | ios::app);
    file<<name<<"*"<<email<<"*"<<username<<"*"<<password<<"\n";
    file.close();
    cout << "SignUp Successful." << endl;
}

void Registration::signIn() {
    string enteredName, enteredPassword;
    cout << "Enter your name: \n";
    cin >> enteredName;
    cout << "Enter your password: \n";
    cin >> enteredPassword;

    ifstream file("Registration.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open the file!" << endl;
        return;
    }

    bool found = false;
    
    while (file.eof()) {
        getline(file, name, '*');
        getline(file, email, '*');
        getline(file, username, '*');
        getline(file, password, '\n');

        if (enteredName == name && enteredPassword == password) {
            cout << "Login successful." << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Your name or password is incorrect." << endl;
    }

    file.close(); 
}