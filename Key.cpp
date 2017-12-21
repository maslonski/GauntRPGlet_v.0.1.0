#include "Key.h"

#include <stdlib.h>

#include "Player.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Statistics.h"

#include <iostream>

Key::Key(const Sprite &_sprite, float2 _position,
               float _orientation)
    :Items(_sprite, _position, _orientation)
{
    sprite.play(0, 10);/////
    //sprite.resume();
}

Key::~Key(){}

void Key::draw()
{

    sprite.draw(position, orientation, 2.f);
}


