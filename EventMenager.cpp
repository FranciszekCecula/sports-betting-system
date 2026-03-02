#include <iostream>
#include <fstream>
#include "EventMenager.hpp"

using namespace std;

shared_ptr<Event> EventMenager::add_event(string team1, string team2, SportType sport, double odds_team1, double odds_team2, double odds_draw, bool draw_possible){
    shared_ptr<Event> new_event = make_shared<Event>(next_event_id,team1, team2, sport, odds_team1, odds_team2, odds_draw, draw_possible);
    events.push_back(new_event);
    next_event_id++;

    cout<<"Event added successfully. ID: "<<new_event->get_event_id()<<endl;
    return new_event;

}

shared_ptr<Event> EventMenager::find_by_id(int event_id){
    for (shared_ptr<Event>event : events){
        if(event->get_event_id()==event_id){
            return event;
        }
    }
    
    return nullptr;
    //cout<<"Event with ID" <<event_id<<" not found."<<endl;
        
    
}

void EventMenager::list_events() const{
    if(events.empty()){
        cout<<"No events available.\n";
        return;
    }
    cout<<"\n=== Event List ===\n";
    for(shared_ptr<Event> event : events){
        event->display_event();
        cout<<"------------------\n";
    }
}

void EventMenager::list_active_events()const{
    bool found = false;
    for(shared_ptr<Event> event : events){
        if(!event->get_status()){
            event->display_event();
            cout<<"------------------\n";
            found = true;   
        }
    }
    if(!found){
        cout<<"No active events available\n";
    }

}

bool EventMenager::set_event_result(int event_id, int points_team1, int points_team2){
    shared_ptr<Event> event = find_by_id(event_id);
    if(!event){
        cout<<"Error: Event with ID "<<event_id<<" not found\n";
        return false;
    }
    event->set_result(points_team1, points_team2);
    cout<<"Event updated successfully.\n";
    return true;
}


bool EventMenager::save_to_file(const string& filename)const{
    ofstream file(filename);
    if(!file.is_open()){
        cout << "Error: Could not open events file. \n";
        return false;
    }
    for(shared_ptr<Event>event : events){
        file << event->get_event_id()<<";"
             << event->get_team1()<< ";"
             << event->get_team2()<<";"
             << static_cast<int>(event->get_sport())<<";"
             << event->get_odds_team1()<<";"
             << event->get_odds_team2()<<";"
             << event->get_odds_draw()<<";"
             << event->is_draw_possible()<<";"
             << event->get_status()<<";"
             << event->get_points_team1()<<";"
             << event->get_points_team2()<<";"
             << event->get_result()<<";"
             << "\n";
    }
    file.close();
    return true;

}

bool EventMenager::load_from_file(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout<<"Error: Events file not found"<<endl;
        return false;
    }

    events.clear();

    string line;
    while (getline(file,line)){
        size_t pos[12];
        int idx =0;

        size_t start =0;
        for (int i=0; i<12; i++){
            pos[i]=line.find(';',start);
            start=pos[i]+1;
        }
        auto read =[&](int i){
            size_t p0 = (i== 0 ? 0 : pos[i-1]+1);
            size_t p1 = pos[i];
            return line.substr(p0,p1-p0);
        };

        int id = stoi(read(0));
        string team1 = read(1);
        string team2 = read(2);
        SportType sport = static_cast<SportType>(stoi(read(3)));
        double odds_team1 = stod(read(4));
        double odds_team2 = stod(read(5));
        double odds_draw = stod(read(6));
        bool draw_possible = stoi(read(7));
        bool status = stoi(read(8));
        int points_team1 = stoi(read(9));
        int points_team2 = stoi(read(10));
        int result = stoi(read(11));

        shared_ptr<Event> event = make_shared<Event>(id,team1,team2,sport,odds_team1,odds_team2,odds_draw,draw_possible);

        if(status){
            event->set_result(points_team1,points_team2);
            
        }

         events.push_back(event);
         
        if(id>=next_event_id){
            next_event_id = id+1;
        }
    }
file.close();
return true;

}

bool EventMenager::delete_event(int event_id){
    for (auto it = events.begin(); it !=events.end(); ++it){
        if((*it)->get_event_id() == event_id){
        events.erase(it);
        cout<<"Event with ID: "<< event_id<<" successfully deleted.\n";
        return true;
        }
    }
    cout <<"Error: Event with ID: "<< event_id<<" not found./n";\
    return false;
}