#ifndef Menager_hpp
#define Menager_hpp

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "User.hpp"
#include <fstream>

using namespace std;

class Menager{
    private:
        vector<shared_ptr<User>> users;
    
    public:
        shared_ptr<User> find_by_username(const string& username);
        Menager();
        bool register_user(const string& username, const string& password, bool admin=false);
        shared_ptr<User> login_user(const string& username, const string& password);

        void list_users() const; //funkcja pomocnicza do testow
        
        bool load_from_file(const string& filename = "users.txt");
        bool save_to_file(const string& filename = "users.txt") const;

        bool delete_user(const string& username);
};
#endif /* Menager_hpp */