#ifndef FIREBALL_H
#define FIREBALL_H

#include "Weapons.h"

class FireBall : public Weapons
{
    public:
        FireBall(const Sprite &, float2, float, float);
        virtual ~FireBall();

        void update();
        void draw();

        virtual void kill();
    protected:
        unsigned int delTime;
    private:
};

#endif // FIREBALL_H
