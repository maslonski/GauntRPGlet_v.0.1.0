#include "Items.h"


class Key : public Items
{
    public:
        Key(const Sprite &, float2, float);
        virtual ~Key();

        void draw();
    protected:
        Entity * target;
    private:


};
