#include <iostream>
#include "user.hpp"

using namespace std;

string User::simple_hash(const string& input) const{
    string result= "Hash_";
    for(char c : input){
        result += char(c+1);
    }
    return result;
}

User::User(const string& username, const string& password, double balance, bool admin){
    if(username.empty()){
        cout<< "Error: Username cannot be empty!" << endl;
        throw invalid_argument("Enter the username!");
    }

    if (password.length() < 6) {
        cout<< "Error: Password must be at least 6 characters long!" << endl;
        throw invalid_argument("Password must be at least 6 characters long!");
    }

    if(balance < 0.0){
        cout<< "Error: Initial balance cannot be negative!" << endl;
        throw invalid_argument("Initial balance cannot be negative!");
    }
    this->username = username;
    this->password_hash = simple_hash(password);
    this->balance = balance;
    this->admin = admin;
}

const string& User::get_username() const{
    //cout << "Username:" << username << endl;
    return username; 
} 

string User::get_password_hash() const {
    return password_hash;
}

double User::get_balance() const{
    return balance;
}
bool User::get_admin()const{
    return admin;
}
bool User::check_password(const string& password) const {
   
    if (simple_hash(password)==password_hash){

    return (simple_hash(password) == password_hash);
   }
    else {
    return false;
    }
   }

bool User::change_password (const string& old_password, const string& new_password){
    if(!check_password(old_password)){
        cout<< "Error : Password is incorrect" <<endl;
        return false;
    }
    if(new_password.length()<6){
        cout<< "Error: New password must be at least 6 characters long!" << endl;
        return false;
    }
    password_hash = simple_hash(new_password);
    cout<< "Password changed successfully!" << endl;
    return true;
}


void User::deposit(double money){
    if(money>0){
    balance +=money;
     cout<<"Succesfull deposit! "<<endl;
     cout<<"Balnce after deposit = " <<   balance <<endl;
    }
    else{
    cout<<"Error: Enter positive value to deposit!"<<endl;

    }
  
}

bool User::paycheck(double money){
    if(money <=0){
        cout<<"Error: Enter positive value to withdraw!"<<endl;
        return false;

    }
    if(money > balance){
        cout<<"Error: Insufficient funds for this operation!"<<endl;
         return false;
       

    }
    else{
        balance -=money;
        cout<<"Withdrawal completed. Balance after paycheck = " << balance <<endl;
        return true;
    }
}

void User::force_hash(const string& hash){
        password_hash = hash;
}
 void User::withdraw(double amount){
    if (amount <=0){
        cout<<"Error: Cannot withdraw negative or zero amount "<<endl;

    }

    if (amount>balance){
        cout<<"Error: Insuficient funds for this operation "<<endl;
    }

    balance -= amount;
    cout<<"Balance after placing a bet: "<<balance<<endl;
 }
 
