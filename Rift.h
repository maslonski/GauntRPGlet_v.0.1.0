#include "Objects.h"
#include "Statistics.h"


class Rift : public Objects
{
    public:
        Rift(const Sprite &, float2, float);
        virtual ~Rift();

        void update();
        void draw();

    protected:
        Entity * target;
    private:
};
