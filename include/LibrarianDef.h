#include<iostream>
#include "date.h"
#include <fstream>
#include <list>
#include <string>
using namespace std;

// Define a struct for a book
struct Book {
  string serial;
  string bookname;
  string author;
  string publishdate;
  string borrowerID;
  string borrowDate;
  string dueDate;
  bool returned;
  string status;
};

// Define a class for a list of books using STL list
class BookList {
private:
  std::list<Book> books; // STL list of books

public:
  // Method to add a new book at the end of the list
  void addBook(string serial, string bookname, string author,
                       string publishdate) {
  try {
    Book newBook = {serial, bookname, author, publishdate, "",
                    "",     "",       true,   "Available"};

    books.push_back(newBook);
  } catch (const invalid_argument &e) {
    cout << "Error found in addBook: " << e.what() << endl;
  }
}

void deleteBook(string serial) {
  try {

    for (auto it = books.begin(); it != books.end(); ++it) {
      if (it->serial == serial) {

        books.erase(it);
        break;
      }
    }
  } catch (const invalid_argument &e) {
    cout << "Error found in deleteBook: " << e.what() << endl;
  }
}

void writeToFile(string filename) {
  try {
    fstream outFile(filename, ios::out);
    if (outFile.is_open()) {
      for (const auto &book : books) {
        outFile << book.serial << "," << book.bookname << "," << book.author
                << "," << book.publishdate << "," << book.borrowerID << ","
                << book.borrowDate << "," << book.dueDate << ","
                << book.returned << "," << book.status << "\n";
      }
      outFile.close();
      cout << "Data written to " << filename << " successfully.\n";
    } else {
      cerr << "Unable to open file: " << filename << "\n";
    }
  } catch (const invalid_argument &e) {
    cout << "Error found in writeToFile: " << e.what() << endl;
  }
}

void modifyBook(string serial, string bookname, string author,
                          string publishdate) {
  try {

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
  } catch (const invalid_argument &e) {
    cout << "Error Found in modifyBook: " << e.what() << endl;
  }
}
void borrowBook(string serial, string borrowerID, string borrowDate,
                          string dueDate) {
  try {
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
  } catch (const invalid_argument &e) {
    cout << "Error found in borrowBook: " << e.what() << endl;
  }
}
void returnBook(string serial) {
  try {
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
  } catch (const invalid_argument &e) {
    cout << "Error found in returnBook: " << e.what() << endl;
  }
}
void listBorrowedBooksByBorrowerID(string borrowerID) {
  try {
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
  } catch (const invalid_argument &e) {
    cout << "Error found in listBorrowedBooksByBorrowerID: " << e.what()
         << endl;
  }
}
};