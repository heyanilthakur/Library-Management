#include "LibrarianDef.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>
using namespace std;
int fx = 1;
void addBooks(BookList &books) {
  try {
    string serial, bookname, author, publishdate;

    cout << "Enter the following details: " << endl;

    while (true) {
      cout << "BOOK SERIAL (enter 'q' to quit): ";
      getline(cin, serial);

      if (serial == "q")
        break;

      cout << "BOOKNAME: ";
      getline(cin, bookname);

      cout << "AUTHOR: ";
      getline(cin, author);

      cout << "PUBLISH DATE(DD MM YYYY): ";
      getline(cin, publishdate);

      if (isValidDate(publishdate)) {
        books.addBook(serial, bookname, author, publishdate);
      } else {
        cout << "Invalid publish date format." << endl;
      }
    }

    books.writeToFile(
        "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
    cout << "Books added successfully!" << endl;
  } catch (const invalid_argument &e) {
    cout << "Error found in addBooks: " << e.what() << endl;
  }
}

void deleteBooks(BookList &books) {
  try {
    string serial;

    cout << "Enter the following details: " << endl;

    cout << "BOOK SERIAL: ";
    getline(cin, serial);

    books.deleteBook(serial);
    books.writeToFile(
        "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
  } catch (const invalid_argument &e) {
    cout << "Error found in deleteBooks: " << e.what() << endl;
  }
}
void modifyBooks(BookList &books) {
  try {
    std::string serial, bookname, author, publishdate;

    std::cout << "Enter the following details: " << std::endl;

    std::cout << "BOOK SERIAL: ";
    getline(std::cin, serial);

    std::cout << "NEW BOOK NAME: ";
    getline(std::cin, bookname);

    std::cout << "NEW AUTHOR NAME: ";
    getline(std::cin, author);

    std::cout << "NEW PUBLISH DATE: ";
    getline(std::cin, publishdate);

    books.modifyBook(serial, bookname, author, publishdate);
    books.writeToFile(
        "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
  } catch (const invalid_argument &e) {
    cout << "Error found in modifyBooks: " << e.what() << endl;
  }
}

void borrowBooks(BookList &books) {
  try {
    string serial, borrowerID, borrowDate, dueDate;

    cout << "Enter the following details: " << endl;

    cout << "BOOK SERIAL: ";
    getline(cin, serial);

    cout << "BORROWER ID: ";
    getline(cin, borrowerID);

    cout << "BORROW DATE(DD MM YYYY): ";
    getline(cin, borrowDate);

    cout << "DUE DATE(DD MM YYYY): ";
    getline(cin, dueDate);

    if (isValidDate(borrowDate) && isValidDate(dueDate)) {
      books.borrowBook(serial, borrowerID, borrowDate, dueDate);
    } else {
      cout << "Invalid date format." << endl;
    }

    cout << "Book borrowed successfully!" << endl;
    books.writeToFile(
        "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
  } catch (const invalid_argument &e) {
    cout << "Error found in borrowBooks: " << e.what() << endl;
  }
}

void returnBooks(BookList &books) {
  try {
    string serial;

    cout << "Enter the following details: " << endl;

    cout << "BOOK SERIAL: ";
    getline(cin, serial);

    books.returnBook(serial);
    books.writeToFile(
        "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
  } catch (const invalid_argument &e) {
    cout << "Error found in returnBooks: " << e.what() << endl;
  }
}
void listBorrowedBooksByBorrowerIDs(BookList &books) {
  try {
    string borrowerID;

    cout << "Enter the borrower ID to list borrowed books: ";
    getline(cin, borrowerID);

    books.listBorrowedBooksByBorrowerID(borrowerID);
  } catch (const invalid_argument &e) {
    cout << "Error found in listBorrowedBooksByBorrowerIDs : " << e.what()
         << endl;
  }
}

BookList books;
void LibraryLogin() {

  string userid, password, domain;
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
    do {
      cout << "-----------------LIBRARY MANAGEMENT-------------------" << endl;
      cout << "|                  Select An Option :                |"
           << endl;
      cout << "|               1. Add Books in Library :            |"
           << endl;
      cout << "|               2. Delete Books of Library :         |"
           << endl;
      cout << "|               3. Modify Books of Library :         |"
           << endl;
      cout << "|               4. List Borrowers from Library :     |"
           << endl;
      cout << "|               5. Borrow Boook from Library :       |"
           << endl;
      cout << "|               6. Return Book from Library :        |"
           << endl;
      cout << "|               7. Exit :                            |"
           << endl;
      cout << "-------------------------------------------------------" << endl;

      cout << "Enter your choice: ";
      cin >> choice;
      cin.ignore();

      switch (choice) {
      case 1:
        addBooks(books);
        break;
      case 2:
        deleteBooks(books);
        break;
      case 3:
        modifyBooks(books);
        break;
      case 4:
        listBorrowedBooksByBorrowerIDs(books);
        break;
      case 5:
        borrowBooks(books);
        break;
      case 6:
        returnBooks(books);
        break;
      case 7:
        exit(0);
        break;

      default:
        cout << "Invalid Choice! Try Again." << endl;
        break;
      }
      char continueChoice;
      cout << "Do you want to continue (y/n)? ";
      cin >> continueChoice;
      cin.ignore();

      if (continueChoice != 'y' && continueChoice != 'Y') {
        break;
      }
    } while (true);
  } else {
    fx++;
    if (fx <= 3) {
      cout << "Enter Correct Name/Password" << endl;
      cout << endl;
      LibraryLogin();
    } else {
      cout << endl;
      cout << "Login Limit Reached...Exiting the Application" << endl;
    }
  }
}