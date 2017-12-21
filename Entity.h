#ifndef ENTITY_H
#define ENTITY_H

#include "float2.h"
#include "Sprite.h"
#include "ComponentManager.h"

class Entity : public Component
{
    public:
        Entity(const Sprite &, float2, float);
        virtual ~Entity();

        virtual void update();
        virtual void draw();
        virtual void action();

        float2 getPosition() const { return position; }
        float2 getOrientation() const { return orientation; } //////////////

        void setPosition(const float2 &p) { position = p; }

        template <class EntityType> EntityType* collisionWith(Entity* = NULL);
        template <class EntityType> EntityType* collisionMelle(Entity* = NULL);/////
        float2 collisionSeparate(Entity *e);

        virtual void setHp(int _hp) { hp += _hp; }
        virtual int getHp() { return hp; }

    protected:
        Sprite sprite;
        float2 position;
        float orientation;
        float2 velocity;
        float radius;
        int hp;
        float radiusMelle;
        //int gold;

    private:
};

template <class EntityType> EntityType* Entity::collisionWith(Entity *except)
{
    ComponentManager::get().find<EntityType>();
    EntityType *r, *t = NULL;
    float maxLen = 0.f;
    while ((r=ComponentManager::get().next<EntityType>()) != NULL)
    {
        float len = r->radius + radius - (r->position - position).len();
        if (len>0 && except != r && len>maxLen)
        {
            maxLen = len;
            t = r;
        }
    }
    return t;
}

/////////////
template <class EntityType> EntityType* Entity::collisionMelle(Entity *except)
{
    ComponentManager::get().find<EntityType>();
    EntityType *r, *t = NULL;
    float maxLen = 0.f;
    while ((r=ComponentManager::get().next<EntityType>()) != NULL)
    {
        float len = r->radiusMelle + radiusMelle - (r->position - position).len();
        if (len>0 && except != r && len>maxLen)
        {
            maxLen = len;
            t = r;
        }
    }
    return t;
}
//////////////
#endif // ENTITY_H
