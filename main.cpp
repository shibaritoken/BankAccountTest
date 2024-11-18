#include <iostream>
#include <map>
#include <locale.h>



class BankAccount {
public:
    BankAccount() : accountName(""), balance(0.0) {}

    BankAccount(const std::string &accountName, double balance) {
        this->accountName = accountName;
        this->balance = balance;
    };

    void deposit(double amount) {
        if(amount <= 0) {
            throw std::invalid_argument("Amount should be greater than 0");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            throw std::invalid_argument("Balance is not enough for withdraw");
        }
        balance -= amount;
    }

    std::string getAccountName() { return accountName; }
    double getBalance() const { return balance; }
private:
    std::string accountName;
    double balance;
};

class Bank {
public:
    void addAccount(const std::string &accountName, double balance) {
        if (accounts.find(accountName) != accounts.end()) {
            throw std::invalid_argument("Account already exists");
        }
        accounts[accountName] = BankAccount(accountName, balance);
    }

    BankAccount& getAccount(const std::string &accountName) {
        auto it = accounts.find(accountName);
        if (it == accounts.end()) {
            throw std::invalid_argument("Account not found");
        }
        return it->second;
    }


    void listAccounts() {
        for(auto & account : accounts) {
            std::cout << account.first << " " << account.second.getAccountName() << " -- balance:" << account.second.getBalance() << std::endl;
        }
    }
private:
    std::map<std::string, BankAccount> accounts;
};

int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");
    Bank bank;
    int choice;
    std::string clientName;
    double amount;

    while (true) {
        std::cout << "Банк: Добро пожаловать! Что вы хотите сделать?" << std::endl;
        std::cout << "1. Создать новый счёт" << std::endl;
        std::cout << "2. Внести деньги на счёт" << std::endl;
        std::cout << "3. Снять деньги со счёта" << std::endl;
        std::cout << "4. Проверить баланс" << std::endl;
        std::cout << "5. Посмотреть список клиентов" << std::endl;
        std::cout << "6. Выйти" << std::endl;

        std::cout << "Введите номер операции: ";
        std::cin >> choice;

        try {
            switch (choice) {
            case 1: {
                std::cout << "Введите имя клиента: ";
                std::cin >> clientName;
                std::cout << "Введите начальный баланс: ";
                std::cin >> amount;
                bank.addAccount(clientName, amount);
                break;
            }
            case 2: {
                std::cout << "Введите имя клиента: ";
                std::cin >> clientName;
                std::cout << "Введите сумму для внесения: ";
                std::cin >> amount;
                bank.getAccount(clientName).deposit(amount);
                break;
            }
            case 3: {
                std::cout << "Введите имя клиента: ";
                std::cin >> clientName;
                std::cout << "Введите сумму для снятия: ";
                std::cin >> amount;
                bank.getAccount(clientName).withdraw(amount);
                std::cout << "Операция успешна! Баланс: " << bank.getAccount(clientName).getBalance() << std::endl;
                break;
            }
            case 4: {
                std::cout << "Введите имя клиента: ";
                std::cin >> clientName;
                std::cout << "Баланс: " << bank.getAccount(clientName).getBalance() << std::endl;
                break;
            }
            case 5: {
                bank.listAccounts();
                break;
            }
            case 6:
                std::cout << "Выход из программы." << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}