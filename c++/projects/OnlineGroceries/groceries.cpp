#include "split.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct Customer {
  int id;
  std::string name;
  std::string address;
  std::string city;
  std::string state;
  std::string zip;
  std::string phone;
  std::string email;

  void PrintDetail() const {
    std::cout << "Customer ID #" << id << ":" << std::endl;
    std::cout << name << ", ph. " << phone << ", email: " << email << std::endl;
    std::cout << address << std::endl;
    std::cout << city << ", " << state << " " << zip << "\n" << std::endl;
  }
};
struct Item {
  int id;
  std::string desc;
  double price;
};

std::vector<Customer> customers;
std::vector<Item> items;

const Customer *CustomerLookup(const int &id) {
  for (const auto &customer : customers) {
    if (customer.id == id)
      return &customer;
  }
  return nullptr;
}

const Item *ItemLookup(const int &id) {
  for (const auto &item : items) {
    if (item.id == id)
      return &item;
  }
  return nullptr;
}

class LineItem {
private:
  int itemID;
  int qty;

public:
  LineItem(int id, int quantity) : itemID(id), qty(quantity) {}

  double subTotal() const {
    const Item *item = ItemLookup(itemID);
    return item->price * qty;
  }

  friend bool operator<(const LineItem &item1, const LineItem &item2) {
    return item1.itemID < item2.itemID;
  }
  int getID() const { return itemID; }
  int getQTY() const { return qty; }
};

void ReadCustomers(std::string fileName) {
  Customer c;
  std::ifstream inputFile;
  std::string rawLine;

  inputFile.open(fileName);
  while (std::getline(inputFile, rawLine)) {
    std::vector<std::string> splitLine = split(rawLine, ',');
    if (splitLine.size() == 8) {
      c.id = std::stoi(splitLine[0]);
      c.name = splitLine[1];
      c.address = splitLine[2];
      c.city = splitLine[3];
      c.state = splitLine[4];
      c.zip = splitLine[5];
      c.phone = splitLine[6];
      c.email = splitLine[7];
      customers.push_back(c);
    }
  }
  inputFile.close();
}

void ReadItems(std::string fileName) {
  Item i;
  std::ifstream inputFile;
  std::string rawLine;

  inputFile.open(fileName);
  while (std::getline(inputFile, rawLine)) {
    std::vector<std::string> splitLine = split(rawLine, ',');
    if (splitLine.size() == 3) {
      i.id = std::stoi(splitLine[0]);
      i.desc = splitLine[1];
      i.price = std::stod(splitLine[2]);
      items.push_back(i);
    }
  }
  inputFile.close();
}

class Payment {
protected:
  double amount;

public:
  Payment(double amt) : amount(amt) {}
  virtual ~Payment() {}
  virtual std::string printDetail() const = 0;
  friend class Order;
};

class Credit : public Payment {
private:
  std::string cardNumber;
  std::string expiration;

public:
  Credit(double amt, const std::string &card, const std::string &exp)
      : Payment(amt), cardNumber(card), expiration(exp) {}
  std::string printDetail() const override {
    return "Amount: $" + std::to_string(amount) + ", Paid by Credit card " +
           cardNumber + ", exp. " + expiration;
  }
};

class PayPal : public Payment {
private:
  std::string paypalID;

public:
  PayPal(double amt, const std::string &ppID) : Payment(amt), paypalID(ppID) {}
  std::string printDetail() const override {
    return "Amount: $" + std::to_string(amount) +
           ", Paid by Paypal ID: " + paypalID;
  }
};

class WireTransfer : public Payment {
private:
  std::string bankID;
  std::string accountID;

public:
  WireTransfer(double amt, const std::string bID, const std::string aID)
      : Payment(amt), bankID(bID), accountID(aID) {}
  std::string printDetail() const override {
    return "Amount: $" + std::to_string(amount) +
           ", Paid by Wire transfer from Bank ID " + bankID + ", Account# " +
           accountID;
  }
};

class Order {
  int customerID;
  int orderID;
  std::string orderDate;
  std::vector<LineItem> lineItems;
  Payment *payment;

public:
  Order(int cID, int oID, std::string oDate,
        const std::vector<LineItem> &lItems, Payment *pMethod)
      : orderID(oID), orderDate(oDate), customerID(cID), lineItems(lItems),
        payment(pMethod) {}

  ~Order() { delete payment; }

  std::string printOrder() const; // defined later to avoid circular dependency
};

std::list<Order> orders;

void ReadOrders(std::string fileName) {
  std::ifstream inputFile(fileName);
  if (!inputFile.is_open()) {
    std::cerr << "Error: Failed to parse orders." << std::endl;
    return;
  }

  std::string rawLine;

  //  inputFile.open(fileName);
  while (std::getline(inputFile, rawLine)) {
    std::vector<std::string> itemFields = split(rawLine, ',');

    int cID = std::stoi(itemFields[0]);
    int oID = std::stoi(itemFields[1]);
    std::string oDate = itemFields[2];

    std::vector<LineItem> lineItems;
    for (size_t i = 3; i < itemFields.size(); ++i) {
      std::vector<std::string> cartItems = split(itemFields[i], '-');

      int itemID = std::stoi(cartItems[0]);
      int qty = std::stoi(cartItems[1]);

      lineItems.emplace_back(itemID, qty);
    }

    double totalAmount = 0.0;
    for (const auto &lineItem : lineItems) {
      totalAmount += lineItem.subTotal();
    }

    std::sort(lineItems.begin(), lineItems.end());

    std::getline(inputFile, rawLine);
    std::vector<std::string> payFields = split(rawLine, ',');
    int paymentType = std::stoi(payFields[0]);

    Payment *payment = nullptr;

    switch (paymentType) {
    case 1:
      payment = new Credit(totalAmount, payFields[1], payFields[2]);
      break;
    case 2:
      payment = new PayPal(totalAmount, payFields[1]);
      break;
    case 3:
      payment = new WireTransfer(totalAmount, payFields[1], payFields[2]);
      break;
    default:
      std::cout << "Something wrong for sure" << std::endl;
      break;
    }
    orders.emplace_back(cID, oID, oDate, lineItems, payment);
  }
  inputFile.close();
}
std::string Order::printOrder() const {
  std::string output;

  output += "===========================\n";
  output += "Order #" + std::to_string(orderID) + ", Date: " + orderDate + "\n";

  if (payment) {
    output += payment->printDetail() + "\n";
  }

  const Customer *customer = CustomerLookup(customerID);
  if (customer) {
    output += "Customer ID #" + std::to_string(customer->id) + ": " +
              customer->name + ", ph. " + customer->phone +
              ", email: " + customer->email + "\n";
    output += customer->address + "\n";
    output +=
        customer->city + ", " + customer->state + " " + customer->zip + "\n\n";
  }

  output += "Order Detail:\n";
  for (const auto &lineItem : lineItems) {
    const Item *item = ItemLookup(lineItem.getID());
    if (item) {
      std::ostringstream line;
      line << std::fixed << std::setprecision(2);

      line << "\t\tItem " << item->id << ": \"" << item->desc << "\", "
           << lineItem.getQTY() << " @ $" << item->price;

      output += line.str() + "\n";
    }
  }

  return output;
}

// ahhh how i love headers
int main() {
  ReadCustomers("customers.txt");
  ReadItems("items.txt");
  ReadOrders("orders.txt");

  std::ofstream ofs("order_report.txt");
  for (const auto &order : orders)
    ofs << order.printOrder() << std::endl;

  return 0;
}
