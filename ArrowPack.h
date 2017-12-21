#ifndef ARROWPACK_H
#define ARROWPACK_H

#include "Items.h"
class ArrowPack : public Items
{
    public:
        ArrowPack(const Sprite &, float2, float);
        virtual ~ArrowPack();
    protected:
    private:
};

#endif // ARROWPACK_H
