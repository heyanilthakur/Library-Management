#include <iostream>
#include"/Users/AN20449220/Desktop/Library-Management/include/Librarian.h"
using namespace std;
int main() {
  int choice;
  bool flag = 1;
    // Display the menu and handle user input until the user chooses to exit
  do {
    cout << "----------------------LOGIN HERE-----------------------" << endl;
    cout << "|                  Select An Option :                  |" << endl;
    cout << "|                1. Login As Librarian :               |" << endl;
    cout << "|               2. Exit the application :              |" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "                   Select a Choice :                   " << endl;

    // Read user choice from input

    cin >> choice;
    switch (choice) {
    case 1:
      LibraryLogin();// Call the LibraryLogin function to handle librarian login
      flag = 0;// Set flag to exit the loop after successful login
      break;  

    case 2:
      system("exit");// Exit the application using the system command
      break;
    default:
      cout << "Invalid Input..!" << endl;
      cout << "Try Again.." << endl;
      break;
    }
  } while (choice != 3 && flag);// Keep looping until choice is not 3 and flag is true
  return 0;
}