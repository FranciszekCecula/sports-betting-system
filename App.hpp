#ifndef App_hpp
#define App_hpp

#include <memory>
#include "Menager.hpp"
#include <iostream>
#include "EventMenager.hpp"
#include "AdminApp.hpp"
#include "UserApp.hpp"


using namespace std;

class App{
    private:
    Menager menager;
    EventMenager eventMenager;
    AdminApp adminApp;
    UserApp userApp;
    BetMenager betMenager;

    void main_menu();
    void user_menu(shared_ptr<User> user);
    void admin_menu(shared_ptr<User> user);

    public:
    App();
    void run();
};

#endif