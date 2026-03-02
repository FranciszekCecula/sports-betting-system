#include <iostream>
#include <fstream>

#include "BetMenager.hpp"
#include "Event.hpp"

using namespace std;

BetMenager::BetMenager() : next_bet_id(1){}

shared_ptr<Bet> BetMenager::create_bet(const shared_ptr<Event>& event,const string& username,double amount,int result){
    if (!event){
        cout<< "Error: Event does not exist"<<endl;
        return nullptr;
    }
    if (event->get_status()){
        cout<<"Error: Cannot place bet on finished event"<<endl;
        return nullptr;
        
    }
    int event_id = event->get_event_id();
    shared_ptr<Bet> bet = make_shared<Bet>(next_bet_id,event_id,username,amount,result);
    bets.push_back(bet);
    next_bet_id++;
    return bet;
}

const vector <shared_ptr<Bet>>& BetMenager::get_bets()const{
    return bets;
}

bool BetMenager::save_to_file (const string& filename){
    ofstream file(filename);
    if(!file.is_open()){
        cout<<"Error: Could not open bets file. \n";
        return false;
    }
    for (shared_ptr<Bet>&bet : bets){
        file << bet->get_bet_id()<<";"
             << bet->get_event_id()<<";"
             << bet->get_username()<<";"
             << bet->get_amount()<<";"
             << bet->get_result()<<";"
             << bet->is_settled()<<";"
             << bet->get_payout()<<";"
             <<"\n";
    }
    file.close();
    return true;

}

bool BetMenager::load_from_file(const string& filename){
    ifstream file (filename);
    if(!file.is_open()){
        cout<<"Error: Bets file not found \n";
        return false;
    }
    bets.clear();

    string line;
    while (getline(file,line)){
        size_t pos[7];
        size_t start=0;

        for (int i=0; i<7; i++){
            pos[i]=line.find(';',start);
            start=pos[i]+1;
        }
        auto read =[&](int i){
            size_t p0 = (i==0 ? 0 : pos[i-1]+1);
            size_t p1 = pos[i];
            return line.substr (p0,p1-p0);
        };
        
        int bet_id = stoi(read(0));
        int event_id = stoi(read(1));
        string username = read(2);
        double amount = stod(read(3));
        int result = stod(read(4));
        bool settled = stoi(read(5));
        double payout = stod(read(6));

        shared_ptr<Bet> bet=make_shared<Bet>(bet_id,event_id,username,amount,result);

        if(settled){
            bet->settle(payout >0.0, payout/amount);
        }
        bets.push_back(bet);
        if(bet_id>=next_bet_id)
            next_bet_id=bet_id+1;
        
    }
        file.close();
        return true;
    
}

void BetMenager::list_active_bets_for_user(const string& username) const{
    cout <<"\n === YOUR ACTIVE BETS ===\n";
     bool found = false;

     for(const shared_ptr<Bet>&bet : bets){
        if(bet->get_username()==username && !bet->is_settled()){
            cout<<"Bet ID: "<<bet->get_bet_id()<<endl;
            cout<<"Event ID: "<<bet->get_event_id()<<endl;
            cout<<"Chosen result: "<<bet->get_result()<<endl;
            cout<<"Amount placed on event: "<<bet->get_amount()<<endl;
            cout<<"---------------------\n";
            found=true;
        }
     }
    if(!found){
        cout <<"You have no pending bets. \n";
    }
    }

void BetMenager::history_bet_for_user(const string& username)const{
    cout<< "\n === YOUR BETS HISTORY ===\n";
    
    bool found = false;

    for(const shared_ptr<Bet>&bet : bets){
        if(bet->get_username()==username && bet->is_settled()){
            cout<<"Bet ID: "<<bet->get_bet_id()<<endl;
            cout<<"Event ID: "<<bet->get_event_id()<<endl;
            cout<<"Chosen result: "<<bet->get_result()<<endl;
            cout<<"Amount placed on event: "<<bet->get_amount()<<endl;
            
            if (bet->get_payout()>0){
                cout <<"Result: WIN"<<endl;
                cout <<"Payout: "<<bet->get_payout()<<"$\n";

            }
            else{
                cout <<"Result: LOST\n";
            }
            cout<<"---------------------\n";
            found=true;
        }
     }
    if(!found){
        cout <<"You have no bets history. \n";
}   
}

void BetMenager::bets_results_for_event(const shared_ptr<Event>&event, Menager& userMenager){
    if(!event || !event->get_status()){
        cout<<"Error: Event is still pending! "<<endl;
        return;
    }

    int event_id= event->get_event_id();
    int event_result= event->get_result();

    cout<<"\n=== SETTING RESULT FOR BETS ===\n";
    for(const shared_ptr<Bet>&bet : bets){
        if(bet->is_settled())
            continue;
        if(bet->get_event_id()!=event_id)
        continue;
        
        bool win = (bet ->get_result()==event_result);

        double odds = 0.0;
        if (event_result==1)
            odds = event ->get_odds_team1();
        else if (event_result == 2)
            odds = event->get_odds_team2();
        else if (event_result == 0)
            odds = event->get_odds_draw();
        
        bet->settle(win, odds);

        if(win){
            shared_ptr<User>user = userMenager.find_by_username(bet->get_username());

            if (user){
                user->deposit(bet->get_payout());
            }
        }
    }
    userMenager.save_to_file();
    save_to_file();
    cout<<"Event result settled successfully"<<endl;
}