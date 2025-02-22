#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

// ctor dtor
Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) :
  Product("clothing", name, price, qty), size_(size), brand_(brand)
{}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keys;
  // name
  std::set<std::string> names = parseStringToWords(getName());
  keys.insert(names.begin(), names.end());
  // brands
  std::set<std::string> brands = parseStringToWords(brand_);
  keys.insert(brands.begin(), brands.end());

  return keys;
}

std::string Clothing::displayString() const {
  // name size brand price quantity
  // std::string result = getName() + "\n" + "Size: ";
  // result += size_ + " Brand: " + brand_ + "\n";
  // result += std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.";
  // return result;
  std::ostringstream oss;
  oss << getName() << "\nSize: " << size_ 
      << " Brand: " << brand_ << "\n" << std::fixed
      << std::setprecision(2) << getPrice() << " "
      << getQty() << " left.";
  return oss.str();
}

void Clothing::dump(std::ostream& os) const {
  os << "clothing" << "\n";
  os << getName() << "\n";
  os << getPrice() << "\n";
  os << getQty() << "\n";
  os << size_ << "\n";
  os << brand_ << "\n";
}