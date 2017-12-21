#ifndef COIN_H
#define COIN_H

#include "Items.h"

class Coin : public Items
{
    public:
        Coin(const Sprite &, float2, float);
        virtual ~Coin();
        void draw();
    protected:
    private:
};

#endif // COIN_H
