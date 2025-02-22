#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <set>
#include <string>

class Book : public Product{
  public:
    // book has isbn and author
    Book(const std::string name, double price, int qty, const std::string isbn, const std::string author);
    ~Book();
    
    // keywords() returns name, author, isbn
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

  private:
    std::string isbn_;
    std::string author_;
};

#endif