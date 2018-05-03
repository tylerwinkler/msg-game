#ifndef MSG_GAME_GAMEENGINE_HPP
#define MSG_GAME_GAMEENGINE_HPP

class TextureManager;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

public:
    TextureManager& getTextureManager();

private:
    TextureManager* m_textureManager;
}; // GameEngine

#endif // MSG_GAME_GAMEENGINE_HPP
