#include "mydatastore.h"
#include "util.h"
#include <set>
#include <algorithm>
#include <cctype>

// ctor dtor
MyDataStore::MyDataStore(){
}
MyDataStore::~MyDataStore(){
  for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }
  for(std::vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete *it;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  // as we add a product identify its keywords
  std::set<std::string> keys = p->keywords();
  for(std::set<std::string>::iterator it = keys.begin(); it != keys.end(); ++it){
    std::string lowerKey = convToLower(*it);
    keywords_[lowerKey].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  std::string username = convToLower(u->getName());
  // create an empty cart
  cart_[username] = std::vector<Product*>();
}

// and search type = 0, or search type = 1
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::set<Product*> results;
  bool first = true;
  for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
    std::string term = convToLower(*it);
    if(keywords_.find(term) != keywords_.end()){
      // term is found, do and/or search
      if(first){
        results = keywords_[term];
        first = false;
      } else {
        if(type == 0){
          results = setIntersection(results, keywords_[term]);
        } else {
          results = setUnion(results, keywords_[term]);
        }
      }
    } else {
      // term is not found, break if AND search
      if(type == 0){
        results.clear();
        break;
      }
    }
  }
  // convert set to vector
  std::vector<Product*> resultV(results.begin(), results.end());
  return resultV;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    // dump the product according to class
    (*it)->dump(ofile);
  }

  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;
  for(std::vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    // users are dumped in the same format
    (*it)->dump(ofile);
    // ofile << (*it)->getName() << " " << std::fixed << std::setprecision(2) << (*it)->getBalance() << " " << "0" << std::endl;
  }
  ofile << "</users>" << std::endl;
}

bool MyDataStore::addCart(const std::string& username, int index, const std::vector<Product*>& searchResults){
  std::string lowname = convToLower(username);
  // look for cart with the username, user not found or invalid index
  if(cart_.find(lowname) == cart_.end() || index < 1){
    std::cout << "Invalid request" << std::endl;
    return false;
  }
  Product* p = searchResults[index - 1];
  cart_[lowname].push_back(p);
  return true;
}

void MyDataStore::viewCart(const std::string& username) const {
  std::string lowname = convToLower(username);
  if(cart_.find(lowname) == cart_.end()){
    // not found, output invalid
    std::cout << "Invalid username" << std::endl;
  } else {
    const std::vector<Product*>& cart = cart_.at(lowname);
    int index = 1;
    // if found, iter thru vector for all products in cart
    for(std::vector<Product*>::const_iterator it = cart.begin(); it != cart.end(); ++it){
      std::cout << "Item " << index << std::endl << (*it)->displayString() << std::endl;
      ++index;
    }
  }
}

void MyDataStore::buyCart(const std::string& username){
  std::string lowname = convToLower(username);
  User* user = nullptr;
  for(std::vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    // look for user
    if(convToLower((*it)->getName()) == lowname){
      user = *it;
      break;
    }
  }
  if(user == nullptr || cart_.find(lowname) == cart_.end()){
    std::cout << "Invalid username" << std::endl;
  }

  std::vector<Product*>& cart = cart_[lowname];
  // in case not all can be bought
  std::vector<Product*> restCart;
  for(std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it){
    Product* p = *it;
    // user has enough money and in stock
    if(p->getQty() > 0 && user->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    } else {
      // skip item 
      restCart.push_back(p);
    }
  }

  cart_[lowname] = restCart;
}