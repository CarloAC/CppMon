#include "match.h"

//EXTERNAL INITIALIZERS
string get_user_player_name(string fname)
{
    ifstream file;
    string line;
    file.open(fname.c_str());
    if (!file.is_open())
    {
        cout << "Error Reading File:\t" << fname << endl;
        exit (EXIT_FAILURE);
    }
    getline(file, line);    //leggi la prima riga del file --> nome del giocatore
    return line;
}

string get_NPC_player_name(string fname)
{
    ifstream file;
    string line;
    file.open(fname.c_str());
    if (!file.is_open())
    {
        cout << "Error Reading File:\t" << fname << endl;
        exit (EXIT_FAILURE);
    }
    getline(file, line);        //read first name
    do
    {
        getline(file, line);    //macina linee
    }
    while(isdigit(line[0])&&!(file.eof())); //fintanto che legge numeri
    if (file.eof()) //se, quando smette di leggere numeri ha raggiunto eof
    {
        return "PC";    //usa nome Default
    }
    return line;
}

string get_date_time()
{
    stringstream ss;
    struct tm* t;
    time_t long_time;
    time( &long_time );
    t = localtime( &long_time );
    time_t h = time(NULL);      // return sys time
    tm *tempo;
    tempo = localtime(&h);
    ss << "Data: " <<t->tm_mday<<"/"<<t->tm_mon+1<<"/"<<t->tm_year+1900<<" - Ore: "<<tempo->tm_hour<<":"<<tempo->tm_min;
    return ss.str();
}

//CREATE & READ FILES
int match::search_monster_inVector(int monster_ID)
{
    int unsigned i = 0;
    while ((_monsters[i].get_id() != monster_ID)&&(i<=_monsters.size()))
    {
        ++i;
    }
    if (i>_monsters.size())
    {
        msg("EPIC ERROR","Mostro non presente nella lista fornita!!!");
        exit (EXIT_FAILURE);
    }
    return i;
}
int match::search_attack_inVector(int attack_ID)
{
    int unsigned i = 0;
    while ((_attacks[i].get_ID() != attack_ID)&&(i<=_attacks.size()))
    {
        ++i;
    }
    if (i>_attacks.size())
    {
        msg("EPIC ERROR","Mostro con attacco non presente nella lista fornita!!!");
        exit (EXIT_FAILURE);
    }
    return i;
}
void match::read_create_attacks(string fname)
{
    ifstream file;
    file.open(fname.c_str());
    if (!file.is_open())
    {
        msg("Error Reading File:\t",fname);
        exit (EXIT_FAILURE);
    }
    while (!file.eof())
    {
        string line;
        getline(file, line);
        if (line.size() > 0)
        {
            attacchi  a(line);
            _attacks.push_back(a);
        }
    }
}
void match::read_create_monsters(string fname)
{
    ifstream file;
    file.open(fname.c_str());
    if (!file.is_open())
    {
        msg("Error Reading File:\t",fname);
        exit (EXIT_FAILURE);
    }
    while (!file.eof())
    {
        string line;
        getline(file, line);
        if (line.size() > 0)
        {
            monster m(line, Logger::get_file());
            _monsters.push_back(m);
        }
    }
}
void match::read_create_player(string fname)
{
    ifstream file;
    string line;
    file.open(fname.c_str());
    if (!file.is_open())
    {
        msg("Error Reading File:\t",fname);
        exit (EXIT_FAILURE);
    }
    getline(file, line);
    int counter = 1;
    getline(file, line);
    while((isdigit(line[0]))&&(counter<5)&&!(file.eof()))
    {
        if (counter!=1)
        {
            getline(file, line);
        }
        if (isdigit(line[0]))
        {
            int M, A1, A2, A3, A4;
            stringstream ss(line);
            ss >> M >> A1 >> A2 >> A3 >> A4;
            int monster_position = search_monster_inVector(M);
            int attack_1_position = search_attack_inVector(A1);
            int attack_2_position = search_attack_inVector(A2);
            int attack_3_position = search_attack_inVector(A3);
            int attack_4_position = search_attack_inVector(A4);
            monster tmp = _monsters[monster_position];
            tmp.insert_attack(_attacks[attack_1_position]);
            tmp.insert_attack(_attacks[attack_2_position]);
            tmp.insert_attack(_attacks[attack_3_position]);
            tmp.insert_attack(_attacks[attack_4_position]);
            _user.add_monster(tmp);
            ++counter;
        }
    }
    if (file.eof())    //if file is ended and no NPC is created
    {
        msg("Nessuna info sulla squadra NPC","creazione automatica\n");
        fmsg("Nessuna info sulla squadra NPC","creazione automatica");
        create_NPC();   //create randomly NPC
        return;
    }
    else
    {
        counter = 1;
        while(isdigit(line[0]))
        {
            getline(file, line);
            if (file.eof())    //if file is ended and no NPC is created
            {
                msg("Nessuna info sulla squadra NPC","creazione automatica\n");
                fmsg("Nessuna info sulla squadra NPC","creazione automatica");
                create_NPC();   //create randomly NPC
                return;
            }
        }
        do
        {
            getline(file, line);
            int M, A1, A2, A3, A4;
            stringstream ss(line);
            ss >> M >> A1 >> A2 >> A3 >> A4;
            int monster_position = search_monster_inVector(M);
            int attack_1_position = search_attack_inVector(A1);
            int attack_2_position = search_attack_inVector(A2);
            int attack_3_position = search_attack_inVector(A3);
            int attack_4_position = search_attack_inVector(A4);
            monster tmp = _monsters[monster_position];
            tmp.insert_attack(_attacks[attack_1_position]);
            tmp.insert_attack(_attacks[attack_2_position]);
            tmp.insert_attack(_attacks[attack_3_position]);
            tmp.insert_attack(_attacks[attack_4_position]);
            _PC.add_monster(tmp);
            ++counter;
        }
        while((isdigit(line[0]))&&(counter<5)&&(!(file.eof())));
    }
}

void match::create_NPC()
{
    int N_monsters = (randFz::NRandom(4))+1;
    for (int i=0; i< N_monsters; i++)   //create monsters for NPC
    {
        int index_monster = randFz::NRandom(_monsters.size());  //random index to choose a monster
        monster tmp(_monsters[index_monster]);   //create temporary monster copy

        int rand_attack = randFz::NRandom(_attacks.size());//random choice of attack
        int counter = 0;
        int tmp_rand_attack = 0;
        while (counter < 4)//insert in monster 4 different attacks
        {
            if (rand_attack != tmp_rand_attack)//control to have different attack
            {
                tmp.insert_attack(_attacks[rand_attack]);//give to tmp.monster a random attack
                rand_attack = tmp_rand_attack;
                tmp_rand_attack = randFz::NRandom(_attacks.size());
                ++counter;
            }
            else
            {
                tmp_rand_attack = randFz::NRandom(_attacks.size());
            }
        }
        _PC.add_monster(tmp);
    }
}


//INITIALIZERS
match::match(string attacks_file_name, string monsters_file_name, string players_file_name, ofstream * o):
    Logger("CppMon", o),
    _PC(get_NPC_player_name(players_file_name),o),
    _user(get_user_player_name(players_file_name),o)
{
    fmsg(get_date_time());
    fmsg("Comincia la partita ",_user.get_username(), " vs ", _PC.get_username());
    read_create_attacks(attacks_file_name);
    read_create_monsters(monsters_file_name);
    read_create_player(players_file_name);
    _PC_monster_on_field = 0;
    _user_monster_on_field = 0;
    _user.start_msg();
    cout << "\t\t---" << endl;
    _PC.start_msg();
    _attacks.clear();                   //delete list of attacks
    _monsters.clear();                  //delete list of monsters
}
match::~match()
{
}

//CONTROL
int match::monster_stat_value(monster mon, char statistica)
{
    int tmp;
    if (statistica == 'A')
    {
        tmp = mon.get_ap();
    }
    if (statistica == 'D')
    {
        tmp = mon.get_dp();
    }
    if (statistica == 'V')
    {
        tmp = mon.get_sp();
    }
    return tmp;
}

int match::limit_statistic_value(monster mon, bool upper, char statistic)
{
    int x = 0;
    if (upper)
    {
        if(statistic=='A')
            x = ((mon.get_ap())*8);
        if(statistic=='D')
            x = ((mon.get_dp())*8);
        if(statistic=='V')
            x = ((mon.get_sp())*8);
    }
    else
    {
        if(statistic=='A')
            x = ((mon.get_ap())/8);
        if(statistic=='D')
            x = ((mon.get_dp())/8);
        if(statistic=='V')
            x = ((mon.get_sp())/8);
    }
    return x;
}

string match::define_influence(int inf)
{
    string tmp;
    if (inf == -2)
    {
        tmp = "Diminuisce di molto";
    }
    if (inf == -1)
    {
        tmp = "Diminuisce";
    }
    if (inf == +1)
    {
        tmp = "Aumenta";
    }
    if (inf == +2)
    {
        tmp = "Aumenta di molto";
    }
    return tmp;
}

string match::define_stat(char statistica)
{
    string tmp;
    if (statistica == 'A')
    {
        tmp = "PA";
    }
    if (statistica == 'D')
    {
        tmp = "PD";
    }
    if (statistica == 'V')
    {
        tmp = "PV";
    }
    return tmp;
}

//PLAY
bool match::menu(monster *Mon)//return: true->change ; false->attack
{
    cout << endl;
    _user.msg("Premi 0 per attaccare, 1 per cambiare mostro.");
    int choice;
    std::cin.ignore(0,'\n');
    while (!(cin >> choice)||((choice!=0)&&(choice!=1)))
    {
        msg("Inserire 0 o 1, non altri numeri!");
        std::cin.clear();
        std::cin.ignore(1,'\n');
    }
    if ((choice == 1)&&(_user.get_num_monster_team()>1))
    {
        _user.msg("Scegliere il mostro:");
        change();
        return true;
    }
    else //(choice == 0)  ||  (#monster in team < = 1)
    {
        if ((choice == 1)&&(_user.get_num_monster_team()<2))
        {
            _user.msg("Non hai altri mostri, attacca!");
            _user.fmsg("Non può sostituire",Mon->get_race());
            _user.fmsg("Deve attaccare.");
        }
        _user.msg("Scegliere l'attacco:");
        user_attack(Mon);
        return false;
    }
}

void match::change()
{
    int i=0;
    while (i<_user.get_num_monster_team())
    {
        if (i != _user_monster_on_field)
        {
            cout << i << ") " << _user.get_name_monster_team(i) << endl;
        }
        ++i;
    }
    int choice;
    std::cin.ignore(0,'\n');
    while (!(cin >> choice)||(!(choice<_user.get_num_monster_team())||(choice==_user_monster_on_field)))
    {
        msg("Il numero DEVE essere uno di quelli indicati, reinserire:");
        std::cin.clear();
        std::cin.ignore(1,'\n');
    }
    monster * tmp_mon = _user.get_monster(_user_monster_on_field);
    tmp_mon ->reset_Stats();
    string tmp_name = _user.get_name_monster_team(_user_monster_on_field);
    _user.fmsg("Statistiche di",tmp_name,"resettate a",tmp_mon->get_ap(),tmp_mon->get_dp(),tmp_mon->get_sp());
    _user_monster_on_field = choice;
    _user.fmsg("Sostituzione",tmp_name,"per",_user.get_name_monster_team(_user_monster_on_field));
    cout << endl;
}

void match::user_attack(monster *Mon)
{
    for (int i=0; i<4; ++i)
    {
        cout << i << ") " << Mon->get_attack_name(i) << endl;
    }
    int choice;
    std::cin.ignore(0,'\n');
    while (!(cin >> choice)||(!(choice<4)))
    {
        msg("Il numero DEVE essere uno di quelli indicati, reinserire:");
        std::cin.clear();
        std::cin.ignore(1,'\n');
    }
    cout << endl;
    _user_attack = Mon->get_attack(choice);
}

void match::PC_attack(monster *Mon)
{
    int rand_pc_att = (randFz::NRandom(4));
    _PC_attack = Mon->get_attack(rand_pc_att);
}

bool match::speed(monster *MonPC,monster *MonUser)//return: true->user's monster is faster than PC's one
{
    if ((_PC_attack.get_priority())!=(_user_attack.get_priority())) //only one with priority
    {
        if (_PC_attack.get_priority() == true)  //PC_p == true
        {
            MonPC->fmsg("Sorteggiato l'attacco con priorita'",_PC_attack.get_Name());
            MonUser->fmsg("Scelto l'attacco senza priorita'",_user_attack.get_Name());
            return false;
        }
        else    //user_p == true
        {
            MonUser->fmsg("Scelto l'attacco con priorita'",_user_attack.get_Name());
            MonPC->fmsg("Sorteggiato l'attacco senza priorita'",_PC_attack.get_Name());
            return true;
        }
    }
    else    //(no one has priority)OR(both with priority)
    {
        MonUser->fmsg("Velocita'",MonUser->get_sp());
        MonPC->fmsg("Velocita'",MonPC->get_sp());
        if(MonPC->get_sp() != MonUser->get_sp())    //PC_speed != user_speed
        {
            if(MonPC->get_sp() < MonUser->get_sp()) //PC_speed < user_speed
            {
                return true;
            }
            else                                    //PC_speed > user_speed
            {
                return false;
            }
        }
        else                                        //PC_speed == user_speed
        {
            bool tmp_random_turn = randFz::chooseRandom();
            if (tmp_random_turn)
            {
                fmsg("Sorteggiato", _user.get_username());
            }
            else
            {
                fmsg("Sorteggiato", _PC.get_username());
            }
            return (tmp_random_turn);
        }
    }
}

void match::fight()
{
    monster * MA = _PC.get_monster(_PC_monster_on_field);
    monster * MD = _user.get_monster(_user_monster_on_field);
    int counter_cycle = 0;
    bool user_turn = false;
    int att_cycle = 0;  //MAX attack cycle if 1:(A-D), else if 2:(A-D , D-A)
    int ROUND = 0;
    while ((_PC.void_team()==false)&&(_user.void_team()==false))//until: empty team
    {
        cout << "\t--------------\n" << endl;
        att_cycle = 0;
        while ((MA->get_is_dead()==false)&&(MD->get_is_dead()==false)&&(att_cycle!=1))//until: no dead and no change
        {
            MA = _PC.get_monster(_PC_monster_on_field);
            MD = _user.get_monster(_user_monster_on_field);
            counter_cycle = 0;
            msg("Turno", ROUND);
            fmsg("\t\t***\n");
            fmsg("Turno", ROUND);
            cout << endl;
            MD->msg("HP",MD->get_hp());
            MA->msg("HP",MA->get_hp());
            MD->fmsg("HP",MD->get_hp());
            MA->fmsg("HP",MA->get_hp());

            PC_attack(MA);//attack analysis for PC
            if ((menu(MD)==true))//change monster
            {
                att_cycle = 1;
                MA = _PC.get_monster(_PC_monster_on_field);
                MD = _user.get_monster(_user_monster_on_field);
                user_turn = false;
            }
            else//attack analysis for user
            {
                att_cycle = 2;
                if (speed(MA, MD)==true)//user FASTER than PC
                {
                    MD = _PC.get_monster(_PC_monster_on_field);
                    MA = _user.get_monster(_user_monster_on_field);
                    user_turn = true;
                }
                else//PC FASTER than user
                {
                    MA = _PC.get_monster(_PC_monster_on_field);
                    MD = _user.get_monster(_user_monster_on_field);
                    user_turn = false;
                }
            }
//FIGHT
            while ((counter_cycle<att_cycle)&&(MA->get_is_dead()==false)&&(MD->get_is_dead()==false))
            {
                attacchi tmp_attack;
                if (user_turn)//which attack has to be analyzed?     //user attack
                {
                    tmp_attack = _user_attack;
                }
                else                                                //pc attack
                {
                    tmp_attack = _PC_attack;
                }
//ATTACCO VERO E PROPRIO
                string tmp_mit_priority, tmp_fighter_turn;
                if (tmp_attack.get_priority()==true)        //priority attack
                {
                    tmp_mit_priority = "con";
                }
                else                                        //normal attack
                {
                    tmp_mit_priority = "senza";
                }
                if (user_turn==true)                        //user attack
                {
                    tmp_fighter_turn = "Scelto";
                }
                else                                        //NPC attack
                {
                    tmp_fighter_turn = "Sorteggiato";
                }

                MA->msg("Usa",tmp_attack.get_Name());
                MA->fmsg(tmp_fighter_turn,"attacco", tmp_mit_priority,"priorita' :",tmp_attack.get_Name());

                int tmp_damage = 0;

                if ((tmp_attack.get_attack_type()==2)||(tmp_attack.get_attack_type()==3))//MOD STAT
                {
                    string f_a_or_d,a_or_d,f_limit;
                    bool upper;
                    if (tmp_attack.get_influence()>0)
                    {
                        f_a_or_d = "dovrebbe aumentare da";
                        a_or_d = "non puo' piu' aumentare.";
                        f_limit = "ma non posso aumentare oltre";
                        upper = true;
                    }
                    else
                    {
                        f_a_or_d = "dovrebbe diminuire da";
                        a_or_d = "non puo' piu' diminuire.";
                        f_limit = "ma non posso diminuire oltre";
                        upper = false;
                    }
                    if (tmp_attack.get_target())    //attacker
                    {
                        MA->msg(define_stat(tmp_attack.get_statistic()),define_influence(tmp_attack.get_influence()));
                        int previous_value = monster_stat_value(*MA,tmp_attack.get_statistic());
                        if((MA->modify_stat(tmp_attack.get_statistic(),tmp_attack.get_influence()))==true)
                        {
                            MA->msg(define_stat(tmp_attack.get_statistic()),a_or_d);
                            int limit = limit_statistic_value(*MA, upper, tmp_attack.get_statistic());
                            MA->fmsg(define_stat(tmp_attack.get_statistic()),f_a_or_d,previous_value,"a",(previous_value*exp2(tmp_attack.get_influence())),f_limit,limit);
                        }
                        MA->fmsg(define_stat(tmp_attack.get_statistic()),monster_stat_value(*MA,tmp_attack.get_statistic()));
                    }
                    else                            //defender
                    {
                        MD->msg(define_stat(tmp_attack.get_statistic()),define_influence(tmp_attack.get_influence()));
                        int previous_value = monster_stat_value(*MD,tmp_attack.get_statistic());
                        if((MD->modify_stat(tmp_attack.get_statistic(),tmp_attack.get_influence()))==true)
                        {
                            MD->msg(define_stat(tmp_attack.get_statistic()),a_or_d);
                            int limit = limit_statistic_value(*MD, upper, tmp_attack.get_statistic());
                            MD->fmsg(define_stat(tmp_attack.get_statistic()),f_a_or_d,previous_value,"a",(previous_value*exp2(tmp_attack.get_influence())),f_limit,limit);
                        }
                        MD->fmsg(define_stat(tmp_attack.get_statistic()),monster_stat_value(*MD,tmp_attack.get_statistic()));
                    }
                }
                if ((tmp_attack.get_attack_type()==1)||(tmp_attack.get_attack_type()==3))//ATTACK HP
                {
                    tmp_damage = (MA->calculate_partialDamage(tmp_attack.get_PDB()));
                    MA->fmsg("Attacca con",tmp_attack.get_Name(),"infliggendo all'avversario un danno agli HP di",(tmp_damage/MD->get_dp()));
                    MD->reduce_HP(tmp_damage);
                    MD->fmsg("Nuovi HP",MD->get_hp());
                }
//END ATTACK
                MD->msg("Danno subito",(tmp_damage/MD->get_dp()));

                if ((MD->get_is_dead()==false)&&(att_cycle==2)&&(counter_cycle<1))
                {
                    swap(MA,MD);    //invert MA and MD
                    user_turn = !user_turn;
                    cout << "\t\t---"<< endl;
                }
                ++counter_cycle;
            }
//CHECK DEADS
            if(MD->get_is_dead())  //if MD is dead
            {
                if (user_turn)          //if user was last MA => PC's monster is dead
                {
                    monster * tmp_m = _PC.get_monster(_PC_monster_on_field);
                    tmp_m->msg("E' morto","non potra' piu' combattere.");
                    tmp_m->fmsg("HP",tmp_m->get_hp());
                    tmp_m->fmsg("E' morto","non potra' piu' combattere.");
                    _PC.delete_monster(_PC_monster_on_field);
                    if(_PC.get_num_monster_team()!=0)
                    {
                        _PC_monster_on_field = randFz::NRandom(_PC.get_num_monster_team());
                        tmp_m = _PC.get_monster( _PC_monster_on_field);
                        tmp_m ->reset_Stats();
                        MD = _PC.get_monster(_PC_monster_on_field);
                    }
                    else
                    {
                        return;
                    }
                    _PC.msg("Numero di mostri rimasti nel team",_PC.get_num_monster_team());
                    _PC.fmsg("Numero di mostri rimasti nel team",_PC.get_num_monster_team());
                }
                else                    //if PC was last MA => user's monster is dead
                {
                    monster * tmp_m = _user.get_monster(_user_monster_on_field);
                    tmp_m->msg("E' morto","non potra' piu' combattere.");
                    tmp_m->fmsg("HP",tmp_m->get_hp());
                    tmp_m->fmsg("E' morto","non potra' piu' combattere.");
                    _user.delete_monster(_user_monster_on_field);
                    if(_user.get_num_monster_team()!=0)
                    {
                        _user_monster_on_field = randFz::NRandom(_user.get_num_monster_team());
                        tmp_m = _user.get_monster(_user_monster_on_field);
                        tmp_m ->reset_Stats();
                        MD = _user.get_monster(_user_monster_on_field);
                    }
                    else
                    {
                        return;
                    }
                    _user.msg("Numero di mostri rimasti nel team",_user.get_num_monster_team());
                    _user.fmsg("Numero di mostri rimasti nel team",_user.get_num_monster_team());
                }
                cout<<"\n"<<endl;
            }
            ++ROUND;
            if (att_cycle==2)
            {
                cout << "\t\t***\n" << endl;
            }
        }
    }
    delete MA;
    delete MD;
}

void match::end_match()
{
    cout << "\n\n\n\t-+-+-+-+-+-+-+-+-+-+-+-+-\n\n" << endl;
    fmsg("\t-+-+-+-+-+-+-+-+-+-+-+-+-");
    if(_PC.void_team()==true)
    {
        msg(_user.get_username(),"Vince il match");
        fmsg("Si conclude il match con la vittoria di",_user.get_username());
        fmsg(get_date_time());
        return;
    }
    if(_user.void_team()==true)
    {
        msg(_PC.get_username(),"Vince il match");
        fmsg("Si conclude il match con la vittoria di",_PC.get_username());
        fmsg(get_date_time());
        return;
    }
}
