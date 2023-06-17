/*
    
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <thread>
#include <mutex>

using namespace std;
    

class Account {
public:
    Account(string name, double money): mName(name), mMoney(money) {};

    void changeMoney(double amount) {
        unique_lock<mutex> lock(mMoneyLock);
        mConditionVar.wait(lock, [this, amount]{
            return mMoney + amount > 0;
        });
        mMoney += amount;
        mConditionVar.notify_all();
    }

    string getName() {
        return mName;
    }
    double getMoney() {
        return mMoney;
    }
    mutex* getLock() {
        return &mMoneyLock;
    }
private:
    string mName;
    double mMoney;
    mutex mMoneyLock;
    condition_variable mConditionVar;
};

class Bank {
public:
    void addAccount(Account* account) {
        mAccounts.insert(account);
    }

    void transferMoney(Account *accountA, Account *accountB, double amount){
        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
    }

    double totalMoney() const {
        double sum = 0;
        for (auto a : mAccounts) {
        sum += a->getMoney();
        }
        return sum;
  }

private:
    set<Account*> mAccounts;
};

// 为输出加锁
mutex sCoutLock;
void randomTransfer(Bank* bank, Account* accountA, Account* accountB) {
    while(true) {
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        {
            lock_guard<mutex> guard(sCoutLock);
            cout << "Try to Transfer " << randomMoney
                 << " from " << accountA->getName() << "(" << accountA->getMoney()
                 << ") to " << accountB->getName() << "(" << accountB->getMoney()
                 << "), Bank totalMoney: " << bank->totalMoney() << endl;
        }
        bank->transferMoney(accountA, accountB, randomMoney);
    }
}

int main() {
    Account a("Paul", 100);
    Account b("Moira", 100);

    Bank aBank;
    aBank.addAccount(&a);
    aBank.addAccount(&b);

    thread t1(randomTransfer, &aBank, &a, &b);
    thread t2(randomTransfer, &aBank, &b, &a);

    t1.join();
    t2.join();

    return 0;
}