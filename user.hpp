#include <iostream>
#include <string>

#ifndef USER_HPP
#define USER_HPP

using namespace std;


class User {
private:
    friend class Menager;

    string get_password_hash() const;
    void force_hash(const string& hash);

    string username;
    string password_hash;
    double balance;
    bool admin;

    string simple_hash(const string& input) const;

public:
    User(const string& username, const string& password, double balance=0.0, bool admin=false); 

    const string& get_username() const;
    double get_balance() const;
    bool get_admin() const;
    //string get_password_hash() const;

    bool check_password(const string& password) const;
    bool change_password(const string& old_password, const string& new_password);
    void deposit (double money);
    bool paycheck(double money);
    void withdraw(double amount);
    
};

#endif 
