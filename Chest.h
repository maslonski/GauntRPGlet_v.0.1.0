#ifndef CHEST_H
#define CHEST_H

#include "Objects.h"

class Chest : public Objects
{
    public:
        Chest(const Sprite &, float2, float);
        virtual ~Chest();

        void action();
        void draw();
    protected:
    private:
};

#endif // CHEST_H
