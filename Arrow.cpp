#include <windows.h>

#include "Arrow.h"
#include "Terrain.h"
#include "Entity.h"

#include "ResourceFactory.h"

Arrow::Arrow(const Sprite &_sprite,
           float2 _position, float _orientation,
           float _speed)
    :Weapons(_sprite, _position, _orientation)
    ,delTime(GetTickCount()+1000)
{
    velocity = float2(_orientation) * _speed;
    radius = .15f;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
    position += velocity * .05f;
    if (GetTickCount() > delTime
        || !Terrain::get().collision('1', position, .5).isZero()
        || !Terrain::get().collision('2', position, .5).isZero()
        || !Terrain::get().collision('3', position, .5).isZero()
        || !Terrain::get().collision('4', position, .5).isZero()
        || !Terrain::get().collision('5', position, .5).isZero()
        || !Terrain::get().collision('6', position, .5).isZero()
        || !Terrain::get().collision('7', position, .5).isZero()
        || !Terrain::get().collision('8', position, .5).isZero()
        || !Terrain::get().collision('9', position, .5).isZero()
        || !Terrain::get().collision('q', position, .5).isZero()
        || !Terrain::get().collision('w', position, .5).isZero()
        || !Terrain::get().collision('e', position, .5).isZero()
        )

    {
        deleted = true;
    }
}

void Arrow::draw()
{
    sprite.draw(position, orientation, .5f);
}

void Arrow::kill()
{
    deleted = true;
}

