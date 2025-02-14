#include <iostream>
#include <iomanip> 
#include "Team.h"
using namespace std;

void Team::SetName(string name) {
this->name = name;
    
}

void Team::SetWins(int wins) {
this->wins = wins;
}

void Team::SetLosses(int losses) {
this->losses = losses;
}

string Team::GetName() const {
    return name;
}

int Team::GetWins() const {
    return wins;
}

int Team::GetLosses() const {
    return losses;
}
   
double Team::GetWinPercentage() {
    double percent = ((double)wins) / (wins + losses);
    return percent;
}

void Team::PrintStanding() {
    double percent = GetWinPercentage();
    cout << fixed << setprecision(2);
    cout << "Win percentage: "  << percent << endl;

    if (percent >= 0.5) {
        cout << "Congratulations, Team Ravens has a winning average!" << endl;
    } else {
        cout << "Team Angels has a losing average." << endl;
    }
}
