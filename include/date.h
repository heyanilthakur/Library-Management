#include <iomanip>
#include <sstream>
#include <string>

// A function to check if a string is a valid date in the format YYYY-MM-DD
bool isValidDate(std::string date) {
  // Create a stringstream from the input string
  std::stringstream ss(date);

  // Create a tm struct to store the parsed date
  std::tm tm = {};

  // Use std::get_time to parse the date and check if it matches the format
  if (ss >> std::get_time(&tm, "%Y-%m-%d")) {
    // Check if the stringstream is empty after parsing
    if (ss.eof()) {
      // Return true if the date is valid
      return true;
    }
  }

  // Return false otherwise
  return false;
}
