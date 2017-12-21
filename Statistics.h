#ifndef STATISTICS_H
#define STATISTICS_H


class Statistics
{
    public:
        static Statistics &get(void)
        {
            static Statistics instance;
            return instance;
        }

        virtual ~Statistics();

        virtual int getGold() { return gold;}
        virtual int getLvl() { return lvl;}
        virtual int getExp() { return exp;}
        virtual int getExpNeed() { return expNeed;}
        virtual int getPotion() { return hpPotions; }
        virtual int getMana() { return (int)mana; }
        virtual int getManaPotion() { return manaPotions; }
        virtual int getArrows() { return arrows; }
        virtual int getHpMax() {return hpMax; }
        virtual int getManaMax() {return manaMax; }
        virtual int getHp() {return (int)hp; }

        virtual void setGold(int _gold) { gold += _gold;}
        virtual void setLvl(int _lvl) { lvl += _lvl;}
        virtual void setExp(int _exp) { exp = _exp;}
        virtual void setExpNeed(int _expNeed) { expNeed += _expNeed;}
        virtual void setPotion(int _hpPotions) { hpPotions += _hpPotions;}
        virtual void setManaPotion(int _manaPotions) { manaPotions += _manaPotions;}
        virtual void setArrows(int _arrows) { arrows = _arrows;}
        virtual void setHpMax(int _hpMax) {hpMax = _hpMax;}
        virtual void setManaMax(int _manaMax) {manaMax = _manaMax;}
        virtual void setHp(float _hp) {hp = _hp;}
        virtual void setMana(float _mana) { mana = _mana;}

        virtual int getIleDungeons(){ return ileDungeons; }
        virtual int getIleKluczy() { return ileKluczy; }
        virtual void setIleDungeons(int ileD) { ileDungeons = ileD; }///////////////////
        virtual void setIleKluczy(int ileK) { ileKluczy += ileK; }/////////////////

        virtual void changeArrows(int _arrows) { arrows += _arrows;}
        virtual void changeHpMax(int _hpMax) {hpMax += _hpMax;}
        virtual void changeManaMax(int _manaMax) {manaMax += _manaMax;}
        virtual void changeHp(float _hp) {hp+= _hp;}
        virtual void changeMana(float _mana) { mana += _mana;}
        virtual void changeExp(int _exp) { exp += _exp;}

        void reset();


    protected:
        int gold, exp, expNeed, lvl, hpPotions, manaPotions, arrows, hpMax, manaMax, ileDungeons, ileKluczy;
        float mana , hp;
    private:
        Statistics();
        Statistics(const Statistics  &);
        void operator=(const Statistics  &);


};

#endif // STATISTICS_H
