#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <iostream>

#include "Ghost.h"
#include "Arrow.h"
#include "Terrain.h"
#include "ResourceFactory.h"
#include "Coin.h"
#include "Player.h" ///////////////////////
#include "HpPotion.h"
#include "ManaPotion.h"
#include "FireBall.h"
#include "Chest.h"
#include "Statistics.h"
#include "SoundFactory.h"

using std::cout;
using std::endl;

Ghost::Ghost(const Sprite &_sprite, float2 _position,
             float _orientation, Entity *_target)
    :Monster(_sprite, _position, _orientation)
    ,target(_target)
{
    sprite.play(0, 3);
}

Ghost::~Ghost()
{
}

void Ghost::kill()
{
    srand( time( NULL ) );

    switch ( rand() % 10 )
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        ComponentManager::get().add(
            new Coin(Sprite(ResourceFactory::get().load("coin.bmp")),
                        position, 0));
        break;
    case 6:
        ComponentManager::get().add(
            new HpPotion(Sprite(ResourceFactory::get().load("potion4.bmp")),
                        position, 0));
        break;
    case 7:
        ComponentManager::get().add(
            new ManaPotion(Sprite(ResourceFactory::get().load("manaPotion.bmp")),
                        position, 0));
        break;
    }

    deleted = true;


    ComponentManager::get().find<Player>();/////////
    Player *p = ComponentManager::get().next<Player>();/////////

    p -> gainExp(1);    /////////
}

void Ghost::update()
{
//    Arrow *arrow = collisionWith<Arrow>();
//    if (arrow != NULL){
//            arrow -> kill();
//            hp -= rand() * 60 / RAND_MAX;
//            if (hp<0){
//                kill();
//                return;
//            }
//    }

    FireBall *fireBall = collisionWith<FireBall>();
    if (fireBall != NULL){
		BASS_ChannelPlay(SoundFactory::get().load("mage_atk.wav") , TRUE);////////
        fireBall -> kill();
        kill();

    }

    float2 diff = target->getPosition() - position;
    float2 force = diff.normalized() - velocity;
    velocity += force * 0.01f;
    velocity.clampLen(0.02f);
    if (diff.len()> .7f)
    {
        position += velocity;
        float2 coll = Terrain::get().collision('1', position, .5);
        position += coll;

        coll = Terrain::get().collision('2', position, .5);
        position += coll;

        coll = Terrain::get().collision('3', position, .5);
        position += coll;

        coll = Terrain::get().collision('4', position, .5);
        position += coll;

        coll = Terrain::get().collision('5', position, .5);
        position += coll;

        coll = Terrain::get().collision('6', position, .5);
        position += coll;

        coll = Terrain::get().collision('7', position, .5);
        position += coll;

        coll = Terrain::get().collision('8', position, .5);
        position += coll;

        coll = Terrain::get().collision('9', position, .5);
        position += coll;

        coll = Terrain::get().collision('q', position, .5);
        position += coll;

        coll = Terrain::get().collision('w', position, .5);
        position += coll;

        coll = Terrain::get().collision('e', position, .5);
        position += coll;

        Entity *e = collisionWith<Monster>(this);
        if (e != NULL)
            position+=collisionSeparate(e);
        e = collisionWith<Humans>(this);
        if (e != NULL)
            position+=collisionSeparate(e);
        e = collisionWith<Chest>();
        if (e != NULL)
            position += collisionSeparate(e);
        sprite.resume();
    }
    else
        sprite.pause();
    float2 direction(orientation);
    direction += velocity * 3.f;
    if ( fabs(orientation - direction.toAngle()) > .1f )
    {
        orientation = direction.toAngle();
        sprite.resume();
    }

    if (diff.len() < 4.f && rand() < RAND_MAX/20){  //wektor roznicy miedzy przediwnikiem a targetem
//        ComponentManager::get().add(
//            new Arrow(
//                Sprite(ResourceFactory::get().load("bullet.bmp")),
//                position + float2(orientation) * .8f,
//                orientation,
//                .8f
//            )
//        );
        Entity *e = collisionMelle<Player>(this);
        if (e != NULL)
        {
        	BASS_ChannelPlay(SoundFactory::get().load("ghost_atk.wav") , TRUE);////////
            float2 me = orientation;
            float2 him = e->getOrientation();

            me.normalized();
            him.normalized();


            float wynik = me.skalar(him);
            cout << "Wynik: " << wynik << endl;
            if(wynik < 0  )
            {
                Statistics::get().changeHp(-(rand() * 20 / RAND_MAX));
            }
            cout <<"HP: " << e->getHp() << endl;

            //e -> kill();
            //position += collisionSeparate(e);
        }


    }

    sprite.update();
}
