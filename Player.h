#ifndef PLAYER_H
#define PLAYER_H

#include "Humans.h"

class Player : public Humans
{
    public:
        Player(const Sprite &, float2, float);
        virtual ~Player();

        void keyb(unsigned char, bool);

        virtual void update();

        void gainExp(int);    ///////////////////////////

		float tempOrientation;///////
		friend class Npc;/////////////
        bool getReload() { return reload; }////////////
        void setReload(bool _reload) { reload = _reload; }///////////
		bool sprawdzCzyRift() { return czyRift; }/////////////
		void ustawRift(bool col) { czyRift = col; }////////////
		void setUkonczone(bool fi) { ukonczone = fi; }
		bool getUkonczone() { return ukonczone; }
    protected:
        enum {BOW, SWORD, MAGIC} PlayerState=BOW;
        void usePotion();
        void useManaPotion();

        bool forward:1, backward:1, left:1, right:1, firePressed:1, weaponChange:1, potionPressed:1, actionPressed:1, interact:1, reload:1 ,czyRift:1, interactionBegin:1, ukonczone:1;/////////;

    private:
};

#endif // PLAYER_H
