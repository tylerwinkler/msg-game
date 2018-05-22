#ifndef MSG_GAME_GAMEENGINE_HPP
#define MSG_GAME_GAMEENGINE_HPP

namespace sf { class RenderWindow; }

class AnimationSystem;
class CollisionSystem;
class FontManager;
class State;
class StateMachine;
class TextureManager;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

public:
    void run(State* initialState, int ups = 25);

    void quit();

    FontManager& getFontManager();

    StateMachine& getStateMachine();

    TextureManager& getTextureManager();

    sf::RenderWindow& getWindow();

    AnimationSystem& getAnimationSystem();

    CollisionSystem& getCollisionSystem();

private:
    bool m_running;

    sf::RenderWindow* m_window;

    StateMachine* m_stateMachine;

    AnimationSystem* m_animationSystem;

    CollisionSystem* m_collisionSystem;

    FontManager* m_fontManager;

    TextureManager* m_textureManager;
}; // GameEngine

#endif // MSG_GAME_GAMEENGINE_HPP
