//This class contains 3 member fz used to compute in 3 different ways
//      a random number

#ifndef RANDFZ_H
#define RANDFZ_H
#include <iostream>
#include <cstdlib>
using namespace std;

class randFz
{
public:
    randFz();
    virtual ~randFz();
    static int NRandom(int numb);
    static bool chooseRandom();
    static float AttackRandom();
protected:
private:

};

#endif // RANDFZ_H
