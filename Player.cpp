#include <stdlib.h>
#include <iostream>

#include "Player.h"

#include "Terrain.h"
#include "Spawner.h"
#include "Arrow.h"
#include "Coin.h"
#include "ResourceFactory.h"
#include "Statistics.h"
#include "HpPotion.h"
#include "FireBall.h"
#include "Monster.h"
#include "ManaPotion.h"
#include "Chest.h"
#include "ArrowPack.h"
#include "Key.h"
#include "Npc.h"
#include "SoundFactory.h"
#include "bass.h"

using std::cout;
using std::endl;

Player::Player(const Sprite &_sprite,
           float2 _position, float _orientation)
    :Humans(_sprite, _position, _orientation)
    ,forward(false)
    ,backward(false)
    ,left(false)
    ,right(false)
    ,firePressed(false)
    ,actionPressed(false)
    ,weaponChange(false)
    ,tempOrientation(_orientation)
    ,interact(false)
    ,reload(false)
    ,PlayerState(BOW)
    ,interactionBegin(false)
{
    Statistics &s = Statistics::get();
    sprite.play(1, 3);
}



Player::~Player()
{
}

void Player::usePotion()
{
    if (Statistics::get().getPotion()>0 && Statistics::get().getHp()<Statistics::get().getHpMax()){
        Statistics::get().changeHp(20);
        Statistics::get().setPotion(-1);

        if (Statistics::get().getHp()>Statistics::get().getHpMax()){
            Statistics::get().setHp(Statistics::get().getHpMax());
            return;
        }
    }
}

void Player::useManaPotion()
{
    if (Statistics::get().getManaPotion()>0 && Statistics::get().getMana()<Statistics::get().getManaMax()){
        Statistics::get().changeMana(15);
        Statistics::get().setManaPotion(-1);

        if (Statistics::get().getMana() > Statistics::get().getManaMax()){
            Statistics::get().setMana(Statistics::get().getManaMax());
            return;
        }
    }
}

void Player::keyb(unsigned char key, bool down)
{
    switch (key)
    {
    case '1':
        if (down)
        {
            if (!potionPressed){
                usePotion();
            }
            potionPressed = true;
        }
        else{
            potionPressed = false;
        }
        break;
    case '2':
        if (down)
        {
            if (!potionPressed){
                useManaPotion();
            }
            potionPressed = true;
        }
        else{
            potionPressed = false;
        }
        break;
    case 'w':
        forward = down;
        //sprite.play(0,0);
        break;
    case 's':
        backward = down;
        //sprite.play(0,0);
        break;
    case 'a':
        left = down;
        break;
    case 'd':
        right = down;
        break;
    case 'f':
        if (down)
            {
                if (!actionPressed)
                {
                    Entity *e = collisionMelle<Chest>(this);
                    if (e != NULL && e->isActive() == true)
                    {
                    	float2 me = orientation;
                    	float2 him = e->getOrientation();

						me.normalized();
						him.normalized();


						float wynik = me.skalar(him);
						cout << "Wynik: " << wynik << endl;
						if(wynik > -1  )
                        {
                            e->action();
                        }


                    }
                    e = collisionMelle<Npc>(this);
                    if (e != NULL && e->isActive() == true)
                    {
                    	float2 me = orientation;
                    	float2 him = e->getOrientation();

						me.normalized();
						him.normalized();


						float wynik = me.skalar(him);
						cout << "Wynik: " << wynik << endl;
						if(wynik > -1  )
                        {
                            interact = down;
                            interactionBegin = true;
                            cout<<"Statistics::get().getIleDungeons()= " <<Statistics::get().getIleDungeons()<<endl;
                            cout<<"Statistics::get().getIleKluczy()= " <<Statistics::get().getIleKluczy()<<endl;
                        }


                    }
                    actionPressed = true;
                }

            }
            else
            {
                actionPressed = false;
            }
            break;
    case ' ':
        switch (PlayerState){
        case (SWORD):
            if (down)
            {
                if (!firePressed){

					BASS_ChannelPlay(SoundFactory::get().load("bow.wav") , TRUE);////////
                        //sprite.play(9,9);
                        if (Statistics::get().getArrows()> 0 ){
                            sprite.play(9, 9);
                            ComponentManager::get().add(
                                new Arrow(
                                    Sprite(ResourceFactory::get().load("arrow.bmp")),
                                    position + float2(orientation) * .8f,
                                    orientation,
                                    2.f
                                )
                            );
                            Statistics::get().changeArrows(-1);
                            //sprite.play(8, 8);
                        }


                    firePressed = true;
                }
            }
            else{
                firePressed = false;
                sprite.play(6,8);
            }

            break;
            //////////////////////////////////////////////////////////////
        case (BOW):
            if (down)
            {
                if (!firePressed)
                {
                	BASS_ChannelPlay(SoundFactory::get().load("rogue_atk.wav") , TRUE);////////
                    sprite.play(4,4);
                    Entity *e = collisionMelle<Monster>(this);
                    if (e != NULL)
                    {
                    	float2 me = orientation;
                    	float2 him = e->getOrientation();

						me.normalized();
						him.normalized();


						float wynik = me.skalar(him);
						cout << "Wynik: " << wynik << endl;
						if(wynik < 0  )
						{
						    e ->setHp(-40);
							if (e->getHp() <= 0)
                                e->kill();
						}
                        cout <<"HP: " << e->getHp() << endl;

                        //e -> kill();
                        //position += collisionSeparate(e);
                    }
                    e = collisionMelle<Spawner>();
                    if (e != NULL){
						BASS_ChannelPlay(SoundFactory::get().load("spawn_dead.wav") , FALSE);////////
						e -> kill();
                        position += collisionSeparate(e);
                    }

                    firePressed = true;
                }
            }
            else
            {
                firePressed = false;
                sprite.play(1,3);
            }
            //sprite.play(1,4);
            break;
            //////////////////////////////////////////////////////////////
        case (MAGIC):
            if (down)
            {
                if (!firePressed){

                        sprite.play(14,14);
                    if (Statistics::get().getMana() > 20){
                        Statistics::get().changeMana(-20);
                        ComponentManager::get().add(
                            new FireBall(
                                Sprite(ResourceFactory::get().load("bullet.bmp")),
                                position + float2(orientation) * .8f,
                                orientation,
                                2.f
                            )
                        );
                        firePressed = true;
                    }
                }
            }
            else{
                firePressed = false;
                sprite.play(11,13);
            }
            break;
        }

        break;
    case 'q':
        if (down){
            if (!weaponChange){
                switch (PlayerState){
                case (BOW):
                    PlayerState=SWORD;
                    sprite.play(6,8);
                break;

                case (SWORD):
                    PlayerState=MAGIC;  ////////
                    sprite.play(11, 13);
                break;
                case (MAGIC):
                    PlayerState=BOW;
                    sprite.play(1, 3);
                break;
                }
                weaponChange = true;
            }
        }
        else{
            weaponChange = false;
        }
        break;
    }
}

void Player::update()
{
    if (Statistics::get().getHp() < 0){
        Statistics::get().setHp(0);
        active = false;
        return;
    }

    Arrow *arrow = collisionWith<Arrow>();
    if (arrow != NULL){
        arrow -> kill();
        Statistics::get().changeHp(-(rand() * 20 / RAND_MAX));
        //hp -=rand() * 20 / RAND_MAX;
        if (Statistics::get().getHp() < 0){
            Statistics::get().setHp(0);
            active = false;
            return;
        }
    }

    FireBall *fb = collisionWith<FireBall>();
    if (fb != NULL){
		BASS_ChannelPlay(SoundFactory::get().load("spider_atk.wav") , TRUE);////////
        fb -> kill();
        Statistics::get().changeHp(-(rand() * 20 / RAND_MAX));
        //hp -=rand() * 20 / RAND_MAX;
        if (Statistics::get().getHp() < 0){
            Statistics::get().setHp(0);
            active = false;
            return;
        }
    }

    Key *key = collisionWith<Key>();
    if (key != NULL)
    {
    	BASS_ChannelPlay(SoundFactory::get().load("rift.wav") , FALSE);////////
        key->kill();
        Statistics::get().setIleKluczy(1);
        reload = true;

    }

    Coin *coin = collisionWith<Coin>();
    if (coin!=NULL)
    {
        Statistics::get().setGold((rand()%30) + 5);
        coin->kill();

    }

    HpPotion *hpPotion = collisionWith<HpPotion>();
    if (hpPotion!=NULL)
    {
        if (Statistics::get().getPotion()<10)
        {
            Statistics::get().setPotion(1);

        }
        hpPotion->kill();
    }

    ManaPotion *manaPotion = collisionWith<ManaPotion>();
    if (manaPotion!=NULL)
    {
        if (Statistics::get().getManaPotion()<10)
        {
            Statistics::get().setManaPotion(1);

        }
        manaPotion->kill();
    }

    ArrowPack *arrowPack = collisionWith<ArrowPack>();
    if (arrowPack!=NULL)
    {
        if (Statistics::get().getArrows()<18)
        {
                        Statistics::get().changeArrows(3);


            if (Statistics::get().getArrows()>18)
            {
                Statistics::get().setArrows(12);
            }

        }
        arrowPack->kill();
    }

    bool isMoving = false;
    if (forward)
    {
        velocity = float2(orientation)*.05f;
        //sprite.play(1,3);
        isMoving = true;
    }
    if (backward)
    {
        velocity = float2(orientation)*-.05f;
        //sprite.play(1,3);
        isMoving = true;
    }
    if (left)
    {
        orientation += 2.0f;
        isMoving = true;
    }
    if (right)
    {
        orientation -= 2.0f;
        isMoving = true;
    }
    position += velocity;
    velocity.zero();

    if (Statistics::get().getMana() < Statistics::get().getManaMax()){
        Statistics::get().changeMana(0.01);
    }

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
        position += collisionSeparate(e);
    e = collisionWith<Spawner>();
    if (e != NULL)
        position += collisionSeparate(e);
    e = collisionWith<Chest>();
    if (e != NULL)
        position += collisionSeparate(e);


    if (isMoving) sprite.resume();
    else sprite.pause();
    Terrain::get().setViewPos(position);
    sprite.update();
}

void Player::gainExp(int _exp)
{
    Statistics::get().changeExp(_exp);
    if (Statistics::get().getExp() >= Statistics::get().getExpNeed())
    {
        Statistics::get().setLvl(1);
        Statistics::get().setExp(1);
        Statistics::get().setExpNeed(5+Statistics::get().getLvl());

        Statistics::get().changeHpMax((Statistics::get().getLvl()*4)+Statistics::get().getLvl());
        Statistics::get().changeManaMax((Statistics::get().getLvl()*2)+Statistics::get().getLvl());

        Statistics::get().setHp(Statistics::get().getHpMax());
        Statistics::get().setMana(Statistics::get().getManaMax());
    }
}


