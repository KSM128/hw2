#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

// ctor dtor
Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
  Product("movie", name, price, qty), genre_(genre), rating_(rating)
{}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> keys;
  // name
  std::set<std::string> names = parseStringToWords(getName());
  keys.insert(names.begin(), names.end());
  // genre
  // keys.insert(genre_);
  std::set<std::string> genres = parseStringToWords(genre_);
  keys.insert(genres.begin(), genres.end());

  return keys;
}

std::string Movie::displayString() const {
  // name genre rating price quantity
  // std::string result = getName() + "\n" + "Genre: ";
  // result += genre_ + " Rating: " + rating_ + "\n";
  // result += std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.";
  // return result;
  std::ostringstream oss;
  oss << getName() << "\nGenre: " << genre_ 
      << " Rating: " << rating_ << "\n" << std::fixed
      << std::setprecision(2) << getPrice() << " "
      << getQty() << " left.";
  return oss.str();
}

void Movie::dump(std::ostream& os) const {
  os << "movie" << "\n";
  os << getName() << "\n";
  os << getPrice() << "\n";
  os << getQty() << "\n";
  os << genre_ << "\n";
  os << rating_ << "\n";
}