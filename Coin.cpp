#include "Coin.h"

Coin::Coin(const Sprite &_sprite, float2 _position, float _orientation)
    : Items(_sprite, _position, _orientation)
{
    //ctor
}

Coin::~Coin()
{
    //dtor
}

void Coin::draw()
{
    sprite.draw(position, orientation, 0.7f);
}
