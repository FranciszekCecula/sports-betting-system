#ifndef Bet_hpp
#define Bet_hpp

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Bet{
    private:
    int bet_id;
    int event_id;
    string username;
    double amount;
    int result;
    bool settled;
    double payout;

    public:

    Bet(int bet_id, int event_id, string username, double amount, int result );

    int get_bet_id()const;
    int get_event_id()const;
    const string& get_username()const;
    double get_amount()const;
    int get_result()const;
    double get_payout()const;
    
    bool is_settled()const;
    void settle(bool win,double odds);
    
};



#endif //Bet_hpp
