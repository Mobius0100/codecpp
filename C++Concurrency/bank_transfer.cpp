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
        mMoney += amount;
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
};

class Bank {
public:
    void addAccount(Account* account) {
        mAccounts.insert(account);
    }

    bool transferMoney(Account* accountA, Account* accountB, double amount) {
        lock_guard<mutex> guardA(*accountA->getLock());
        lock_guard<mutex> guardB(*accountB->getLock());

        if (amount > accountA->getMoney()) { // ②
        return false;
        }

        accountA->changeMoney(-amount); // ③
        accountB->changeMoney(amount);
        return true;
    }

    // 避免死锁
    bool transferMoney_(Account* accountA, Account* accountB, double amount) {
        // 使用 std::lock() 锁定两个账户对象，确保按照相同的顺序进行锁定，避免死锁
        std::lock(*accountA->getLock(), *accountB->getLock());

        // 使用 std::lock_guard 代替 lock_guard，以便在函数退出时自动释放锁
        std::lock_guard<std::mutex> guardA(*accountA->getLock(), std::adopt_lock); // 使用 std::adopt_lock 表示锁已经被锁定
        std::lock_guard<std::mutex> guardB(*accountB->getLock(), std::adopt_lock);

        if (amount > accountA->getMoney()) {
            return false;
        }

        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
        return true;
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
        if (bank->transferMoney(accountA, accountB, randomMoney)) {
            sCoutLock.lock();
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                << " to " << accountB->getName()
                << ", Bank totalMoney: " << bank->totalMoney() << endl;
            sCoutLock.unlock();
        } else {
            sCoutLock.lock();
            cout << "Transfer failed, "
                << accountA->getName() << " has only " << accountA->getMoney() << ", but "
                << randomMoney << " required" << endl;
            sCoutLock.unlock();
        }
        
    }
}

int main() {
    Account a("Paul", 10000);
    Account b("Moira", 10000);

    Bank aBank;
    aBank.addAccount(&a);
    aBank.addAccount(&b);

    thread t1(randomTransfer, &aBank, &a, &b);
    thread t2(randomTransfer, &aBank, &b, &a);

    t1.join();
    t2.join();

    return 0;
}