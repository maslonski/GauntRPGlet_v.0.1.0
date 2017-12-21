#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entity.h"


class Explosion : public Entity
{
    public:
        Explosion(const Sprite &, float2, float);
        virtual ~Explosion();

        void update();
    protected:
        unsigned int delTime;   // czas usuniecia
    private:
};

#endif // EXPLOSION_H
