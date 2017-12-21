#ifndef OBJECTS_H
#define OBJECTS_H

#include "Entity.h"

class Objects : public Entity
{
    public:
        Objects(const Sprite &, float2, float);
        virtual ~Objects();

        //virtual void action();
    protected:
    private:
};

#endif // OBJECTS_H
