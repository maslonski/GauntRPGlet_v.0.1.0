#ifndef POTION_H
#define POTION_H

//#include "Entity.h"
#include "Potions.h"

class HpPotion : public Potions
{
    public:
        HpPotion(const Sprite &, float2, float);
        virtual ~HpPotion();
    protected:
    private:
};

#endif // POTION_H
