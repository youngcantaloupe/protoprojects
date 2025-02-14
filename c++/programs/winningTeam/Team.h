#ifndef TEAMH
#define TEAMH

#include <string>

using namespace std;

class Team {
   // TODO: Declare private data members - name, wins, losses
private:
    string name;
    int wins;
    int losses;

public:
    void SetName(string name);
    void SetWins(int wins);
    void SetLosses(int losses);
        
    string GetName() const;
    int GetWins() const;
    int GetLosses() const;
   
    double GetWinPercentage();
    void PrintStanding();
};

#endif
