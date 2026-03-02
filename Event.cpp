#include "Event.hpp" 
#include <iostream>

using namespace std;
Event::Event(int event_id, string team1, string team2, SportType sport, double odds_team1, double odds_team2, double odds_draw, bool draw_possible):
event_id(event_id),team1(team1),team2(team2),sport(sport),odds_team1(odds_team1),odds_team2(odds_team2),odds_draw(odds_draw),draw_possible(draw_possible),points_team1(0),points_team2(0),status(false),result(-1){}

int Event::get_event_id() const{
    return event_id;
}
string Event::get_team1() const{
    return team1;
}
string Event::get_team2() const{
    return team2;
}
SportType Event::get_sport()const{
    return sport;
}
double Event::get_odds_team1() const{
    return odds_team1;
}
double Event::get_odds_team2() const{
    return odds_team2;
}
double Event::get_odds_draw() const{
    return odds_draw;
}
bool Event::is_draw_possible() const{
    return draw_possible;
}
bool Event::get_status() const{
    return status;
}
int Event::get_result() const{
    return result;
}
int Event::get_points_team1()const{
    return points_team1;
}
int Event::get_points_team2()const{
    return points_team2;
}

void Event::set_result(int p1, int p2){
   points_team1= p1;
   points_team2= p2;
   status = true;

   if (p1==p2 && !draw_possible){
    throw logic_error("Draw is not allowed for this event type. ");
   }

   if(p1>p2){
    result =1;
   }
   else if(p2>p1){
    result=2;
   }
   else 
    if(draw_possible){
     result=0;
    }
    
}

void Event::display_event() const{
    cout << "Event ID: " << event_id <<endl;

    switch(sport){
        case SportType::Football:
            cout <<"Foootball "<< endl;break;
        case SportType::Basketball:
            cout <<"Basketball "<< endl;break;
        case SportType::Nfl:
            cout <<"NFL "<< endl;break;
    }

    cout << team1 << " vs " << team2 << endl;
    cout << "Odds: " <<endl;
    cout << team1 << ": " << odds_team1<<endl;
    cout << team2 << ": " << odds_team2<<endl;
    if(draw_possible){
        cout << "Draw: " << odds_draw << endl;
    }

    if(status){
        cout <<"Final result: "<<team1<<" "<<points_team1<<" : "<<points_team2<<" "<<team2<<endl;    
    
    if(result==1){
        cout <<team1<< " won"<<endl;
    }
    else if(result==0){
        cout<<"Match endend with a draw"<<endl;
    }
    else if(result==2){
        cout<<team2<<" won"<<endl;
    }
}

}