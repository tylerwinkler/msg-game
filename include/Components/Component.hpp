#ifndef MSG_GAME_COMPONENT_HPP
#define MSG_GAME_COMPONENT_HPP

class Entity;

namespace ComponentType
{
    enum
    {
        AnimationComponent,
        HealthComponent,
        SpriteComponent,
    };
};

class Component
{
public:
    int type;

    virtual bool init(Entity& owner){return true;}

    virtual void update(Entity& owner){}

    virtual void render(Entity& owner){}
}; // Component

#endif // MSG_GAME_COMPONENT_HPP
