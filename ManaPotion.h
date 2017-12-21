#ifndef MANAPOTION_H
#define MANAPOTION_H

#include "Potions.h"
class ManaPotion : public Potions
{
    public:
        ManaPotion(const Sprite &, float2, float);
        virtual ~ManaPotion();
        void draw();
    protected:
    private:
};

#endif // MANAPOTION_H
