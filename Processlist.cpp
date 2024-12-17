#include <iostream>
#include<unistd.h>
#include <cstdlib>
#include <string>

using namespace std;
void list_Of_Process(){
        cout<<"LIST OF PROCESS\n";
	    system("tasklist");
    }
    void delete_Process(){
        string process_Name;
	    cout << "Enter the Process Name to terminate the process from the list(e.g notepad.exe): ";
        cin >> process_Name;

	    string command = "taskkill /F /IM " + process_Name;

	    int result = system(command.c_str());
	    if (result == 0) {
	        cout << "Process with Process " << process_Name << " was terminated successfully.\n";
	    } 
	    else{
		    cout << "Failed to terminate the process. Ensure the Process Name is correct and you have the necessary permissions.\n";
	    }
    }
int main() {
    int choice;
    do{
        system("clear");
        cout<<"Running Process Manager\n"<<endl;
        cout<<"1. List of Process\n2. Terminate the Process\n0. Exit\n";
        cout<<"Enter you choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                system("clear");
                list_Of_Process();
                sleep(3);
                break;
            case 2:
                system("clear");
                delete_Process();
                sleep(3);
                break;
            case 0:
                break;
            default:
                cout<<"You Enter invaild option!!!!\n";
        
        }
    }while(choice!=0);
	return 0;
}