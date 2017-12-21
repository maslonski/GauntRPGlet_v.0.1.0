#include "ComponentManager.h"

using std::cout;
using std::endl;

void ComponentManager::add(Component *c)
{
    components.push_front(c);
}

void ComponentManager::update()
{
    for (list<Component *>::reverse_iterator i = components.rbegin();
        i != components.rend();
        ++i)
        if ( (*i)->active )
            (*i)->update();

    for (list<Component *>::iterator i = components.begin();
        i != components.end();/*NIE MA NIC*/)
        if ((*i) -> deleted)
        {
            delete *i;
            i = components.erase(i);
        }
        else
            ++i;
}

void ComponentManager::draw()
{
    for (list<Component *>::reverse_iterator i = components.rbegin();
        i != components.rend();
        ++i)
        if ( (*i)->visible )
            (*i)->draw();
}

ComponentManager::ComponentManager()
{
    cout<<"ComponentManager::ComponentManager()"<<endl;
}

ComponentManager::~ComponentManager()
{
    cout<<"ComponentManager::~ComponentManager()"<<endl;
    clear();
}

void ComponentManager::clear()
{
    for (list<Component *>::iterator i = components.begin();
        i != components.end(); ++i)
        delete *i;
    components.clear();
}
