#ifndef BetMenager_hpp
#define BetMenager_hpp

#include <vector>
#include <memory>
#include <string>
#include "Bet.hpp"
#include "Menager.hpp"

class Event;

class BetMenager{
    private:
    vector<shared_ptr<Bet>>bets;
    int next_bet_id;

    public:
    BetMenager();
    shared_ptr<Bet>create_bet(const shared_ptr<Event>& event, const string& username, double amount, int result);
    const vector <shared_ptr<Bet>>& get_bets() const;

    bool save_to_file(const string& filename="Bets.txt");
    bool load_from_file(const string& filename="Bets.txt");

    int get_next_bet_id()const;

    void list_active_bets_for_user(const string& username)const;
    void history_bet_for_user (const string& username)const;

    void bets_results_for_event(const shared_ptr<Event>&event, Menager& userMenager);

};



#endif //BetMenager_hpp