#include <iostream>
#include "App.hpp"

using namespace std;

App::App():
menager(),
eventMenager(),
betMenager(),
adminApp(menager,eventMenager,betMenager),
userApp(menager,eventMenager,betMenager)
{menager.load_from_file();eventMenager.load_from_file();betMenager.load_from_file();};

void App::run(){
    main_menu();
}

void App::main_menu(){
    bool running = true;
    while (running){
        cout << "\n=== MENU ===\n";
        cout << "1)Register\n2)Login\n3)List users\n4)Exit\n";
        cout <<"Choose an option:";
        int choice;
        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(100000, '\n');
            cout <<" Invalid input. Please enter valid number."<<endl;

        }
        if(choice==1){
            string user_name; 
            string pass_word;
            cout << "Enter username: "<<endl;
            cin >> user_name;
            cout << "Enter password "<<endl;
            cin >> pass_word;
            menager.register_user(user_name, pass_word,false);
            menager.save_to_file();
        }
        
        else if(choice==2){
            string user_name;
            string pass_word;
            cout << "Enter username: "<<endl;
            cin >> user_name;
            cout << "Enter password"<<endl;
            cin >> pass_word;
            shared_ptr<User> user=menager.login_user(user_name, pass_word);
            if(user){
                user_menu(user);
            }
    }
         else if(choice==3){
             menager.list_users();
        }   

        else if(choice==4){
            running=false;
        }
    }
        cout <<"Exiting...\n";
        
    
 }

 void App::user_menu(shared_ptr<User> user){
    
    if (user->get_admin()){
        admin_menu(user);
        return;
    }
    
   userApp.run(user);

 }

void App::admin_menu(shared_ptr<User> user){
    adminApp.run(user);
}
