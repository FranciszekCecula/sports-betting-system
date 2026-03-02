#include <iostream>
#include "Menager.hpp"
#include <fstream>

using namespace std;

Menager::Menager(){
    load_from_file("users.txt");

    if(find_by_username("admin")==nullptr){
        register_user("admin","FRANCIk85@",true);
        save_to_file("users.txt");
        cout<<" Defaul admin account created. "<<endl;
    }
}

shared_ptr<User> Menager::find_by_username(const string& username){
    for (auto &user : users) {

        if( user->get_username() == username ){
            return user;
        }
    }
    return nullptr;
        
}

bool Menager::register_user (const string& username, const string& password, bool admin){
    if (find_by_username(username) !=nullptr){
        cout << "The username is already taken. Please choose different one" << endl;
        return false;
    }
try{
    shared_ptr<User> new_user = make_shared<User>(username, password,0.0,admin);
    users.push_back(new_user);
    cout<< "User " << username << " registered successfully." << endl;
    return true;
}
catch(const invalid_argument& e){
    cout << "Error registering user"<< endl;
    return false;
}
}

shared_ptr<User> Menager::login_user(const string& username, const string& password){
    shared_ptr<User> user =find_by_username(username);
    if (user == nullptr){
        cout << "Login failed: user not found" << endl;
        return nullptr;
    }
    if( user->check_password(password)){
        cout << "Login successful. Welcome, " << username << "!" << endl;
        return user;
    }
    else{
        cout << "Login failed: incorrect password" << endl;
        return nullptr;
    }
}

void Menager::list_users() const{
    cout<< " \n Users:" <<endl;
    for (const shared_ptr<User> &user : users){
        cout <<" - " << shared_ptr<User> (user)->get_username()
            << (shared_ptr<User> (user)->get_admin() ? " (admin)" : "") << "\n";
            
    }
}


bool Menager::save_to_file(const string& filename)const{
    ofstream file(filename);
    if(!file.is_open()){
        cout<<"Error could not open the file" <<endl;
        return false;
    }
    for (const shared_ptr<User> user : users){
        file <<user->get_username()<<";"
             <<user->get_password_hash()<<";"
             <<user->get_balance()<<";"
             <<user->get_admin() << "\n";
    }
    file.close();
    return true;

}

bool Menager::load_from_file(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout <<"Warning: users file not found. "<<endl;
        return false;
    }

    users.clear();

    string line;
    while (getline (file,line)){
        string username, hash, balance_read, admin_read;

        size_t pos1= line.find(';');
        size_t pos2= line.find(';', pos1+1);
        size_t pos3= line.find(';', pos2+1);

        username =line.substr(0,pos1);
        hash = line.substr(pos1+1,pos2-pos1-1);
        balance_read = line.substr(pos2+1,pos3-pos2-1);
        admin_read = line.substr(pos3+1);

        double balance = stod(balance_read);
        bool admin = (admin_read =="1");
        
        shared_ptr<User> user = make_shared<User>(username, "SystemPassword", balance, admin);
        user-> force_hash(hash);
        users.push_back(user);
    }
    file.close();
    return true;

}

bool Menager::delete_user(const string& username){
    for (auto it = users.begin(); it !=users.end(); ++it){

        if((*it)->get_username()==username){
            if((*it)->get_admin()){
                cout<<" Error: Cannot delete admin account. "<<endl;
                return false;
            }

            users.erase(it);
            save_to_file("users.txt");
            cout << " User " << username << " deleted succesfully. "<<endl;
            return true;
        }
    }

    cout << " Error: User not found. "<<endl;
    return false;

}



