#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <string>
#include <set>
#include <map>
#include <vector>

class MyDataStore : public DataStore{
  public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    bool addCart(const std::string& username, int index, const std::vector<Product*>& searchResults);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);

  private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    // this map maps keywords to products helping search
    std::map<std::string, std::set<Product*>> keywords_;
    //this map maps users' carts to products
    std::map<std::string, std::vector<Product*>> cart_;
};

#endif