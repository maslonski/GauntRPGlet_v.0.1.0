#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
    public:
        Component()
            :deleted(false)
            ,active(true)
            ,visible(true)
            {
            }
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual ~Component() {}

        virtual void kill() {deleted = true; }
        virtual bool isActive() { return active; }
    protected:
        bool deleted:1, active:1, visible:1;
    private:
        friend class ComponentManager;
};

#endif // COMPONENT_H
