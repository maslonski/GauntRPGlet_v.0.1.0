#include <iostream>

#include "Statistics.h"

using std::cout;
using std::endl;

Statistics::Statistics()
    :gold(100)
    ,hpMax(100)
    ,manaMax(100)
    ,exp(1)
    ,expNeed(5)
    ,lvl(1)
    ,hp(hpMax)
    ,mana(manaMax)
    ,hpPotions(5)
    ,manaPotions(3)
    ,arrows(12)
    ,ileDungeons(0)
    ,ileKluczy(0)
{
    cout << "Statistic()" << endl;
}

void Statistics::reset()
{
    gold        = 100;
    hpMax       = 100;
    manaMax     = 100;
    exp         = 1;
    expNeed     = 5;
    lvl         = 1;
    hp          = hpMax;
    mana        = manaMax;
    hpPotions   = 5;
    manaPotions = 3;
    arrows      = 12;
    ileDungeons = 0;
    ileKluczy   = 0;
}

Statistics::~Statistics(){}
