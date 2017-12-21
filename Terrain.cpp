#include <windows.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctime>

#include "Terrain.h"
#include "ResourceFactory.h"
#include "Player.h"
#include "Spawner.h"
#include "Chest.h"
#include "Tree.h"
#include "Statistics.h"
#include "Rift.h"
#include "Npc.h"

using std::ios;
using std::fstream;
using std::string;
using std::cout;
using std::endl;



Terrain::Terrain()
    :tile({
          Sprite(ResourceFactory::get().load("dungeon_floor.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_G.bmp")), //5
          Sprite(ResourceFactory::get().load("dungeon_wall_L.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_R.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_D.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_DL.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_GL.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_DP.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_GP.bmp")),
          Sprite(ResourceFactory::get().load("black_1.bmp")),

          Sprite(ResourceFactory::get().load("dungeon_wall_DL2.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_DP2.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_GL2.bmp")),
          Sprite(ResourceFactory::get().load("dungeon_wall_GP2.bmp")),

          Sprite(ResourceFactory::get().load("bridge.bmp")),
          Sprite(ResourceFactory::get().load("dirt.bmp")),
          Sprite(ResourceFactory::get().load("6tex.bmp")),
          Sprite(ResourceFactory::get().load("hill.bmp")),
          Sprite(ResourceFactory::get().load("river.bmp")),

          Sprite(ResourceFactory::get().load("start.bmp")),
          }),
    fname(NULL), sizeX(0), sizeY(0), tiles(NULL)
{
    srand( time( NULL ) );
    cout<<"Terrain::Terrain()"<<endl;
    flag = false;
}

Terrain::~Terrain()
{
    cout<<"Terrain::~Terrain()"<<endl;
}

void Terrain::die(int e)
{
    cout<<"Level '"<<fname<<"' loading error: "<<e<<endl;
    exit(EXIT_FAILURE);
}

void Terrain::create(const char *fname)
{
    if (tiles!=NULL)
        delete[] tiles;
    this->fname = fname;

    fstream ifs(fname, ios::in);
    if (!ifs.is_open())
        die(1);
    ifs>>sizeX;
    ifs>>sizeY;
    if (sizeX<=0 || sizeY<=0)
        die(11);
    tiles = new char[sizeX * sizeY];

    for (int i=sizeY-1; i>=0; --i)
    {
        if (ifs.eof())
            die(12);
        string buf;
        ifs>>buf;
        if ((int)buf.size()!=sizeX)
            die(13);
        strncpy( &tiles[i*sizeX], buf.c_str(), sizeX );
    }

    Player* player =
        new Player(Sprite(ResourceFactory::get().load("Player.bmp"), 15, 5),
                                float2(0,0), 0);


    Texture2D *t=ResourceFactory::get().load("Spawner3.bmp");
    Texture2D *ri=ResourceFactory::get().load("rift.bmp");/////////
    //Texture2D *drzewo=ResourceFactory::get().load("tree2.bmp");/////////
    Texture2D *nonComp=ResourceFactory::get().load("koles2.bmp");/////////

    for (int y=0; y<sizeY; ++y)
        for (int x=0; x<sizeX; ++x)
    {

        switch (tiles[x+y*sizeX])
        {
        case 'P':
            tiles[x+y*sizeX] = 's';
            player->setPosition(float2(x,y));
            ComponentManager::get().add(player);
            break;
        case 'B':
            tiles[x+y*sizeX] = 'f';
            ComponentManager::get().add(
                    new Spawner(Sprite(t), float2(x,y), .0f, player));
            break;
        case 'T':
            tiles[x+y*sizeX] = 'f';
            ComponentManager::get().add(
                    new Tree(Sprite(ResourceFactory::get().load("drz2.bmp"),1,32.f),float2(x,y)));
            break;
        case 'C':
            tiles[x+y*sizeX] = 'f';
            ComponentManager::get().add(
                    new Chest(Sprite(ResourceFactory::get().load("chest_sprite.bmp"),4,24.f),float2(x+0.1f,y),1)
                    );
            break;
        case 'R':
            tiles[x+y*sizeX] = 'g';
            if(Statistics::get().getIleKluczy() < 2)/////////////
            {
                ComponentManager::get().add(
                        new Rift( Sprite(ri, 5, 5.f), float2(x,y), 2.f)
                        );
                       // new Rift(Sprite(ResourceFactory::get().load("rifteusz_0.bmp"),1,32.f),float2(x,y)));
            }
            break;

		case 'N':
			tiles[x+y*sizeX] = 'g';
			ComponentManager::get().add(
					new Npc( Sprite(nonComp, 4, 2.f), float2(x,y), 1.f )
					);
			break;
        }
    }
    ifs.close();
}

void Terrain::draw()
{

    glTranslatef(-viewPos.x, -viewPos.y, 0);
    for (int y = 0; y < sizeY; ++y)
    {
        for (int x = 0; x < sizeX; ++x)
        {
            tile[9].draw(float2(x,y));
            switch ( tiles[x+y*sizeX] )
            {
                case 'f': tile[0].draw(float2(x,y)); break;

                case '1': tile[1].draw(float2(x,y)); break;
                case '2': tile[2].draw(float2(x,y)); break;
                case '3': tile[3].draw(float2(x,y)); break;
                case '4': tile[4].draw(float2(x,y)); break;
                case '5': tile[5].draw(float2(x,y)); break;
                case '6': tile[6].draw(float2(x,y)); break;
                case '7': tile[7].draw(float2(x,y)); break;
                case '8': tile[8].draw(float2(x,y));  break;

                case 'd': tile[9].draw(float2(x,y)); break;

                case '9': tile[10].draw(float2(x,y)); break;
                case 'q': tile[11].draw(float2(x,y)); break;
                case 'w': tile[12].draw(float2(x,y)); break;
                case 'e': tile[13].draw(float2(x,y)); break;

                case 'b': tile[14].draw(float2(x,y)); break;
                //case 'd': tile[1].draw(float2(x,y)); break;
                case 'g': tile[16].draw(float2(x,y)); break;
                case 'h': tile[17].draw(float2(x,y)); break;
                case 'r': tile[18].draw(float2(x,y)); break;

                case 's': tile[19].draw(float2(x,y)); break;
            }
        }
    }
}

void Terrain::setViewPos(float2 _viewPos)
{
    viewPos = _viewPos;
    if (viewPos.x < halfViewSize.x - .5f)
        viewPos.x = halfViewSize.x - .5f;
    if (viewPos.x > sizeX - halfViewSize.x - .5f)
        viewPos.x = sizeX - halfViewSize.x - .5f;
    if (viewPos.y < halfViewSize.y - .5f)
        viewPos.y = halfViewSize.y - .5f;
    if (viewPos.y > sizeY - halfViewSize.y - .5f)
        viewPos.y = sizeY - halfViewSize.y - .5f;
}

char Terrain::getTileType(float2 pos)
{
    int x=pos.x;
    int y=pos.y;

    return tiles[x+y*sizeX];
}

float2 Terrain::collision(char tileType, float2 pos, float radius)
{
    int x1=lroundf(pos.x-.5f);
    int y1=lroundf(pos.y-.5f);
    int x2=x1+1;
    int y2=y1+1;
    float2 r[4];
    if (x1==-1 || y1==-1 || tiles[x1+y1*sizeX] == tileType)
        if  ( (pos-float2(x1, y1)).len() < radius + .4f )
            r[0] = (pos-float2(x1, y1)).normalized() * (radius + .4f - (pos-float2(x1, y1)).len());

    if (x2==sizeX || y1==-1 || tiles[x2+y1*sizeX] == tileType)
        if  ( (pos-float2(x2, y1)).len() < radius + .4f )
            r[1] = (pos-float2(x2, y1)).normalized() * (radius + .4f - (pos-float2(x2, y1)).len());
    if (x1==-1 || y2==sizeY || tiles[x1+y2*sizeX] == tileType)

        if  ( (pos-float2(x1, y2)).len() < radius + .4f )
            r[2] = (pos-float2(x1, y2)).normalized() * (radius + .4f - (pos-float2(x1, y2)).len());
    if (x2==sizeX || y2==sizeY || tiles[x2+y2*sizeX] == tileType)

        if  ( (pos-float2(x2, y2)).len() < radius + .4f )
            r[3] = (pos-float2(x2, y2)).normalized() * (radius + .4f - (pos-float2(x2, y2)).len());

    float maxLen = r[0].len();
    float2 maxVal = r[0];
    for (int i=1; i<4; ++i)
        if (r[i].len() > maxLen)
        {
            maxLen = r[i].len();
            maxVal = r[i];
        }
    return maxVal;
}
