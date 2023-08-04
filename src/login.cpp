#include <iostream>
using namespace std;
int main() {
  int choice;
  bool flag = 1;
  do {
    cout << "----------------------LOGIN HERE-----------------------" << endl;
    cout << "|                  Select An Option :                  |" << endl;
    cout << "|                1. Login As Librarian :               |" << endl;
    cout << "|               2. Exit the application :              |" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "                   Select a Choice :                   " << endl;

    cin >> choice;
    switch (choice) {
    case 1:
      flag = 0;
      break;

    case 2:
      system("exit");
      break;
    default:
      cout << "Invalid Input..!" << endl;
      cout << "Try Again.." << endl;
      break;
    }
  } while (choice != 3 && flag);
  return 0;
}