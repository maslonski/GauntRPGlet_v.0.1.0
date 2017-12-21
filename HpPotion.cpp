#include "HpPotion.h"

HpPotion::HpPotion(const Sprite &_sprite, float2 _position, float _orientation)
    : Potions(_sprite, _position, _orientation)
{
    //sprite.play(0.5, 0.5);
}

HpPotion::~HpPotion()
{
    //dtor
}
