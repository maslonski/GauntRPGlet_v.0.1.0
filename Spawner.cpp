#include <stdlib.h>
#include <cstdio>
#include <ctime>

#include "Spawner.h"
#include "Arrow.h"
#include "ResourceFactory.h"
#include "Monster.h"
#include "Humans.h"
#include "Ghost.h"
#include "Spider.h"
#include "Statistics.h"

Spawner::Spawner(const Sprite &_sprite, float2 _position,
               float _orientation, Entity *_target)
    :Objects(_sprite, _position, _orientation), target(_target)
{
    //sprite.play(0,0);
}

Spawner::~Spawner()
{
}

void Spawner::draw()
{
    sprite.draw(position, orientation, 1.f);
}

void Spawner::update()
{
    Arrow *arrow = collisionWith<Arrow>();
    if (arrow != NULL){
            arrow -> kill();
            hp -= rand() * 30 / RAND_MAX;
            if (hp < 0){
                deleted = true;
                return;
            }
            //sprite.play((100-hp)/26, (100-hp)/26);
    }
    radius = 3.f;
    if (rand() < RAND_MAX/2000// (Statistics::get().getIleKluczy()+1))/////////////////////////////////
        && collisionWith<Humans>() == NULL && collisionWith<Monster>() == NULL)
    {
        srand( time( NULL ) );
        float2 diff = (target->getPosition() - position).normalized();
        switch (rand() % 3)
        {
        case 0:
        case 1:
            ComponentManager::get().add(
            new Ghost(Sprite(ResourceFactory::get().load("duch.bmp"),
                             4/*8*/,
                             24),
                      position + diff * 1.1f,
                      diff.toAngle(),
                      target)
                                    );
            break;
        case 2:
            ComponentManager::get().add(
            new Spider(Sprite(ResourceFactory::get().load("pajak.bmp"),
                             4/*8*/,
                             24),
                      position + diff * 1.1f,
                      diff.toAngle(),
                      target)
                                    );
            break;
        }

    }
    radius = .45f;
}
