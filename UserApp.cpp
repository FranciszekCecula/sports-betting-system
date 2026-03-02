#include <iostream>
#include <limits>
#include <string>
#include "UserApp.hpp"

using namespace std;

UserApp::UserApp(Menager& menagerRef, EventMenager& eventMenagerRef, BetMenager& betMenagerRef):
menager(menagerRef),eventMenager(eventMenagerRef),betMenager(betMenagerRef){}

void UserApp:: run(shared_ptr<User> &user){
    if(!user){
        cout<<"Error: Invalid user. \n";
        return;
    }
    
    bool running = true;
    
    while (running){
        cout<<"\n === HAWKS BOOKIE ===\n";
        cout<<"1) Show balance \n";
        cout<<"2) Deposit money \n";
        cout<<"3) Withdraw money \n";
        cout<<"4) Show events \n";
        cout<<"5) Place a bet \n";
        cout<<"6) My bets \n";
        cout<<"7) Bets history \n";
        cout<<"8) Change password \n";
        cout<<"9) Logout \n";
        cout<<"Choose option: ";

        int choice;
        cin>>choice;
        if (!choice){
            cin.clear();
            cin.ignore(100000, '\n');
            cout <<"Invalid input. Please enter valid number."<<endl;
        }
        
        switch (choice){
            case 1:
            show_balance(user);
            break;

            case 2:
            deposit(user);
            break;

            case 3:
            paycheck(user);
            break;

            case 4:
            list_events();
            break;

            case 5:
            place_bet(user);
            break;

            case 6:
            list_active_bets (user);
            break;

            case 7:
            list_bets_history(user);
            break;

            case 8:
            change_password(user);
            break;

            case 9:
            running = false;
            break;

            default: cout<<"Error: Invalid input option.\n";
        } 
    }
}

void UserApp::show_balance(shared_ptr<User>&user)const{
    cout<<"Current balance: "<<user->get_balance()<<" $\n";
}

void UserApp::deposit(shared_ptr<User>&user){
    double amount;
    cout<<"Enter amount you want to deposit (-1 = back to the menu): "<<endl;
    cin>> amount;

    if(cin.fail()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Invalid input. Please enter valid number."<<endl;
        return;   
    }
    if(amount == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    user->deposit(amount);
    menager.save_to_file();
}

void UserApp::paycheck(shared_ptr<User>&user){
    double amount;
    cout<<"Enter withdrawal amount (-1 = back to the menu): "<<endl;
    cin>> amount;

    if(cin.fail()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Invalid input. Please enter valid number."<<endl;
        return;   
    }
    if(amount == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    user->paycheck(amount);
    menager.save_to_file();
}

void UserApp:: change_password(shared_ptr<User>&user){
    string old_password;
    string new_password;

    cout<<"Enter old password (-1 = back to the menu): ";
    cin>> old_password;
    if(old_password == "-1"){
        cout<<"Returning to the interface...\n"; 
        return;
    }
    cout<<"Enter new password (-1 = back to the menu): ";
    cin>> new_password;
    if(new_password == "-1"){
        cout<<"Returning to the interface...\n"; 
        return;
    }

    if(user->change_password(old_password,new_password)){
        menager.save_to_file();
    }
    else{
        cout<<"Error during password change! Try again. \n";

    }

}

void UserApp::list_events()const{
    cout<<"\n === EVENTS LIST ===\n";
    eventMenager.list_events();
}

void UserApp::place_bet(shared_ptr<User> user){
    cout <<"\n === PLACE A BET ===\n";
    eventMenager.list_active_events();

    cout<<"Enter ID of event you want to bet on:  ";
    int event_id;
    cin>>event_id;

    if(cin.fail()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Error: Please enter valid number."<<endl;
        return;   
    }
    if(event_id == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }

    shared_ptr<Event> event = eventMenager.find_by_id(event_id);
    if(!event){
        cout<<" Error: Event not found. Enter valid input \n";
        return;
    }

    if(event->get_status()){
        cout << "Error: This event is alread finished. Cannot place bet on finished events" <<endl;
        return;
    }

    cout <<"\nPick a result \n";
    cout <<"1) "<< event->get_team1() <<" "<< event->get_odds_team1() <<endl;
    cout <<"2) "<< event->get_team2() <<" "<< event->get_odds_team2() <<endl;
    if(event->is_draw_possible()){
        cout <<"3) Draw"<<" "<<event->get_odds_draw() <<endl;
    }

    int choice;
    cout<<"Enter your result: ";
    cin>>choice;
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Error: Please enter valid number."<<endl;
        return;   
    }

    if(choice == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }

    int bet_result=-1;
    if(choice==1){
        bet_result=1;
    }
    else if(choice==2){
        bet_result=2;
    }
    else if(choice==3 && event->is_draw_possible()){
        bet_result=0;
    }
    else{
        cout<<"Error: Enter valid option \n";
        return;
    }
    cout<<"Enter the amount to bet:  ";
    double amount;
    cin>>amount;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Invalid input. Please enter valid number."<<endl;
        return;   
    }

    if(amount == -1){
        cout<<"Returning to the interface...\n"; 
        return;
    }

    if(amount <= 0||amount > user->get_balance()){
        cin.clear();
        cin.ignore(100000, '\n');
        cout <<"Invalid input. Please enter valid number."<<endl;
        return;   
    }
    user->withdraw(amount);
    menager.save_to_file();

    auto new_bet = betMenager.create_bet(event,user->get_username(),amount,bet_result);
    if (!new_bet){
        user->deposit(amount);
        menager.save_to_file();
        cout <<"Bet was NOT placed succesfully "<<endl;
        return;
    }
    int bet_id = new_bet->get_bet_id();

    cout<<"Bet placed successfully! Bet ID = "<< bet_id <<endl;

    betMenager.save_to_file();
}

void UserApp::list_bets_history(shared_ptr<User>&user){
    betMenager.history_bet_for_user(user->get_username());
}

void UserApp::list_active_bets(shared_ptr<User>&user){
    betMenager.list_active_bets_for_user(user->get_username());
}