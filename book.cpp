#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

// ctor dtor
Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) :
  Product("book", name, price, qty), isbn_(isbn), author_(author)
{}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
  std::set<std::string> keys;
  // name
  std::set<std::string> names = parseStringToWords(getName());
  keys.insert(names.begin(), names.end());
  // author
  std::set<std::string> authors = parseStringToWords(author_);
  keys.insert(authors.begin(), authors.end());
  // isbn
  keys.insert(isbn_);

  return keys;
}

std::string Book::displayString() const {
  // name author isbn price quantity
  // std::string result = getName() + "\n" + "Author: ";
  // result += author_ + " ISBN: " + isbn_ + "\n";
  // result += std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.";
  // return result;
  std::ostringstream oss;
  oss << getName() << "\nAuthor: " << author_ 
      << " ISBN: " << isbn_ << "\n" << std::fixed
      << std::setprecision(2) << getPrice() << " "
      << getQty() << " left.";
  return oss.str();
}

void Book::dump(std::ostream& os) const {
  os << "book" << "\n";
  os << getName() << "\n";
  os << getPrice() << "\n";
  os << getQty() << "\n";
  os << isbn_ << "\n";
  os << author_ << "\n";
}