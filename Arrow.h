#ifndef ARROW_H
#define ARROW_H

#include "Weapons.h"


class Arrow : public Weapons
{
    public:
        Arrow(const Sprite &, float2, float, float);
        virtual ~Arrow();

        void update();
        void draw();

        virtual void kill();
    protected:
        unsigned int delTime;
    private:
};

#endif // BULLET_H
