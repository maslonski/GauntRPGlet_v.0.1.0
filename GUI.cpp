
#include "GUI.h"

GUI::GUI(const Sprite& _sprite)
    : sprite(_sprite)
{

}

GUI::~GUI()
{
    //dtor
}

void GUI::draw(float2 position, float scaleX, float scaleY)
{
    //sprite.play( 0, 1 );
    sprite.draw(position, 0.f, scaleX, scaleY);
}

void GUI::drawBar(float2 position, float scaleX, float scaleY, float posX)
{
    sprite.drawBar(position, 0.f, scaleX, scaleY, posX);
}
