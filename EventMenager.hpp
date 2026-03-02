#ifndef EventMenager_hpp
#define EventMenager_hpp

#include <vector>
#include <memory>
#include "Event.hpp"
#include <string>

using namespace std;

class EventMenager {
private:
    vector<shared_ptr<Event>> events;
    int next_event_id=1;
public:
    EventMenager() = default;
    shared_ptr<Event> add_event(string team1, string team2, SportType sport,double odds_team1, double odds_team2, double odds_draw, bool draw_possible);
    shared_ptr<Event> find_by_id(int event_id);
    void list_events() const;
    void list_active_events()const;
    bool set_event_result(int id, int points_team1, int points_team2);

    bool save_to_file(const string& filename = "events.txt") const;
    bool load_from_file(const string& filename = "events.txt");
    bool delete_event(int event_id);
    
};
#endif /* EventMenager_hpp */