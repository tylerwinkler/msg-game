#ifndef MSG_GAME_COMPONENT_HPP
#define MSG_GAME_COMPONENT_HPP

class Entity;

namespace ComponentType
{
    enum
    {
        AnimationComponent,
        CollisionComponent,
        HealthComponent,
        SpriteComponent,
        LootComponent,
        InteractionComponent,
    };
};

class Component
{
public:
    Component(){m_owner = nullptr;}

public:
    int type;

    bool init(Entity* owner);

    virtual void receive(int x, int y){}

private:
    virtual bool onInit(Entity* owner){return true;}

public:
    int getOwnerID();

private:
    int m_owner;
}; // Component

#endif // MSG_GAME_COMPONENT_HPP
