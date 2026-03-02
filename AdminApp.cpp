#include <iostream>
#include <limits>

#include "AdminApp.hpp"

using namespace std;

AdminApp::AdminApp(Menager &menagerRef, EventMenager &eventMenagerRef,BetMenager &betMenager):
menager(menagerRef),eventMenager(eventMenagerRef),betMenager(betMenager){}

void AdminApp::run(const shared_ptr<User> &admin_user){
    if(!admin_user){
        cout<< "Error: no admin user provided"<<endl;
        return;
    }

    if(!admin_user->get_admin()){
        cout <<"Error: Acces denied"<<endl;
        return;
    }

    bool running =true;
    while(running){
        cout<<"\n=== ADMIN PANEL ===\n";
        cout<<"1) List users\n";
        cout<<"2) Delete user\n";
        cout<<"3) List events\n";
        cout<<"4) Create event\n";
        cout<<"5) Delete event\n";
        cout<<"6) Set event results\n";
        cout<<"7) Save events to file\n";
        cout<<"8) Load events from file\n";
        cout<<"9) Exit admin panel \n";
        cout<<"Choose option: ";

        int choice;
        cin>> choice;
        if (cin.fail()){
             cin.clear();
            cin.ignore(100000, '\n');
            cout <<" Invalid input. Please enter valid number."<<endl;
            return;
        }
        switch (choice){
            case 1:
            list_users();
            break;

            case 2:
            delete_users();
            break;

            case 3:
            list_events();
            break;

            case 4:
            create_event();
            break;

            case 5:
            delete_event();
            break;

            case 6:
            set_result();
            break;
            
            case 7:
            save_event();
            break;

            case 8:
            load_event();
            break;

            case 9:
            running = false;
            break;

            default: cout <<"Error: Invalid option"<<endl;
        }
    }

}

void AdminApp::list_users() const{
    cout<<"\n=== USERS ===\n";
    menager.list_users();
}

void AdminApp::delete_users(){
    string delete_username;
    cout << "Enter user to delete (-1 = back to the menu): ";
    cin >> delete_username;

    if(delete_username == "-1"){
        cout<<"Returning to the interface...\n"; 
        return;
    }

    string confirm;
    cout << "Are you sure you want to delete user: "<< delete_username <<"? (yes/no): ";
    cin >> confirm;

    if (confirm =="yes"){
        menager.delete_user(delete_username);                    
    }
    else{
        cout << "User deletion cancelled.\n";
    }
}

void AdminApp::list_events() const{
    cout<<"\n=== EVENTS ===\n";
    eventMenager.list_events();
}

void AdminApp::create_event(){
    string team1;
    string team2;
    double odds1=0.0;
    double odds2=0.0;
    double oddsd=0.0;
    int sport_type;
    int draw_possible_int=0;

    cout<<"\n=== EVENT CREATOR ===\n";
    cout<<"Team 1: "<<endl;
    cin>> ws;
    getline(cin,team1);
    cout<<"Team 2: "<<endl;
    getline (cin,team2);

    cout <<"Sport: 0=Football, 1=Basketball, 2=Nfl, (-1 = back to the menu): ";
    cin>> sport_type;
    if(cin.fail()){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    if(sport_type == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    cout <<"Odds team1: ";
    cin>>odds1;
    if(!(odds1)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    cout <<"Odds team2: ";
    cin>>odds2;
    if(!(odds2)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    cout<<"Is draw possible (yes=1, 0=no): ";
    cin>>draw_possible_int;
    if(cin.fail()){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    cout<<"Odds draw: ";
    cin>>oddsd;
    if(!(oddsd)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    SportType sport = static_cast<SportType>(sport_type);
    bool draw_possible= (draw_possible_int !=0);

    eventMenager.add_event(team1,team2,sport,odds1,odds2,oddsd,draw_possible_int);
    eventMenager.save_to_file();
    //cout<<"Event created successfully "<<endl;
}

void AdminApp::set_result(){
    int id;
    int points1;
    int points2;
    
    cout<<"\n=== SETTING RESULT ===\n";
    cout<<"Enter event ID (-1 = back to the menu): ";
    cin>>id;
    if(!(id)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    if (id==-1){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    cout<<"Points for team1: ";
    cin>>points1;
    if(cin.fail()){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    cout<<"Points for team2: ";
    cin>>points2;

    if(cin.fail()){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');cout<<"Error: Invalid input \n";return;}

    if(eventMenager.set_event_result(id,points1,points2)){
        shared_ptr<Event>event = eventMenager.find_by_id(id);
        //cout<<"Result correctly set\n";
        betMenager.bets_results_for_event(event, menager);
        eventMenager.save_to_file();
        betMenager.load_from_file();
    }
    else{
        cout<<"Error: Failed to set this result for this event! "<<endl;   
    }
}

void AdminApp::save_event()const{
    if(eventMenager.save_to_file()){
        cout<<"Events saved to file successfully \n "; 
    }
    else{
        cout<<"Error: Failed to save events "<<endl;
    }
}

void AdminApp::load_event(){
     if(eventMenager.load_from_file()){
        cout<<"Events loaded from file successfully \n "; 
    }
    else{
        cout<<"Error: Failed to load events "<<endl;
    }

}

void AdminApp::delete_event(){
    int id;
    cout<<"\n === DELETE EVENT ===\n";
    cout<<"Enter event ID to delete (-1 - back to the menu): ";
    cin>>id;
    if(!(id)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Error: Invalid input\n";
    return;
    }
    if(id == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    shared_ptr<Event> event = eventMenager.find_by_id(id);

    if(!event){
        cout<<"Error: Event with ID: "<<id<<" not found\n";
        return;
    }

    cout << "Event to be deleted: "<<event->get_team1()<< "vs"<< event->get_team2()<<"\n";
    cout <<"Sport: ";
    switch (event->get_sport()){
        case SportType::Football: cout<< "Football"; break;
        case SportType::Basketball: cout<< "Basketball"; break;
        case SportType::Nfl: cout<<"Nfl"; break;
    }
    cout<<"Status: "<< (event->get_status() ? "Finished" :"Pending") << "\n";
    cout<<"Score: "<< event->get_points_team1()<< " : " <<event->get_points_team2()<<"\n";

    cout<<"Warning: Deleting event may affect bets!"<<endl;
    cout<<"Are you sure you want to delete this event? (yes/no): ";
    string confirm;
    cin>>confirm;
    if(confirm != "yes" && confirm != "YES" ){
        cout<<"Deletion canceled. \n";
        return;
    }
    bool deletion = eventMenager.delete_event(id);
    if (deletion){
         eventMenager.save_to_file();
}
else{
    cout<<"Error: Failed to delete the event.\n";
}
    }