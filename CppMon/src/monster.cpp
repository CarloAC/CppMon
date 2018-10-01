#include "monster.h"

string get_second_word(string line)
{
    stringstream ss(line);
    string w, s;
    ss >> w >> s;
    return s;
}

//INITIALIZERS
monster::monster(const string & line, ofstream * o): Logger(get_second_word(line),o)
{
    stringstream ss(line);
    ss >> _ID >> _specie >> _HP >> _AP_default >> _DP_default >> _SP_default;

    _AP = _AP_default;
    _DP = _DP_default;
    _SP = _SP_default;
}

monster::~monster()
{
}
void monster::insert_attack(const attacchi & Att)
{
    _attacks.push_back(Att);
}

//ELABORATE
int monster::calculate_partialDamage(int PDB_attack)
{
    return (_AP*PDB_attack*randFz::AttackRandom());
}


//MODDERS
void monster::reduce_HP(int partialDamage)
{
    _HP = _HP - (partialDamage/_DP);
}
bool monster::modify_stat(char stat, int value)
{
    if (stat == 'A')
    {
        _AP = _AP * exp2(value);
        if (_AP < (_AP_default/8))
        {
            _AP = _AP_default/8;
            return true;
        }
        if (_AP > (_AP_default*8))
        {
            _AP = _AP_default*8;
            return true;
        }
    }
    if (stat == 'D')
    {
        _DP = _DP * exp2(value);
        if (_DP < (_DP_default/8))
        {
            _DP = _DP_default/8;
            return true;
        }
        if (_DP > (_DP_default*8))
        {
            _DP = _DP_default*8;
            return true;
        }
    }
    if (stat == 'V')
    {
        _SP = _SP * exp2(value);
        if (_SP < (_SP_default/8))
        {
            _SP = _SP_default/8;
            return true;
        }
        if (_SP > (_SP_default*8))
        {
            _SP = _SP_default*8;
            return true;
        }
    }
    return false;
}
void monster::reset_Stats()
{
    _AP = _AP_default;
    _DP = _DP_default;
    _SP = _SP_default;
}


//GETTERS monsters
bool monster::get_is_dead() const
{
    if (_HP <= 0)
    {
        return true;//is dead
    }
    else
    {
        return false;//is alive
    }
}

int monster::get_id() const
{
    return _ID;
}
string monster::get_race() const
{
    return _specie;
}
int monster::get_hp() const
{
    return _HP;
}
int monster::get_ap() const
{
    return _AP;
}
int monster::get_dp() const
{
    return _DP;
}
int monster::get_sp() const
{
    return _SP;
}
int monster::get_ap_default() const
{
    return _AP_default;
}
int monster::get_dp_default() const
{
    return _DP_default;
}
int monster::get_sp_default() const
{
    return _SP_default;
}

//GETTERS attack
attacchi monster::get_attack(int i)
{
    return _attacks[i];
}
string monster::get_attack_name(int i)
{
    return _attacks[i].get_Name();
}

