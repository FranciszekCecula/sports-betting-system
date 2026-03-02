#ifndef Event_hpp
#define Event_hpp

#include <string>
#include <iostream>

using namespace std;

enum class SportType{
    Football,
    Basketball,
    Nfl,
};

class Event {
    private:
        int event_id;
        string team1;
        string team2;
        SportType sport;
        int points_team1;
        int points_team2;

        double odds_team1;
        double odds_team2;
        double odds_draw;

        bool draw_possible;
        bool status; //false->active true->finished
        int result; // 1 -> team1 wins, 2 -> team2 wins, 0 -> draw

    public:
        Event(int event_id, string team1, string team2, SportType sport, double odds_team1, double odds_team2, double odds_draw, bool draw_possible);

        int get_event_id() const;
        string get_team1() const;
        string get_team2() const;
        SportType get_sport() const;

        double get_odds_team1() const;
        double get_odds_team2() const;
        double get_odds_draw() const;
        
        bool is_draw_possible() const;
        bool get_status() const;
        int get_result() const;

        void set_result(int p1, int p2);
        void display_event() const;

        int get_points_team1()const;
        int get_points_team2()const;

        
        


};
#endif// Event.hpp