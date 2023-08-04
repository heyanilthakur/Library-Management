#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int fx = 1;
    // Define a struct for a book node
    struct Book {
      string serial;
      string bookname;
      string author;
      string publishdate;
      Book* next; // pointer to the next book in the list
    };

    // Define a class for a linked list of books
    class BookList {
      private:
        Book* head; // pointer to the first book in the list
        Book* tail; // pointer to the last book in the list
      public:
        // Constructor to initialize an empty list
        BookList() {
          head = NULL;
          tail = NULL;
        }

        // Destructor to free the memory of the list
        ~BookList() {
          Book* current = head;
          while (current != NULL) {
            Book* next = current->next;
            delete current;
            current = next;
          }
        }

        // Method to add a new book at the end of the list
        void addBook(string serial, string bookname, string author, string publishdate) {
          // Create a new book node with the given data
          Book* newBook = new Book();
          newBook->serial = serial;
          newBook->bookname = bookname;
          newBook->author = author;
          newBook->publishdate = publishdate;
          newBook->next = NULL;

          // If the list is empty, make the new book the head and tail
          if (head == NULL) {
            head = newBook;
            tail = newBook;
          }
          // Else, append the new book after the tail and update the tail
          else {
            tail->next = newBook;
            tail = newBook;
          }
        }

        // Method to write the list to a file
        void writeToFile(string filename) {
          // Open the file in append mode
          fstream file;
          file.open(filename, std::ios::out | std::ios::app);

          // Traverse the list and write each book's data to the file
          Book* current = head;
          while (current != NULL) {
            file << current->serial << "," << current->bookname << "," << current->author << "," << current->publishdate << "\n";
            current = current->next;
          }

          // Close the file
          file.close();
        }
    };

    // Rewrite the addBooks function using the BookList class
    void addBooks() {
      string serial, bookname, author, publishdate;

      // Create an object of BookList class
      BookList books;

      cout << "Enter the following details: " << endl;

      // Loop until the user enters 'q' to quit
      while (true) {
        cout << "BOOK SERIAL (enter 'q' to quit): ";
        cin >> serial;

        // Break out of the loop if 'q' is entered
        if (serial == "q") break;

        cout << "BOOKNAME: ";
        cin >> bookname;

        cout << "AUTHOR: ";
        cin >> author;

        cout << "PUBLISH DATE(DD MM YYYY): ";
        cin >> publishdate;

        // Add a new book to the list with the given data
        books.addBook(serial, bookname, author, publishdate);
      }

      // Write the list to the file
      books.writeToFile("/Users/AN20449220/Desktop/Library-Management/csv/data.csv");
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