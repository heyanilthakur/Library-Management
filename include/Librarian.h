#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

// Define a struct for a book
struct Book {
  string serial;
  string bookname;
  string author;
  string publishdate;
};

// Define a class for a list of books using STL list
class BookList {
private:
  list<Book> books; // STL list of books

public:
  // Method to add a new book at the end of the list
  void addBook(string serial, string bookname, string author,
               string publishdate) {
    // Create a new book with the given data
    Book newBook = {serial, bookname, author, publishdate};

    // Add the new book to the end of the list
    books.push_back(newBook);
  }

  // Method to delete a book from the list based on its serial number
  void deleteBook(string serial) {
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
  void writeToFile(string filename) {
    // Open the file in append mode
    fstream file;
    file.open(filename, std::ios::out);

    // Traverse the list and write each book's data to the file
    for (const Book &book : books) {
      file << book.serial << "," << book.bookname << "," << book.author << ","
           << book.publishdate << "\n";
    }

    // Close the file
    file.close();
  }
  void modifyBook(string serial, string bookname = "", string author = "",
                  string publishdate = "") {
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
          book.publishdate = publishdate;
        }
        break;
      }
    }
  }
};

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
    books.addBook(serial, bookname, author, publishdate);
  }
  books.writeToFile(
      "/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
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
    BookList books;

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
      cout << "|               4. Exit :                              |"
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
        exit(0);
        break;

      default:
        cout << "Invalid Choice! Try Again." << endl;
        break;
      }
    } while (choice != 3);
  }
}