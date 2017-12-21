#ifndef HUMANS_H
#define HUMANS_H

#include "Entity.h"

class Humans : public Entity
{
    public:
        Humans(const Sprite &, float2, float);
        virtual ~Humans();
    protected:
    private:
};

#endif // TANK_H
