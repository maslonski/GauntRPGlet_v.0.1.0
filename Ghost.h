#ifndef GHOST_H
#define GHOST_H

#include "Monster.h"

class Ghost : public Monster
{
    public:
        Ghost(const Sprite &, float2, float, Entity *);
        virtual ~Ghost();

        void update();
        virtual void kill();
    protected:
        Entity *target;
    private:
};

#endif // ENEMY_H
