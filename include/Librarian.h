#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int fx = 1;

  void addBooks() {
    string serial, bookname, author, publishdate;
    cout << "Enter the following details: " << endl;
    cout << "BOOK SERIAL: ";
    cin >> serial;
    cout << "BOOKNAME";
    cin >> bookname;
    cout << "AUTHOR";
    cin >> author;
    cout << "PUBLISH DATE(DD MM YYYY): ";
    cin >> publishdate;
    fstream file;
    file.open("/Users/AN20449220/Desktop/Library-Management/csv/data.csv",
              std::ios::out | std::ios::app);
    file << serial << "," << bookname << "," << author << "," << publishdate
         << "\n";
  }
void libraryLogin() {

  string userid, password;
  cout << "Enter Your Name: ";
  cin >> userid;
  cout << "Enter your Password: ";
  cin >> password;

  fstream data;
  string details, word, l;
  vector<string> users;
  data.open("/Users/AN20449220/Desktop/Library-Management/csv/login.csv",
            ios::in);
  int count = 0;
  while (getline(data, l)) {
    count++;
  }
  data.close();
  data.open("/Users/AN20449220/Desktop/Library-Management/csv/login.csv",
            ios::in);

  for (int i = 0; i <= count; i++) {
    getline(data, details);
    stringstream s(details);
    while (getline(s, word, ',')) {
      users.push_back(word);
    }
  }
  int length = users.size();
  int i = 0;
  int flag = 0;
  while (i < length) {
    if (userid == users[i] && password == users[i + 1]) {
      flag = 1;
    }
    i = i + 3;
  }
  if (flag == 1) {
    int choice;
    cout << "ADMIN, Login Successfull" << endl;
    do {
      cout << "-----------------LIBRARY MANAGEMENT-------------------" << endl;
      cout << "|                  Select An Option :                  |"
           << endl;
      cout << "|               1. Add Books from Library :            |"
           << endl;
      cout << "|               2. Delete Books from Library :         |"
           << endl;
      cout << "|               3. Search Books in Library             |"
           << endl;
      cout << "|               4. Manage Book Borrowings :            |"
           << endl;
      cout << "|               5. Manage Book Fines :                 |"
           << endl;
      cout << "|               6. Exit the application :              |"
           << endl;
      cout << "-------------------------------------------------------" << endl;

      cin >> choice;
      switch (choice) {
      case 1:
        addBooks();
        flag = 0;
        break;
      case 2:
        addBooks();
        flag = 0;
        break;

      case 3:
        addBooks();
        flag = 0;
        break;
      case 4:
        addBooks();
        flag = 0;
        break;
      case 5:
        addBooks();
        flag = 0;
        break;
      case 6:
        system("exit");
        break;
      default:
        cout << "Invalid Input..!" << endl;
        cout << "Try Again.." << endl;
        break;
      }
    } while (choice != 6);
  } else {
    fx++;
    if (fx <= 3) {
      cout << "Enter Correct Name/Password" << endl;
      cout << endl;
      libraryLogin();
    } else {
      cout << endl;
      cout << "Login Limit Reached...Exiting the Application" << endl;
    }
  }
}