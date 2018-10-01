#include "randFz.h"
randFz::randFz()
{}
randFz::~randFz()
{}

int randFz::NRandom(int numb)   //da 0 a numb-1
{
    int number;
    if (numb == 0)
    {
        number = 0;
    }
    else
    {
        number = rand() %numb;
    }
    return number;
}

bool randFz::chooseRandom()      //true or false
{
    int number = 0;
    number = rand() % 2;
    if (number == 0)
    {
        return false;
    }
    else //number == 1
    {
        return true;
    }
}

float randFz::AttackRandom()    //[0.8;1]
{
    float rnumb = 0;
    int number = 0;
    number = rand() % 3 + 8;
    rnumb = float(number)/10;
    return rnumb;
}
