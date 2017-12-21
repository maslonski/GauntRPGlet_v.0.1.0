#include "Tree.h"
#include "ResourceFactory.h"

#include <stdlib.h>

Tree::Tree(const Sprite &_sprite, float2 _position)
    :Objects(_sprite, _position, 1.f)
{
    sprite.play(0,0);
}

Tree::~Tree()
{
    //dtor
}
