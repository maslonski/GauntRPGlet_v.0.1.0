#include <windows.h>
#include <gl/gl.h>

#include "Sprite.h"

Sprite::Sprite(Texture2D *source, int _frameCount, float _fps)
    :texture(source)
    ,frameCount(_frameCount)
    ,rangeStart(0)
    ,rangeEnd(_frameCount-1)
    ,currentFrame(0.f)
    ,state(PAUSED)
    ,fps(_fps)
    ,lastTime( GetTickCount() )
{
}

void Sprite::play(int start, int end)
{
    state = PLAYING;
    currentFrame = rangeStart = start;
    rangeEnd = end != -1 ? end : frameCount - 1;
}

void Sprite::pause()
{
    state = PAUSED;
}

void Sprite::resume()
{
    state = PLAYING;
}

void Sprite::update()
{
    if (state == PLAYING)
    {
        currentFrame += fps*(GetTickCount() - lastTime)/1000.f;
        if (currentFrame > rangeEnd +1)
            currentFrame = rangeStart;
        lastTime = GetTickCount();
    }
}

void Sprite::drawBar(float2 position, float orientation, float scaleX, float scaleY, float posX)
{
    texture->bind();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.f);
    glRotatef(orientation, 0,0,1);
    glScalef(scaleX, scaleY, 1.f);
	glBegin(GL_QUADS);
        glTexCoord2f((int)currentFrame/(float)frameCount,0);
	    glVertex3f(0,-1,0.0);

        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,0);
	    glVertex3f(posX,-1,0.0);

        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,.99f);
	    glVertex3f(posX,1,0.0);

        glTexCoord2f((int)currentFrame/(float)frameCount,.99f);
	    glVertex3f(0,1,0.0);
	glEnd();
	glPopMatrix();
}

void Sprite::draw(float2 position, float orientation, float scaleX, float scaleY)
{
    texture->bind();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.f);
    glRotatef(orientation, 0,0,1);
    glScalef(scaleX, scaleY, 1.f);
	glBegin(GL_QUADS);
        glTexCoord2f((int)currentFrame/(float)frameCount,0);
	    glVertex3f(-1,-1,0.0);

        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,0);
	    glVertex3f(1,-1,0.0);

        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,.99f);
	    glVertex3f(1,1,0.0);

        glTexCoord2f((int)currentFrame/(float)frameCount,.99f);
	    glVertex3f(-1,1,0.0);
	glEnd();
	glPopMatrix();
}

void Sprite::draw(float2 position, float orientation, float scale)
{
    texture->bind();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.f);
    glRotatef(orientation, 0,0,1);
    glScalef(scale, scale, 1.f);
	glBegin(GL_QUADS);
        glTexCoord2f((int)currentFrame/(float)frameCount,0);
	    glVertex3f(-0.5,-0.5,0.0);
        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,0);
	    glVertex3f(0.5,-0.5,0.0);
        glTexCoord2f((.99f+(int)currentFrame)/(float)frameCount,.99f);
	    glVertex3f(0.5,0.5,0.0);
        glTexCoord2f((int)currentFrame/(float)frameCount,.99f);
	    glVertex3f(-0.5,0.5,0.0);
	glEnd();
	glPopMatrix();
}
