#include "Rift.h"

#include <stdlib.h>

#include "Player.h"
#include "ResourceFactory.h"

#include "ComponentManager.h"
#include "Terrain.h"

#include <iostream>

Rift::Rift(const Sprite &_sprite, float2 _position,
               float _orientation)
    :Objects(_sprite, _position, _orientation)
{

    radius = .8f;
    sprite.play(0,4);
    sprite.resume();
}

Rift::~Rift(){}

void Rift::draw()
{
    sprite.draw(position, orientation, 2.f);
}

void Rift::update()
{

    Player *player = collisionWith<Player>();
    if (player != NULL)
    {

            switch(Statistics::get().getIleDungeons())
            {
            case 0:
                player->ustawRift(true);
                std::cout<< "jestem w case 0"<<std::endl;
            break;

            case 1:
                player->ustawRift(true);
                std::cout<< "jestem w case 1"<<std::endl;
            break;
            }
           /* bullet -> kill();
            hp -= rand() * 30 / RAND_MAX;
            if (hp < 0){
                deleted = true;
                return;
            }*/
            //sprite.play((100-hp)/26, (100-hp)/26);
    }
	sprite.update();

}
