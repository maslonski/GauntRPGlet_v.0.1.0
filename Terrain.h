#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>

using std::vector;

#include "Sprite.h"

class Terrain
{
    public:
        static Terrain &get(void)
        {
            static Terrain instance;
            return instance;
        }
        void create(const char *);
        void draw();
        void setViewSize(float2 _viewSize) { halfViewSize = _viewSize*.5f; }
        void setViewPos(float2 _viewPos);
        float2 collision(char, float2, float);
        char getTileType(float2);

        const char* getFname() { return fname; }
    protected:
        Sprite tile[20];
        const char *fname;
        int sizeX, sizeY;
        char *tiles;
        float2 halfViewSize, viewPos;

        virtual ~Terrain();
        void die(int);
    private:
        bool flag;

        Terrain();
        Terrain(Terrain const &);
        void operator=(Terrain const &);

        //bool playerLoad:1;
};

#endif // TERRAIN_H
