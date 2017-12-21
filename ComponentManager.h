#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <iostream>
#include <list>

using std::list;

#include "Component.h"

class ComponentManager
{
    public:
        static ComponentManager &get()
        {
            static ComponentManager instance;
            return instance;
        }
        void add(Component *);
        void update();
        void draw();
        void clear();
        ~ComponentManager();

        template <class ComponentType> void find();
        template <class ComponentType> ComponentType *next();
        template <class ComponentType> int count();
    protected:
        list<Component *> components;
        list<Component *>::iterator foundIter;
    private:
        ComponentManager();
        ComponentManager(const ComponentManager &);
        void operator=(const ComponentManager &);
};

template <class ComponentType> void ComponentManager::find()
{
    foundIter = components.begin();
}

template <class ComponentType> ComponentType *ComponentManager::next()
{
    while ( foundIter != components.end() )
    {
        ComponentType *c = dynamic_cast<ComponentType*>(*foundIter);
        ++foundIter;
        if (c != NULL)
            return c;
    }
    return NULL;
}

template <class ComponentType> int ComponentManager::count()
{
    int count = 0;
    for (list<Component*>::iterator i = components.begin();
        i != components.end(); ++i)
        if (dynamic_cast<ComponentType*>(*i) != NULL)
            ++count;
    return count;
}

#endif // COMPONENTMANAGER_H
