#include <fstream>
#include <list>
#include <string>
using namespace std;

// Define a struct for a book
struct Book {
  std::string serial;
  std::string bookname;
  std::string author;
  std::string publishdate;
};

// Define a class for a list of books using STL list
class BookList {
private:
  std::list<Book> books; // STL list of books

public:
  // Method to add a new book at the end of the list
  void addBook(string serial, string bookname, string author,
               string publishdate);

  // Method to delete a book from the list based on its serial number
  void deleteBook(string serial);

  // Method to write the list to a file
  void writeToFile(string filename);

  // Method to modify a book's data based on its serial number
  void modifyBook(string serial, string bookname = "", string author = "",
                  string publishdate = "");
};
