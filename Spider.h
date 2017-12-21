#ifndef SPIDER_H
#define SPIDER_H

#include "Monster.h"

class Spider : public Monster
{
    public:
        Spider(const Sprite &, float2, float, Entity *);
        virtual ~Spider();

        void update();
        virtual void kill();
    protected:
        Entity *target;
    private:
        int exp;
};

#endif // ENEMY_H
