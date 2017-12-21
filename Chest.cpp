#include "Chest.h"
#include "ResourceFactory.h"
#include "ArrowPack.h"
#include "Coin.h"
#include "HpPotion.h"
#include "ManaPotion.h"
#include "Objects.h"
#include "Player.h"
#include "Terrain.h"
#include "Items.h"

#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include "SoundFactory.h"

using std::cout;
using std::endl;

Chest::Chest(const Sprite &_sprite, float2 _position,
               float _orientation)
    :Objects(_sprite, _position, _orientation)
{
    sprite.play(0,0);
}

Chest::~Chest()
{
}

void Chest::draw()
{
    sprite.draw(position, orientation, 1.f);

}

void Chest::action()
{
    sprite.play(0,3);
    srand( time( NULL ) );

    ComponentManager::get().find<Player>();
    Player *p = ComponentManager::get().next<Player>();

    float2 tmpPos = p->getPosition();
	BASS_ChannelPlay(SoundFactory::get().load("chest.wav") , FALSE);////////
    switch ( rand() % 4 )
    {

        case 0:
            if (Terrain::get().getTileType(float2(tmpPos.x-1, position.y-1)) == 'f')
            {
                ComponentManager::get().add(
                        new ArrowPack(Sprite(ResourceFactory::get().load("arrows_pack.bmp")),
                        float2(tmpPos.x-1 , position.y - 1.f), 0));
                break;
            }
            else{
                if (Terrain::get().getTileType(float2(tmpPos.x+1, position.y-1)) == 'f')
                {
                    ComponentManager::get().add(
                        new ArrowPack(Sprite(ResourceFactory::get().load("arrows_pack.bmp")),
                        float2(tmpPos.x+1 , position.y - 1.f), 0));
                    break;
                }
            }

            break;
        case 1:
            if (Terrain::get().getTileType(float2(tmpPos.x-1, position.y-1)) == 'f')
            {
            ComponentManager::get().add(
                new Coin(Sprite(ResourceFactory::get().load("coin.bmp")),
                            float2(tmpPos.x-1 , position.y - 1.f), 0));
                break;
            }
            else{
                if (Terrain::get().getTileType(float2(tmpPos.x+1, position.y-1)) == 'f')
                {
            ComponentManager::get().add(
                new Coin(Sprite(ResourceFactory::get().load("coin.bmp")),
                            float2(tmpPos.x+1, position.y - 1.f), 0));
                    break;
                }
            }

            break;
        case 2:
            if (Terrain::get().getTileType(float2(tmpPos.x-1, position.y-1)) == 'f')
            {
                ComponentManager::get().add(
                new HpPotion(Sprite(ResourceFactory::get().load("potion4.bmp")),
                            float2(tmpPos.x-1, position.y - 1.f), 0));
                break;
            }
            else{
                if (Terrain::get().getTileType(float2(tmpPos.x+1, position.y-1)) == 'f')
                {
                    ComponentManager::get().add(
                new HpPotion(Sprite(ResourceFactory::get().load("potion4.bmp")),
                            float2(tmpPos.x+1 , position.y - 1.f), 0));
                break;
                }
            }

            break;
        default:
            if (Terrain::get().getTileType(float2(tmpPos.x-1, position.y-1)) == 'f')
            {
                ComponentManager::get().add(
                    new ManaPotion(Sprite(ResourceFactory::get().load("manaPotion.bmp")),
                            float2(tmpPos.x-1 , position.y - 1.f), 0));
                break;
            }
            else{
                if (Terrain::get().getTileType(float2(tmpPos.x+1, position.y-1)) == 'f')
                {
                    ComponentManager::get().add(
                        new ManaPotion(Sprite(ResourceFactory::get().load("manaPotion.bmp")),
                            float2(tmpPos.x+1 , position.y - 1.f), 0));
                    break;
                }
            }

            break;
    }
    sprite.play(3,3);
    active = false;
}
