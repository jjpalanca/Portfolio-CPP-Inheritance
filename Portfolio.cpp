/*
 * Portfolio.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: mercer and Jessmer John Palanca
 */
#include <string>
#include <iostream>
#include <vector>
#include <iomanip> // setprecision
#include <memory>

using namespace std;

class Asset {

    // All Assets have a name and a value
protected:
    string name;
    double value;

    // Return amt rounded to 2 decimal places.
    // This function may be used by all subclasses (or write your own in each)
    double rounded(double amt) {
        return ((int) (amt * 100.0)) / 100.0;
    }

public:
    // This constructor must be called from all subclasses like this for BankAccount:
    //
    //   BankAccount(string assetName, double startBalance) :
    //     Asset(assetName), balance(startBalance) {
    //   }
    Asset(string assetName, double currentValue) {
        name = assetName;
        value = currentValue;
    }

    string toString() {
        string part = to_string(rounded(getValue()));
        int dot = part.find(".");
        part = part.substr(0, dot + 3);  // remove trailing zeros
        return name + ": " + part;
    }

    string getName() {
        return name;
    }

    // Abstract methods like this must be implemented by any
    // class that is derived by this abstract class Asset.
    // And if you do not give this a default implementation, you get a CT error!
    // This function is never used.
    virtual double getValue() {
        return -99.99;
    }

    // Base classes ordinarily should define a virtual destructor.
    // Virtual destructors are needed even if they are never used.
    // If we don't make a base class non-virtual destructor,
    // we can't delete an object by pointer to the base class.
    virtual ~Asset() = default;
};

/////////////////////////////////////////////
class BankAccount : public Asset {

public:

    BankAccount(string assetName, double currentBalance) :
            Asset(assetName, currentBalance) {
    }

    double getValue() {
        return rounded(value);
    }

    void deposit(double amt) {
        value += amt;
    }

    void withdraw(double amt) {
        value -= amt;
    }

};


///////////////////////////////////////////
// Complete class bond, no new methods here
class Bond : public Asset {
public:
    Bond(string assetName, double startAmount) :
            Asset(assetName, startAmount) {

    };

    double getValue() {
        return value;
    }
};

////////////////////////////////////////////////////////////
// TODO Complete class Stock. Two new methods added here.
// Two new data members added: shares and price
// Override getValue to return shares * price
class Stock : public Asset {
private:
    int shares;
    double price;
public:
    Stock(string stockName, int _share, double _price) :
            Asset(stockName, _price * _share) {
        shares = _share;
        price = _price;
    };

    void changeShares(int newShares) {
        shares = newShares;
    }

    void changePrice(double newPrice) {
        price = newPrice;
    }

    double getValue() override {
        return shares * price;
    }
};

///////////////////////////////////////////
// Complete class Portfolio. Here are two function headings
// you need that use smart pointers (there are others)
//
//  1. void add(const std::shared_ptr<Asset> & asset) 
//  2. std::shared_ptr<Asset> & get(int index)
class Portfolio {
private:
    string portfolioName;
    vector<shared_ptr<Asset>> portfolio;
public:
    Portfolio(string name) {
        portfolioName = name;
    }

    void add(const std::shared_ptr<Asset> &asset) {
        portfolio.push_back(asset);
    }

    shared_ptr<Asset> &get(int index) {
        return portfolio[index];
    }

    double getValue() {
        double total = 0;
        for (auto x: portfolio) {
            total += x->getValue();
        }
        return total;
    }

    void showAll() {
        for (auto x: portfolio) {
            cout << x->getName() << ": " << x->getValue() << endl;
        }
    }
};

int main() {
    auto acct = shared_ptr<BankAccount>(new BankAccount("an account", 50.00));
    auto stock = shared_ptr<Stock>(new Stock("a stock", 50, 10.0));
    auto bond = shared_ptr<Bond>(new Bond("a bond", 5000));

    Portfolio portfolio("My Portfolio");
    // Just as we can convert an ordinary pointer to a derived type to a pointer to a base-class type,
    // we can also convert a smart pointer to a derived type to a smart pointer to a base-class type.
    // All of the elements of portfolio have the same type, a shared_ptr<Asset>
    portfolio.add(acct);
    portfolio.add(stock); //  void add(const std::shared_ptr<Asset> & asset)
    portfolio.add(bond);  //  Now we can call push_back(asset)

    acct->withdraw(50.00);
    acct->deposit(1.23);

    stock->changeShares(10);
    stock->changePrice(7.00);

    // Can access an ele,ents directly with get
    cout << portfolio.get(0)->getName() << ": " << portfolio.get(0)->getValue() << "\n";
    cout << portfolio.get(1)->getName() << ": " << portfolio.get(1)->getValue() << "\n";
    cout << portfolio.get(2)->getName() << ": " << portfolio.get(2)->getValue() << "\n";
    cout << "\n";

    // Use a loop to show all Assets
    portfolio.showAll();

    // Use a loop to total the value of all Assets.
    cout << "\nPortfolio's Total Value: ";
    std::cout << fixed << setprecision(2) << portfolio.getValue();
}