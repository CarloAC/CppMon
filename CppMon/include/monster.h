#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include "randFz.h"
#include "attacchi.h"
#include "Logger.h"
using namespace std;

class monster: public Logger
{
public:
//INITIALIZERS
    monster(const string & line, ofstream * o= NULL);
    virtual ~monster();
    void insert_attack(const attacchi & Att);

//ELABORATE
    int calculate_partialDamage(int PDB_attack);

//MODDERS
    void reduce_HP(int partialDamage);
    bool modify_stat(char stat,int value);
    void reset_Stats();

//GETTERS monster
    bool get_is_dead() const;   //true if is dead
    int get_id() const;
    string get_race() const;
    int get_hp() const;
    int get_ap() const;
    int get_dp() const;
    int get_sp() const;
    int get_ap_default() const;
    int get_dp_default() const;
    int get_sp_default() const;

//GETTERS attack
    attacchi get_attack(int i);
    string get_attack_name(int i);

protected:
private:

    vector <attacchi> _attacks;
    int _ID;
    string _specie;
    int _HP;
    int _AP;
    int _DP;
    int _SP;
    int _AP_default;  //val default iniziali
    int _DP_default;
    int _SP_default;
};

#endif // MONSTER_H
