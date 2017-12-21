#ifndef SPRITE_H
#define SPRITE_H

#include "Texture2D.h"
#include "float2.h"

class Sprite
{
    public:
        Sprite(Texture2D *source, int = 1, float = 24.f);
        ~Sprite() {}

        void update();
        void draw(float2 position, float orientation = 0.f, float scale = 1.f);
        void draw(float2 position, float orientation, float scaleX, float scaleY);
        void drawBar(float2 position, float orientation, float scaleX, float scaleY, float posX);
        void play(int = 0, int = -1);
        void pause();
        void resume();
    protected:
        Texture2D *texture;
        int frameCount, rangeStart, rangeEnd;
        float currentFrame;
        enum { PAUSED, PLAYING } state;
        float fps;
        unsigned int lastTime;
    private:
};

#endif // SPRITE_H
