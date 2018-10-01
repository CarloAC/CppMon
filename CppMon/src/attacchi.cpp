#include "attacchi.h"


int influenceConverter(bool sign, int duty)//converte -- in -2, ++ in +2, ecc
{
    int result = 0;
    if (sign == true)
    {
        result = 1*duty;
    }
    else
    {
        result = (-1)*duty;
    }
    return result;
}

int CountWords(string myString, int *inf) //conta il numero di "parole" che occore per distinguere il ctor di attacks
{
    int numspaces = 0;
    int tmp = 0;
    bool symbType;
    int symbNumb = 0;
    // checks each character in the string
    for (int i=0; i<int(myString.length()); i++)
    {
        if ((isspace(myString[i]))||(ispunct(myString[i])))
        {
            if(ispunct(myString[i]))
            {
                tmp ++;
                if (tmp >= 2)
                {
                    symbNumb++;             //count # of ++ or --
                    if (myString[i]=='+')
                    {
                        symbType = true;    //++
                    }
                    else
                    {
                        symbType = false;   //--
                    }
                    if (tmp == 3) numspaces--;
                }
            }
            numspaces++;
        }
    }
    *inf = influenceConverter(symbType, symbNumb);
    return (numspaces+1);
}

bool priority_ctrl(char p)
{
    if (p=='p')
    {
        return  true;
    }
    else
    {
        return  false;
    }
}



attacchi::attacchi(const string & line)
{
    _Attack_type = 0;
    _PDB = 0;
    stringstream ss(line);
    int influence = 0;
    int Nwords = CountWords(line,&influence);

    if ((Nwords == 3)||(Nwords == 4))   //normal attack or priority attack
    {
        _Attack_type = 1;
        char priorita;
        ss >> _ID >> _NAME >> _PDB >> priorita;
        _priority = priority_ctrl(priorita);
    }

    if (Nwords == 5)                    //statistic modder
    {
        string info;
        _Attack_type = 2;
        _influence = influence;
        ss >> _ID >> _NAME >> info;
        if (info[0]=='a')//is "attaccante"
        {
            _target = true;
            _statistic = info[12];//char after P
        }
        else //info[0]=='d'     //is "difensore"
        {
            _target = false;
            _statistic = info[11];//char after P
        }
        _priority = false;
    }

    if ((Nwords == 6)||(Nwords == 7))   //normal attack or priority attack with statistic modder
    {
        char priorita;
        _Attack_type = 3;
        string info;
        _influence = influence;
        ss >> _ID >> _NAME >> _PDB >> info >> priorita;
        if (info[0]=='a')//is "attaccante"
        {
            _target = true;
            _statistic = info[12];//char after P
        }
        else //info[0]=='d'  //is "difensore"
        {
            _target = false;
            _statistic = info[11];//char after P
        }
        _priority = priority_ctrl(priorita);
    }
}

attacchi::attacchi()
{
}

attacchi::~attacchi()
{
}


//GETTERS

int attacchi::get_ID() const
{
    return _ID;
}
string attacchi::get_Name() const
{
    return _NAME;
}
int attacchi::get_PDB() const
{
    return _PDB;
}
bool attacchi::get_target() const
{
    return _target;
}
char attacchi::get_statistic() const
{
    return _statistic;
}
int attacchi::get_influence() const
{
    return _influence;
}
bool attacchi::get_priority() const
{
    return _priority;
}
int attacchi::get_attack_type() const
{
    return _Attack_type;
}
