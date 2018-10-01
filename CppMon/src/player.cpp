#include "player.h"

//INITIALIZERS
player::player(const string & line, ofstream * o):
    Logger(line,o)
{
    _player_name = "PC";
    if (!line.empty())
    {
        _player_name = line;
    }
}
player::~player()
{
    //dtor
}
void player::set_player_name(string Pname)
{
    _player_name = Pname;
}
void player::add_monster(const monster & M)
{
    _team.push_back(M);
}

//ELABORATE
void player::delete_monster(int position)
{
    _team.erase(_team.begin()+position);
}

//GETTERS player
string player::get_username()
{
    return _player_name;
}

void player::start_msg()
{
    stringstream ss;
    ss.str("");
    ss <<_team[0].get_race();
    for (unsigned int i=1; i<(_team.size()); ++i)
    {
        string tmp = ss.str();
        ss.str("");
        ss << tmp << " " << _team[i].get_race();
    }
    msg("Mostri",ss.str());
    msg("Manda in campo",get_name_monster_team(0));
    fmsg("Mostri",ss.str());
    fmsg("Manda in campo",get_name_monster_team(0));
}

//GETTERS monster
bool player::void_team()
{
    return (_team.empty());
}

monster * player::get_monster(int i)
{
    return & _team[i];
}
int player::get_num_monster_team()
{
    return _team.size();
}
string player::get_name_monster_team(int i)
{
    return _team[i].get_race();
}
