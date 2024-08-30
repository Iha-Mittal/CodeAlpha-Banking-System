#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class to represent a transaction
class Transaction {
public:
    string type;  // Type of transaction (Deposit/Withdrawal)
    double amount; // Amount involved in the transaction
    Transaction(const string& t, double a) : type(t), amount(a) {}
};

// Class to represent a bank account
class Account {
public:
    Account(const string& owner, double initialBalance)
        : owner(owner), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction("Deposit", amount));
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid or insufficient funds for withdrawal!" << endl;
        }
    }

    void printAccountSummary() const {
        cout << "Account Owner: " << owner << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Transactions:" << endl;
        for (const Transaction& txn : transactions) {
            cout << txn.type << ": $" << txn.amount << endl;
        }
    }

    string getOwner() const { return owner; } // Getter for owner

private:
    string owner;
    double balance;
    vector<Transaction> transactions;
};

// Class to manage customers
class Customer {
public:
    void addAccount(const string& owner, double initialBalance) {
        accounts.push_back(Account(owner, initialBalance));
    }

    Account* getAccount(const string& owner) {
        for (Account& acc : accounts) {
            if (acc.getOwner() == owner) {
                return &acc;
            }
        }
        cout << "Account not found!" << endl;
        return nullptr;
    }

private:
    vector<Account> accounts;
};

// Class to handle banking services
class BankingServices {
public:
    static void performDeposit(Account* account, double amount) {
        if (account) {
            account->deposit(amount);
        }
    }

    static void performWithdrawal(Account* account, double amount) {
        if (account) {
            account->withdraw(amount);
        }
    }
};

int main() {
    Customer customer;
    int choice;
    string username;
    double initialBalance, amount;

    cout << "Welcome to the Banking System!" << endl;

    while (true) {
        cout << "\n1. Register Account\n2. Deposit\n3. Withdraw\n4. View Account Summary\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter account owner's name: ";
            cin.ignore(); // To clear the newline character from the input buffer
            getline(cin, username);
            cout << "Enter initial balance: ";
            cin >> initialBalance;
            customer.addAccount(username, initialBalance);
            cout << "Account created successfully!" << endl;
        } else if (choice == 2) {
            cout << "Enter account owner's name: ";
            cin.ignore();
            getline(cin, username);
            Account* account = customer.getAccount(username);
            if (account) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                BankingServices::performDeposit(account, amount);
            }
        } else if (choice == 3) {
            cout << "Enter account owner's name: ";
            cin.ignore();
            getline(cin, username);
            Account* account = customer.getAccount(username);
            if (account) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                BankingServices::performWithdrawal(account, amount);
            }
        } else if (choice == 4) {
            cout << "Enter account owner's name: ";
            cin.ignore();
            getline(cin, username);
            Account* account = customer.getAccount(username);
            if (account) {
                account->printAccountSummary();
            }
        } else if (choice == 5) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}