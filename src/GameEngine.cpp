#include "GameEngine.hpp"

#include "TextureManager.hpp"

GameEngine::GameEngine() : m_textureManager(new TextureManager)
{

}

GameEngine::~GameEngine()
{
    delete m_textureManager;
}

TextureManager& GameEngine::getTextureManager()
{
    return *m_textureManager;
}


