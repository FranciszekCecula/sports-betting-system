#include <iostream>
#include <string>
#include "Bet.hpp"

using namespace std;

Bet::Bet(int bet_id, int event_id,string username, double amount, int result):
bet_id(bet_id),
event_id(event_id),
username(username),
amount(amount),
result(result),
settled(false),
payout(0.0) 
{}

int Bet::get_bet_id()const{
    return bet_id;
}

int Bet::get_event_id()const{
    return event_id;
}

const string& Bet::get_username()const{
    return username;
} 

double Bet::get_amount()const{
    return amount;
} 

bool Bet::is_settled()const{
    return settled;
}

double Bet::get_payout() const{
    return payout;
}

int Bet::get_result()const{
    return result;
}

void Bet::settle(bool win,double odds){
    settled=true;
    if(win){
        payout=amount*odds;
    }
    else{
        payout=0.0;
    }
}


