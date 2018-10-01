#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <cstdlib>


#include "match.h"
/*
#include "randFz.h"
#include "monster.h"
#include "attacchi.h"
#include "Logger.h"
#include "player.h"
*/
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));                //init seed for rand generation
    ofstream f_log;                                 //creates f.var for output file
    f_log.open("log.txt");                          //link f.var to .txt file
    cout << "Benvenuto su CppMon!\n" << endl;

    match * partita;                                //creates ptr of type 'match'
        //creates new match obj - passing it input.file name and output.log.file address
    partita = new match("attacchi.txt","mostri.txt","squadre.txt", &f_log);
    partita->fight();                               //starts fight
    partita->end_match();                           //ends fight

    cout << "\n\n\tEND" << endl;
    delete partita;                                 //delete ptr and free memory
    return 0;
}
