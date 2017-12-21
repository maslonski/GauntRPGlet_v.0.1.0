#include "SoundFactory.h"

SoundFactory::SoundFactory()
{
    cout<<"SoundFactory::SoundFactory()"<<endl;
}

SoundFactory::~SoundFactory()
{
    cout<<"SoundFactory::~SoundFactory()"<<endl;
    /*for (map<const char *, HSTREAM >::iterator i=sounds.begin();
        i != sounds.end(); ++i)
        delete i->second;*/
}

HSTREAM SoundFactory::load(const char *fname )
{
    HSTREAM t = sounds[fname];
    if (t==NULL)
    {
        t = sounds[fname] = BASS_StreamCreateFile(FALSE, fname, 0, 0, BASS_MP3_SETPOS);
        cout << "SoundsFactory::load(" << fname << ") id: " << t << endl;
        if(t == 0)
        {
            //t = 1;
            //sounds[fname] = 1;
            cout<<fname<<" not found"<<endl;
            exit(0);
        }

    }
    return t;
}

void SoundFactory::turnDownMusic()
{
	for (map<const char *, HSTREAM>::iterator it=sounds.begin(); it!=sounds.end(); ++it) {
//		if (it->first != "mission1.mp3" && it->first != "mission2.mp3" && it->first != "mission3.mp3") {
		if (it->first[0] == 'm') {
			BASS_ChannelSetAttribute(it->second, BASS_ATTRIB_VOL, 0.01f);
		}
	}
}

void SoundFactory::turnUpMusic()
{
	for (map<const char *, HSTREAM>::iterator it=sounds.begin(); it!=sounds.end(); ++it) {
//		if (it->first != "mission1.mp3" && it->first != "mission2.mp3" && it->first != "mission3.mp3") {
		if (it->first[0] == 'm') {
			BASS_ChannelSetAttribute(it->second, BASS_ATTRIB_VOL, 1.f);
		}
	}
}


void SoundFactory::stopMusic()
{
	for (map<const char *, HSTREAM>::iterator it=sounds.begin(); it!=sounds.end(); ++it) {
//		if (it->first != "mission1.mp3" && it->first != "mission2.mp3" && it->first != "mission3.mp3") {
		if (it->first[0] == 'm') {
			BASS_ChannelPause(it->second);
		}
	}
}
