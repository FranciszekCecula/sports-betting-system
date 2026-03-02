#ifndef UserApp_hpp
#define UserApp_hpp

#include <iostream>
#include <memory>
#include "EventMenager.hpp"
#include "Menager.hpp"
#include "BetMenager.hpp"


using namespace std;

class UserApp{
    private:

    Menager& menager;
    EventMenager& eventMenager;
    BetMenager& betMenager;
   
    

    void show_balance(shared_ptr<User>&user)const;
    void deposit(shared_ptr<User>&user);
    void paycheck(shared_ptr<User>&user);
    void change_password(shared_ptr<User>&user);
    void list_events()const;
    void place_bet(shared_ptr<User> user);
    void list_active_bets(shared_ptr<User>&user);
    void list_bets_history(shared_ptr<User>&user);

    public:

    UserApp(Menager& menagerRef, EventMenager& eventMenagerRef, BetMenager& betMenagerRef);
    void run (shared_ptr<User>&user);
};



#endif //UserApp_hpp