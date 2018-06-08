#ifndef MSG_GAME_STATE_HPP
#define MSG_GAME_STATE_HPP

#include "SFML/Window/Event.hpp"

class State
{
public:
    virtual ~State(){}

public:
    virtual bool init(){return true;}

    virtual void onResize(int width, int height){}

    virtual void onMouseButton(int x, int y, int button, bool pressed){}

    virtual void onMouseWheelMoved(float delta){}

    virtual void onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed){}

    virtual void update(){}

    virtual void render(float interpolation){}

    virtual void cleanup(){}

    virtual void imguiUpdate(){}
}; // State

#endif // MSG_GAME_STATE_HPP
