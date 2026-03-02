#ifndef AdminApp_hpp
#define AdminApp_hpp

#include <memory>
#include <iostream>
#include <string>

#include "Event.hpp"
#include "user.hpp"
#include "EventMenager.hpp"
#include "Menager.hpp"
#include "BetMenager.hpp"

using namespace std;

class AdminApp{
    private:
    Menager &menager;
    EventMenager &eventMenager;
    BetMenager& betMenager; 

    void list_users() const;
    void delete_users();
    void list_events() const;
    void create_event();
    void set_result();
    void save_event()const;
    void load_event();
    void delete_event();

    public:
    AdminApp(Menager &menagerRef, EventMenager &eventMenagerRef, BetMenager &betMenager);

    void run(const shared_ptr<User> &admin_user);

};




#endif //AdminApp_hpp