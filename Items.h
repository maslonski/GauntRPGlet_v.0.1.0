#ifndef ITEMS_H
#define ITEMS_H

#include "Entity.h"

class Items :public Entity
{
    public:
        Items(const Sprite &, float2, float);
        virtual ~Items();
    protected:
    private:
};

#endif // ITEMS_H
