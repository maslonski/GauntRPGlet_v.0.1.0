#ifndef SPAWNER_H
#define SPAWNER_H

#include "Objects.h"

class Spawner : public Objects
{
    public:
        Spawner(const Sprite &, float2, float, Entity *);
        virtual ~Spawner();

        void update();
        void draw();
    protected:
        Entity *target;
    private:
};

#endif // BUNKER_H
