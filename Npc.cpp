#include "npc.h"

#include "Player.h"
#include "Statistics.h"

#include <iostream>

Npc::Npc(const Sprite &_sprite, float2 _position,
               float _orientation)
    :Humans(_sprite, _position, _orientation)
    ,ostDialog(false)
{
	sprite.play(0, 4);
}

Npc::~Npc(){}

void Npc::draw()
{
    sprite.draw(position, orientation*180, 0.8f);
}

void Npc::update()
{
	Player *player = collisionWith<Player>();

		if (player != NULL && player->interact )
		{
			if(Statistics::get().getIleKluczy() > 1)
			{
				// tekst npcta
				// danie klucz
				// otwarcie skrzyni (lub portalu) i koniec gry
				player->setUkonczone(true);
				ostDialog = true;
			}
			else
			{
				std::cout << "zbierz klucze" << std::endl;
				// tekst npcta
			}
			player->interact = false;
		}

	sprite.update();
}
