#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

#include <time.h>
#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

#include "Sprite.h"
#include "ResourceFactory.h"
#include "float2.h"
#include "Humans.h"
#include "Monster.h"
#include "ComponentManager.h"
#include "Player.h"
#include "Ghost.h"
#include "Spider.h"
#include "Terrain.h"
#include "Spawner.h"
#include "Tree.h"
#include "SpriteText.h"
#include "Statistics.h"
#include "GUI.h"
#include "Monster.h"
#include "Objects.h"
#include "Items.h"
#include "Key.h"
#include "Npc.h"
#include "bass.h"
#include "SoundFactory.h"

Sprite *gameOver, *youWon;
SpriteText *hpText, *goldText, *lvlText, *expText, *expNeedText, *potionText, *manaText, *manaPotionText, *arrowsText, *missionText;
GUI *GUIdraw, *hpBar, *manaBar, *potionGUI, *goldGUI, *missionTextArea;

bool spawnKlucza = false;/////////

// globalne
int fps = 100;
float nextCzas = 0;

enum GameState{
    PLAY, GAMEOVER, YOUWON
} gameState = PLAY;

unsigned int pauseTime = -1;

void renderScene(void) {

    // do renderScene
	clock_t t;
	t = clock();
	float czas = (float)t / 1000;

	while (czas < nextCzas) {
		usleep(10);
		t = clock();
		czas = (float)t / 1000;
	}
	float limit_fps = 1.0 / ((float)fps + 0.5);
	nextCzas = czas + limit_fps;

    glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-1);
	glPushMatrix();
        Terrain::get().draw();
        ComponentManager::get().draw();
    glPopMatrix();




    lvlText->draw(float2(-7.3f, 6.7f), 0.f, 0.3f);////////////////
    //expText->draw(float2(-3.f, -5.5f), 0.f, 0.5f);////////////////
    //expNeedText->draw(float2(-2.f, -5.5f), 0.f, 0.5f);////////////////
    //potionText->draw(float2(-10.f, -4.5f), 0.f, 0.5f);////////////////


    ComponentManager::get().find<Player>();
    Player *p = ComponentManager::get().next<Player>();

    goldGUI->draw(float2(8.f, 7.3), 1.5f, 0.35f);
        goldText->draw(float2(7.8f, 7.2f), 0.f, 0.35f);////////////////
    GUIdraw->draw(float2(-7.2f, 6.7f),3, 1);
        hpBar->drawBar(float2(-7.2f, 7.47f), 1.f, 0.12f, ((2.7f * Statistics::get().getHp())/Statistics::get().getHpMax()));
            hpText->draw(float2(-6.f, 7.45f), 0.f, 0.2f);

        manaBar->drawBar(float2(-7.2f, 7.15f), 1.f, 0.12f, ((2.7f * Statistics::get().getMana())/Statistics::get().getManaMax()));
            manaText->draw(float2(-6.0f, 7.13f), 0.f, 0.2f);////////////////

        potionGUI->draw(float2(-9.8f, 4.2f),0.5, 2);
            potionText->draw(float2(-9.55f, 4.5f), 0.f, 0.15f);////////////////
            manaPotionText->draw(float2(-9.55f, 3.47f), 0.f, 0.15f);////////////////
            arrowsText->draw(float2(-9.58f, 2.45f), 0.f, 0.15f);////////////////
    switch (gameState)
    {
    case GAMEOVER:
        gameOver -> draw(float2(0,0), 0.f, 16.f);
        break;
    case YOUWON:
        youWon -> draw(float2(0,0), 0.f, 16.f);
        break;
    case PLAY:
        break;
    }


	glutSwapBuffers();
}

void resize(int wid, int hei)
{
    if (hei==0) hei=1;
    glViewport(0, 0, wid, hei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float scale = 8.f;
    glOrtho(-scale*(float)wid/(float)hei*.98f,
            scale*(float)wid/(float)hei*.98f,
            -scale,
            scale,
            .1f,
            10.f
            );
    glMatrixMode(GL_MODELVIEW);
}

void keyb(unsigned char k, int, int)
{
    switch (k)
    {
    case 27:
        exit(EXIT_SUCCESS);
    case ' ':
        break;
    }
    ComponentManager::get().find<Player>();
    Player *p = ComponentManager::get().next<Player>();
    if (p != NULL)
        p->keyb(k, true);
}

void keybUp(unsigned char k, int, int)
{
    ComponentManager::get().find<Player>();
    Player *p = ComponentManager::get().next<Player>();
    if (p != NULL)
        p->keyb(k, false);
}

void doAtExit()
{
    cout<<"Game Terminated"<<endl;
}

void idle()
{
	//BASS_ChannelPlay(SoundFactory::get().load("mClearside-SisteViator.ogg") , FALSE);////////

    ComponentManager::get().find<Player>();
    Player *player = ComponentManager::get().next<Player>();

    switch (gameState){
    case PLAY:
        ComponentManager::get().update();

        if (player != NULL){
            hpText -> setText("", Statistics::get().getHp());
            goldText -> setText("", Statistics::get().getGold());/////////
            lvlText -> setText("LVL: ", Statistics::get().getLvl());
            expText -> setText(" ", Statistics::get().getExp());
            expNeedText -> setText(" / ", Statistics::get().getExpNeed());
            potionText -> setText("", Statistics::get().getPotion());
            manaPotionText -> setText("", Statistics::get().getManaPotion());
            arrowsText -> setText("", Statistics::get().getArrows());
            manaText -> setText("", Statistics::get().getMana());
        }


        if (ComponentManager::get().count<Spawner>() == 0 && ComponentManager::get().count<Monster>() == 0)/////////////////////////
        {
            /////////////////////////////////////////////////////////////
            if(!spawnKlucza)
            {
                ComponentManager::get().add(
                    new Key(
                        Sprite(ResourceFactory::get().load("rift.bmp"), 5, 5.f),
                        float2(15.f, 14.f),
                        0.f
                        )
                    );
                spawnKlucza = true;/////////
            }

            switch(Statistics::get().getIleKluczy()) // dropienie klucza
            {
            case 1:
                if(player->getReload())
                {
                    spawnKlucza = false;
                    ComponentManager::get().clear();
                    Terrain::get().create("d2.txt");
                }

            break;
            case 2:
                if(player->getReload())
                {
                    spawnKlucza = false;
                    ComponentManager::get().clear();
                    Terrain::get().create("d3.txt");
                }

            break;

            case 3:

                spawnKlucza = false;
                gameState = YOUWON;
                Statistics::get().reset();
                break;
            }
        }
        else{
            ComponentManager::get().find<Player>();
            Player *p = ComponentManager::get().next<Player>();
            if(p != NULL && !p->isActive()){
                gameState = GAMEOVER;
                pauseTime = GetTickCount() + 2000;
            }
//            if (p != NULL){
//            hpText -> setText("", Statistics::get().getHp());
//            goldText -> setText("", Statistics::get().getGold());/////////
//            lvlText -> setText("LVL: ", Statistics::get().getLvl());
//            expText -> setText(" ", Statistics::get().getExp());
//            expNeedText -> setText(" / ", Statistics::get().getExpNeed());
//            potionText -> setText("", Statistics::get().getPotion());
//            manaPotionText -> setText("", Statistics::get().getManaPotion());
//            arrowsText -> setText("", Statistics::get().getArrows());
//            manaText -> setText("", Statistics::get().getMana());
//
//            }


        }

        break;
    case GAMEOVER:
        if (GetTickCount() > pauseTime){
            ComponentManager::get().clear();
            Statistics::get().reset();
            Terrain::get().create("d1.txt");

            gameState =PLAY;
            pauseTime = -1;
        }
        break;
    case YOUWON:
        if (GetTickCount() > pauseTime){
            ComponentManager::get().clear();
            Statistics::get().reset();

            Terrain::get().create("d1.txt");
            gameState =PLAY;
            pauseTime = -1;
        }
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    cout<<"Initialization"<<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(64,64);
	glutInitWindowSize(800,600);
	glutCreateWindow("GLUT w CodeBlocks");
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyb);
	glutKeyboardUpFunc(keybUp);
	glutReshapeFunc(resize);
	glutIdleFunc(idle);

    BASS_Init(-1, 44100, 0, 0, NULL);///////////

    Terrain::get().setViewSize(float2(21, 16));
    Terrain::get().create("d1.txt");

    gameOver = new Sprite(ResourceFactory::get().load("gameover.bmp"));
    youWon = new Sprite(ResourceFactory::get().load("youwon.bmp"));


    hpText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
	goldText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
	lvlText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
	expText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    expNeedText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    potionText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    manaPotionText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    manaText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    arrowsText = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));

    goldGUI = new GUI(Sprite(ResourceFactory::get().load("zlotoGUI.bmp"),1));
    GUIdraw = new GUI(Sprite(ResourceFactory::get().load("GUI1.bmp"),1));
    hpBar = new GUI(Sprite(ResourceFactory::get().load("hp_bar.bmp"),1));
    manaBar = new GUI(Sprite(ResourceFactory::get().load("mana_bar.bmp"),1));
    potionGUI = new GUI(Sprite(ResourceFactory::get().load("GUI2.bmp"),1));


    hpText -> setColor(1,1,1);
    goldText -> setColor(1,1,0);
    lvlText -> setColor(1,1,1);
    expText -> setColor(1,1,1);
    expNeedText -> setColor(1,1,1);
    potionText -> setColor(1,1,1);
    manaText -> setColor(1,1,1);
    manaPotionText -> setColor(1,1,1);
    arrowsText -> setColor(1,1,1);

	glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    atexit(doAtExit);

    cout<<"Game Started"<<endl;
	glutMainLoop();
}
