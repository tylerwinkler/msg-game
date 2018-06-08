#ifndef MSG_GAME_COMPONENT_HPP
#define MSG_GAME_COMPONENT_HPP

namespace ComponentType
{
    enum
    {
        AnimationComponent,
        CollisionComponent,
        DialogComponent,
        HealthComponent,
        SpriteComponent,
        LootComponent,
        InteractionComponent,
    };
};

class Component
{
public:
    Component(){m_ownerID = -1;}

public:
    int type;

    bool init(int ownerID);

    virtual void receive(int x, int y){}

private:
    virtual bool onInit(int ID){return true;}

public:
    int getOwnerID();

private:
    int m_ownerID;
}; // Component

#endif // MSG_GAME_COMPONENT_HPP
