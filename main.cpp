#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// Trace the Account Hierchy solution
#include <iostream>
/*
 * main.cpp
 *
 * This files contains a small inheritance hierarchy where
 * RegularAccount is a subclass of Account. You job is
 * to have SafeAccount be a subclass of Account also.
 *
 * Author: Rick Mercer and YOUR NAME
 */
#include <string>
#include <iostream>
#include <cmath>
#include <memory>
#include <cassert>
using namespace std;

class Account {

protected:
  string name;
  double balance;

public:
  Account(string name, double balance) : name(name), balance(balance) {
  }

  string getName() {
    return name;
  }

  double getBalance() {
    return balance;
  }

  void deposit(double amount) {
    balance += amount;
  }

  virtual void withdraw(double amount) = 0;
};

/////////////////////////////////////////////////
class RegularAccount : public Account {

public:
  RegularAccount(string initName, double initialBalance) :
          Account(initName, initialBalance) {
  }

  void withdraw(double amount) override {
    if (amount <= balance)
      balance -= amount;
  }

};

/////////////////////////////////////////////////
// TODO: Using good design, implement SafeAccount
// as a subclass of Account so the code in main
// compiles and and the asserts pass
//
class SafeAccount : public Account {

private:
  double loanAmount;

public:
  explicit SafeAccount(string initName,
                       double initialBalance) :
          Account(initName, initialBalance) {
    loanAmount = 0.0;
  }

  void withdraw(double amount) override {
    if (amount <= balance)
      balance -= amount;
    else {
      double needed = amount - balance;
      loanAmount += needed;
      balance += needed;
      balance -= amount;
    }
  }

  double getLoanAmount() {
    return loanAmount;
  }
};

// TODO: Build an Account Collection
class Accounts {
private:
  vector<shared_ptr<Account>> accounts;

public: // addAccount, and show

  void addAccount(shared_ptr<Account> const anAccountPtr) {
      accounts.push_back(anAccountPtr);
  }

  void show() {
    for(auto account : accounts) {
      cout << account->getName() << " has " << account->getBalance() << endl;
    }
  }
};


int main() {

  // CODE DEMO:
  Accounts all;
  shared_ptr<RegularAccount> acct1 = shared_ptr<RegularAccount>
          (new RegularAccount{"One", 1.11});
  shared_ptr<SafeAccount> acct2 = shared_ptr<SafeAccount>(
          new SafeAccount{"Two", 2.22});

  all.addAccount(acct1);
  all.addAccount(acct2);
  all.show();


  // Use a smart pointer just for the fun of it
  unique_ptr<RegularAccount> a = make_unique<RegularAccount>("Five", 5.55);
  assert("Five" == a->getName());
  assert (5.55 == a->getBalance());

  RegularAccount reg{"Kim", 7777.77};
  reg.deposit(44.00);
  assert("Kim" == reg.getName());
  assert(7821.77 == reg.getBalance());

  SafeAccount saf{"Chris", 111.11};
  saf.deposit(33.00);
  assert("Chris" == saf.getName());
  assert( 144.11 == saf.getBalance());
  assert(0.00 == saf.getLoanAmount());

  saf.withdraw(55.00);
  assert(0.0 == saf.getLoanAmount());
  assert(std::abs(89.11 - saf.getBalance()) < 0.1e-8);
  saf.withdraw(200.00);
  assert(std::abs(110.89 - saf.getLoanAmount()) < 0.1e-8);
  assert(0.0 == saf.getBalance());








}
