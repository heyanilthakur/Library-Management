#include "BorrowerDef.h"
#include "LibrarianDef.h" // Include the header file that defines the Librarian class and its methods
#include "date.h" // Include the header file that defines the Date class and its methods
#include <fstream>
#include <iostream>
#include <list>
#include <string>
using namespace std;
// Method to add a new book at the end of the list
void BookList::addBook(string serial, string bookname, string author,
                       string publishdate) {
  // Create a new book with the given data
  Book newBook = {serial, bookname, author, publishdate, "",
                  "",     "",       true,   "Available"};
  // Add the new book to the end of the list
  books.push_back(newBook);
}

// Method to delete a book from the list based on its serial number
void BookList::deleteBook(string serial) {
  // Find the book with the given serial number
  for (auto it = books.begin(); it != books.end(); ++it) {
    if (it->serial == serial) {
      // Delete the book from the list
      books.erase(it);
      break;
    }
  }
}

// Method to write the list to a file
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
  // Find the book with the given serial number
  for (auto &book : books) {
    if (book.serial == serial) {
      // Modify the book's data if new data is provided
      if (!bookname.empty()) {
        book.bookname = bookname;
      }
      if (!author.empty()) {
        book.author = author;
      }
      if (!publishdate.empty()) {
        // Check if the publishdate is valid
        if (isValidDate(publishdate)) {
          book.publishdate = publishdate;
        } else {
          // Print an error message
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

      // Calculate fine if the return is after the due date
      if (isValidDate(book.dueDate)) {
        time_t now = time(nullptr);
        tm dueTm = {};
        istringstream(book.dueDate) >> get_time(&dueTm, "%Y-%m-%d");
        time_t dueTime = mktime(&dueTm);

        double secondsLate = difftime(now, dueTime);
        double daysLate = secondsLate / (60 * 60 * 24);

        if (daysLate > 0) {
          double finePerDay = 5.0; // Adjust the fine per day as needed
          double fineAmount = daysLate * finePerDay;
          cout << "Fine calculated: Rs." << fineAmount << endl;
        }
      }

      // Update the book status
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

// void BorrowerList::addBorrower(string borrowerID, string name, string contact) {
//   Borrower newBorrower = {borrowerID, name, contact};
//   borrowers.push_back(newBorrower);
// }

// void BorrowerList::deleteBorrower(string borrowerID) {
//   for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
//     if (it->borrowerID == borrowerID) {
//       borrowers.erase(it);
//       break;
//     }
//   }
// }

// void BorrowerList::modifyBorrower(string borrowerID, string name,
//                                   string contact) {
//   for (auto &borrower : borrowers) {
//     if (borrower.borrowerID == borrowerID) {
//       if (!name.empty()) {
//         borrower.name = name;
//       }
//       if (!contact.empty()) {
//         borrower.contact = contact;
//       }
//       break;
//     }
//   }
// }
void BorrowerList::writeToFile(std::string filename) {
  std::ofstream outFile(filename);
  if (outFile.is_open()) {
    for (const Borrower &borrower : borrowers) {
      outFile << borrower.borrowerID << "," << borrower.name << ","
              << borrower.contact << "\n";
    }
    outFile.close();
    std::cout << "Borrower data written to file: " << filename << std::endl;
  } else {
    std::cerr << "Unable to open file: " << filename << std::endl;
  }
}

// Function to prompt the user to enter details of books, add them to a BookList
// object, and write it to a CSV file
void addBooks(BookList &books) {
  string serial, bookname, author, publishdate;

  cout << "Enter the following details: " << endl;

  // Loop until the user enters 'q' to quit
  while (true) {
    cout << "BOOK SERIAL (enter 'q' to quit): ";
    getline(cin, serial);

    // Break out of the loop if 'q' is entered
    if (serial == "q")
      break;

    cout << "BOOKNAME: ";
    getline(cin, bookname);

    cout << "AUTHOR: ";
    getline(cin, author);

    cout << "PUBLISH DATE(DD MM YYYY): ";
    getline(cin, publishdate);

    // Add a new book to the list with the given data
    if (isValidDate(publishdate)) {
      books.addBook(serial, bookname, author, publishdate);
    } else {
      cout << "Invalid publish date format." << endl;
    }
  }

  // Write the updated book list to a file
  books.writeToFile(
      "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
  cout << "Books added successfully!" << endl;
}

// Function to prompt the user to enter the serial number of a book and delete
// it from a BookList object
void deleteBook(BookList &books) {
  string serial;

  cout << "Enter the following details: " << endl;

  cout << "BOOK SERIAL: ";
  getline(cin, serial);

  // Delete the book with the given serial number from the list
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

  // Modify the book with the given serial number in the list
  books.modifyBook(serial, bookname, author, publishdate);
  books.writeToFile(
      "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
}

// void addBorrowers(BorrowerList &borrowers) {
//   string borrowerID, name, contact;

//   cout << "Enter the following details: " << endl;

//   while (true) {
//     cout << "BORROWER ID (enter 'q' to quit): ";
//     getline(cin, borrowerID);

//     if (borrowerID == "q")
//       break;

//     cout << "BORROWER NAME: ";
//     getline(cin, name);

//     cout << "BORROWER CONTACT: ";
//     getline(cin, contact);

//     borrowers.addBorrower(borrowerID, name, contact);
//   }
//   borrowers.writeToFile(
//       "/Users/AN20449220/Desktop/Library-Management/csv/borrowers.csv");
// }

// void deleteBorrower(BorrowerList &borrowers) {
//   string borrowerID;

//   cout << "Enter the following details: " << endl;

//   cout << "BORROWER ID: ";
//   getline(cin, borrowerID);

//   borrowers.deleteBorrower(borrowerID);

//   borrowers.writeToFile(
//       "/Users/AN20449220/Desktop/Library-Management/csv/borrowers.csv");
// }

// void modifyBorrowers(BorrowerList &borrowers) {
//   string borrowerID, name, contact;

//   cout << "Enter the following details: " << endl;

//   cout << "BORROWER ID: ";
//   getline(cin, borrowerID);

//   cout << "NEW BORROWER NAME: ";
//   getline(cin, name);

//   cout << "NEW BORROWER CONTACT: ";
//   getline(cin, contact);

//   borrowers.modifyBorrower(borrowerID, name, contact);

//   borrowers.writeToFile(
//       "/Users/AN20449220/Desktop/Library-Management/csv/borrowers.csv");
// }
// Function to prompt the user to enter details of borrowing a book
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

  // Call the borrowBook function using the books object
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

  // Call the returnBook function using the books object
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
BorrowerList borrowers;
void LibraryLogin() {
  // Create an object of BookList class
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
        //addBorrowers(borrowers);
        break;
      case 5:
        //deleteBorrower(borrowers);
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
        break; // Exit the loop if the user doesn't want to continue
      }
    } while (true);
  }
}