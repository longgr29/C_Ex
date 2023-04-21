#include <iostream>
#include <string>

class BankAccount {
public:
    BankAccount(unsigned long accountNumber, std::string accountName, double balance)
        : accountNumber(accountNumber), accountName(accountName), balance(balance) {}

    void withdraw(double amount);

    void deposit(double amount);

    void checkBalance() const;

private:
    unsigned long accountNumber;
    std::string accountName;
    double balance;
};

void BankAccount::withdraw(double amount) {
    if (amount > balance) {
        std::cout << "Insufficient funds" << std::endl;
    } else {
        balance -= amount;
        std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
    }
}

void BankAccount::deposit(double amount) {
    balance += amount;
    std::cout << "Deposit successful. New balance: " << balance << std::endl;
}

void BankAccount::checkBalance() const {
    std::cout << "Current balance: " << balance << std::endl;
}

int main() {
    BankAccount myAccount(9123847, "John", 1000.0);
    myAccount.checkBalance();
    myAccount.withdraw(500.0);
    myAccount.deposit(250.0);
    myAccount.checkBalance();
    return 0;
}
