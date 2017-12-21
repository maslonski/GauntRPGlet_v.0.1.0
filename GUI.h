#ifndef GUI_H
#define GUI_H


#include "Sprite.h"
class GUI
{
    public:
        GUI(const Sprite&);
        virtual ~GUI();

        void draw(float2, float, float);
        void drawBar(float2 position, float scaleX, float scaleY, float posX);
    protected:
        Sprite sprite;
    private:
};

#endif // GUI_H
