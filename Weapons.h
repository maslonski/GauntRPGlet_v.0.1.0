#ifndef WEAPONS_H
#define WEAPONS_H

#include "Entity.h"

class Weapons : public Entity
{
    public:
        Weapons(const Sprite &_sprite,
           float2 _position, float _orientation);
        virtual ~Weapons();
    protected:
    private:
};

#endif // WEAPONS_H
