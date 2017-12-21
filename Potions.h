#ifndef POTIONS_H
#define POTIONS_H

#include "Items.h"

class Potions : public Items
{
    public:
        Potions(const Sprite &, float2, float);
        virtual ~Potions();
    protected:
    private:
};

#endif // POTIONS_H
