#include "ManaPotion.h"

ManaPotion::ManaPotion(const Sprite &_sprite, float2 _position, float _orientation)
    : Potions(_sprite, _position, _orientation)
{
    //ctor
}

ManaPotion::~ManaPotion()
{
    //dtor
}

void ManaPotion::draw()
{
    sprite.draw(position, orientation, 0.7f);
}
