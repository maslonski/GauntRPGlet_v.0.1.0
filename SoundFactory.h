#ifndef SOUNDFACTORY_H
#define SOUNDFACTORY_H

#include <iostream>

#include <map>

using std::map;
using std::cout;
using std::endl;


#include "Texture2D.h"
#include "bass.h"

class SoundFactory
{
public:
    static SoundFactory &get()
    {
        static SoundFactory instance;
        return instance;
    }
    virtual ~SoundFactory();
    HSTREAM load(const char *);

    virtual void turnDownMusic();
    virtual void turnUpMusic();
    virtual void stopMusic();
protected:
    map<const char *, HSTREAM > sounds;
private:
    SoundFactory();
    SoundFactory(SoundFactory const &);
    void operator=(SoundFactory const &);
};

#endif // SOUNDFACTORY_H
