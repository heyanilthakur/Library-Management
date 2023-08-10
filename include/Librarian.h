#include "LibrarianDef.h"
#include "date.h"
#include <fstream>
#include <iostream>
#include <list>
#include <string>
using namespace std;

void BookList::addBook(string serial, string bookname, string author,
                       string publishdate) {

  Book newBook = {serial, bookname, author, publishdate, "",
                  "",     "",       true,   "Available"};

  books.push_back(newBook);
}

void BookList::deleteBook(string serial) {

  for (auto it = books.begin(); it != books.end(); ++it) {
    if (it->serial == serial) {

      books.erase(it);
      break;
    }
  }
}

void BookList::writeToFile(string filename) {
  fstream outFile(filename, ios::out);
  if (outFile.is_open()) {
    for (const auto &book : books) {
      outFile << book.serial << "," << book.bookname << "," << book.author
              << "," << book.publishdate << "," << book.borrowerID << ","
              << book.borrowDate << "," << book.dueDate << "," << book.returned
              << "," << book.status << "\n";
    }
    outFile.close();
    cout << "Data written to " << filename << " successfully.\n";
  } else {
    cerr << "Unable to open file: " << filename << "\n";
  }
}

void BookList::modifyBook(string serial, string bookname, string author,
                          string publishdate) {

  for (auto &book : books) {
    if (book.serial == serial) {

      if (!bookname.empty()) {
        book.bookname = bookname;
      }
      if (!author.empty()) {
        book.author = author;
      }
      if (!publishdate.empty()) {

        if (isValidDate(publishdate)) {
          book.publishdate = publishdate;
        } else {

          std::cout << "Invalid publish date: " << publishdate << "\n";
        }
      }
      break;
    }
  }
}
void BookList::borrowBook(string serial, string borrowerID, string borrowDate,
                          string dueDate) {
  for (auto &book : books) {
    if (book.serial == serial && book.borrowerID.empty()) {
      book.borrowerID = borrowerID;
      book.borrowDate = borrowDate;
      book.dueDate = dueDate;
      book.returned = false;
      book.status = "Borrowed";
      cout << "Book borrowed successfully!" << endl;
      return;
    }
  }
  cout << "Book not available for borrowing." << endl;
}
void BookList::returnBook(string serial) {
  for (auto &book : books) {
    if (book.serial == serial && !book.borrowerID.empty() && !book.returned) {
      book.returned = true;

      if (isValidDate(book.dueDate)) {
        time_t now = time(nullptr);
        tm dueTm = {};
        istringstream(book.dueDate) >> get_time(&dueTm, "%Y-%m-%d");
        time_t dueTime = mktime(&dueTm);

        double secondsLate = difftime(now, dueTime);
        double daysLate = secondsLate / (60 * 60 * 24);

        if (daysLate > 0) {
          double finePerDay = 5.0;
          double fineAmount = daysLate * finePerDay;
          cout << "Fine calculated: Rs." << fineAmount << endl;
        }
      }

      book.status = "Available";
      book.borrowerID = "";
      book.borrowDate = "";
      book.dueDate = "";

      cout << "Book returned successfully!" << endl;
      return;
    }
  }
  cout << "Book not available for returning." << endl;
}
void BookList::listBorrowedBooksByBorrowerID(string borrowerID) {
  bool found = false;

  cout << "Books borrowed by Borrower ID " << borrowerID << ":" << endl;

  for (const auto &book : books) {
    if (book.borrowerID == borrowerID && !book.returned) {
      found = true;
      cout << "Serial: " << book.serial << endl;
      cout << "Book Name: " << book.bookname << endl;
      cout << "Author: " << book.author << endl;
      cout << "Publish Date: " << book.publishdate << endl;
      cout << "Borrow Date: " << book.borrowDate << endl;
      cout << "Due Date: " << book.dueDate << endl;
      cout << "Status: " << book.status << endl;
      cout << "-------------------------------" << endl;
    }
  }

  if (!found) {
    cout << "No borrowed books found for Borrower ID " << borrowerID << endl;
  }
}
void addBooks(BookList &books) {
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
}

void deleteBook(BookList &books) {
  string serial;

  cout << "Enter the following details: " << endl;

  cout << "BOOK SERIAL: ";
  getline(cin, serial);

  books.deleteBook(serial);
  books.writeToFile(
      "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
}
void modifyBooks(BookList &books) {
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
}

void borrowBooks(BookList &books) {
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
}

void returnBooks(BookList &books) {
  string serial;

  cout << "Enter the following details: " << endl;

  cout << "BOOK SERIAL: ";
  getline(cin, serial);

  books.returnBook(serial);
  books.writeToFile(
      "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
}
void listBorrowedBooksByBorrowerIDs(BookList &books) {
  string borrowerID;

  cout << "Enter the borrower ID to list borrowed books: ";
  getline(cin, borrowerID);

  books.listBorrowedBooksByBorrowerID(borrowerID);
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
      cout << "|                  Select An Option :                  |"
           << endl;
      cout << "|               1. Add Books from Library :            |"
           << endl;
      cout << "|               2. Delete Books from Library :         |"
           << endl;
      cout << "|               3. Modify Books from Library :         |"
           << endl;
      cout << "|               4. Add Boorrowers from Library :       |"
           << endl;
      cout << "|               5. Delete Borrowers from Library :     |"
           << endl;
      cout << "|               6. Modify Borrowers from Library :     |"
           << endl;
      cout << "|               7. Borrow Boook from Library :         |"
           << endl;
      cout << "|               8. Return Book from Library :          |"
           << endl;
      cout << "|               9. Exit :                              |"
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
        deleteBook(books);
        break;
      case 3:
        modifyBooks(books);
        break;
      case 4:

        break;
      case 5:

        break;
      case 6:
        listBorrowedBooksByBorrowerIDs(books);
        break;
      case 7:
        borrowBooks(books);
        break;
      case 8:
        returnBooks(books);
        break;
      case 9:
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
  }
}