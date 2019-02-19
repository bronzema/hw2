#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, const string* team2, int len)
{
    cout << "\nCombination " << combo++ << endl;
    cout << "T1: ";
    for(int i=0; i < len; i++){
        cout << team1[i] << " ";
    }
    cout << endl;
    cout << "T2: ";
    for(int i=0; i < len; i++){
        cout << team2[i] << " ";
    }
    cout << endl;
}

void createcombo(string* team1, string* team2, int teamindex, string* players, 
        int totalplayers, int index1, int index2)
{
    //teamindex: keeps track of what player we're adding to the teams
    //index1: keeps track of how many players on team 1
    //index2: keeps track of how many players on team 2

    if(index1 == totalplayers / 2 && index2 == totalplayers / 2)
    //if team 1 and team 2 are full
    {
        printSolution(team1, team2, totalplayers / 2);
        return;
    }

    if(index1 < totalplayers / 2) //if team 1 is not full yet
    {
        team1[index1] = players[teamindex];
        createcombo(team1, team2, teamindex + 1, players, totalplayers,
            index1 + 1, index2);
        //recurse and increase teamindex and index1
    }

    if(index2 < totalplayers / 2) //if team2 is not full yet
    {
        team2[index2] = players[teamindex];
        createcombo(team1, team2, teamindex + 1, players, totalplayers, 
            index1, index2 + 1);
        //recurse and increase teamindex and index2
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        cerr << "Please provide a file of names" << endl;
        return 1;
    }

    ifstream ifile(argv[1]); //stream infile

    if(ifile.fail()) //check if filestream failed
    {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int num;
    ifile >> num;

    string* players = new string[num]; //dynamically allocate array for player names

    for(int i = 0; i < num; i++) //read in player names
    {
        ifile >> players[i];
    }

    string* team1 = new string[num/2]; //dynamically allocate array for team1

    string* team2 = new string[num/2]; //dynamically allocate array for team2

    createcombo(team1, team2, 0, players, num, 0, 0);

    delete [] players;
    delete [] team1;
    delete [] team2;

  return 0;
}
