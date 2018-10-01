#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "monster.h"
#include "Logger.h"
using namespace std;

class player: public Logger
{
public:
//INITIALIZERS
    player(const string & line, ofstream * o= NULL);
    virtual ~player();
    void set_player_name(string Pname = "DefaultNamePlayer");
    void add_monster(const monster & M);

//ELABORATE
    void delete_monster(int position);
//GETTERS player
    string get_username();
    void start_msg();
//GETTERS monster
    bool void_team();   //true if is empty
    monster * get_monster(int i = 0);
    int get_num_monster_team();
    string get_name_monster_team(int i);
protected:
private:
    string _player_name;
    vector <monster> _team;
};

#endif // PLAYER_H
