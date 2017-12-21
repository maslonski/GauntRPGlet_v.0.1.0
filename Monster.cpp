#include "Monster.h"

Monster::Monster(const Sprite &_sprite,
           float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation)
{
}

Monster::~Monster()
{
}
