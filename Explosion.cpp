#include "Explosion.h"
#include <windows.h>

Explosion::Explosion(const Sprite &_sprite,
           float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation)
    ,delTime(GetTickCount() + 500)  // powinno trwac 0,5 sec
{
    sprite.play(0, 4);
}

Explosion::~Explosion()
{
    //dtor
}

void Explosion::update()
{
    if (GetTickCount() > delTime){
        deleted = true;
    }
    sprite.update();
}
