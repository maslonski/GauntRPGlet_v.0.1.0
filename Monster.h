#ifndef TANK_H
#define TANK_H

#include "Entity.h"

class Monster : public Entity
{
    public:
        Monster(const Sprite &, float2, float);
        virtual ~Monster();
    protected:
    private:
};

#endif // TANK_H
