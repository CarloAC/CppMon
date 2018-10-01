/*
    Alla realizzazione di un oggetto 'match'
viene init il 'Logger' (classe padre di 'match') -- "CppMon"
viene init 'player' NPC -- _PC
viene init 'player' human -- _user




*/

#ifndef MATCH_H
#define MATCH_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include "randFz.h"
#include "attacchi.h"
#include "monster.h"
#include "player.h"
#include "Logger.h"

using namespace std;

//EXTERNAL INITIALIZERS
string get_date_time();
string get_NPC_player_name(string fname);
string get_user_player_name(string fname);


class match: public Logger
{
public:
//INITIALIZERS
    match(string attacks_file_name, string monsters_file_name, string players_file_name, ofstream * o= NULL);
    virtual ~match();
//PLAY
    void fight();
    void end_match();
    bool speed(monster *MonPC,monster *MonUser);

protected:
private:
//CREATE & READ FILES
    int search_monster_inVector(int monster_ID);
    int search_attack_inVector(int attack_ID);
    void read_create_attacks(string fname);
    void read_create_monsters(string fname);
    void read_create_player(string fname);
    void create_NPC();
//PLAY
    bool menu(monster *Mon);
    void change();
    void user_attack(monster *Mon);
    void PC_attack(monster *Mon);
//CONTROL
    int limit_statistic_value(monster mon, bool upper, char statistic);
    int monster_stat_value(monster mon, char statistica);
    string define_influence(int inf);
    string define_stat(char statistica);
//VARIABLE
    vector<attacchi> _attacks;
    vector<monster> _monsters;
    player _PC;
    player _user;
    int _PC_monster_on_field;
    int _user_monster_on_field;
    attacchi _PC_attack;
    attacchi _user_attack;
};

#endif // MATCH_H
