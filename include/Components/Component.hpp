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
    };
};

class Component
{
public:
    int type;

    bool init(Entity& owner);

private:
    virtual bool onInit(Entity& owner){return true;}

protected:
    Entity* const getOwner();

private:
    Entity* m_owner;
}; // Component

#endif // MSG_GAME_COMPONENT_HPP
