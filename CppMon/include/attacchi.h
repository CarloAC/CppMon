#ifndef ATTACCHI_H
#define ATTACCHI_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class attacchi
{
public:
    attacchi(const string & line);
    attacchi();
    virtual ~attacchi();

//GETTERS
    int get_ID() const;
    string get_Name() const;
    int get_PDB() const;
    bool get_target() const;
    char get_statistic() const;
    int get_influence() const;
    bool get_priority() const;
    int get_attack_type() const;


protected:
private:

    int _ID;
    string _NAME;
    int _PDB;
    bool _target;       //true attacker or false defender
    char _statistic;    //A, D or V
    int _influence;     //-2, -1, +1, +2
    bool _priority;     // if p then true
    int _Attack_type;   //1: norm or p attack; 2: mod stat; 3: norm or p attack plus mod stat; 0: error
};

#endif // ATTACCHI_H


