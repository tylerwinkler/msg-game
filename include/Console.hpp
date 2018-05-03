#ifndef MSG_GAME_CONSOLE_HPP
#define MSG_GAME_CONSOLE_HPP

#include <functional>
#include <map>
#include <string>

class Console
{
public:
    void draw();

    bool isOpen();

    void open();

    void close();

    void toggle();

    void setFunction(std::string str, std::function<void()> func);

private:
    bool m_open;

    std::map<std::string, std::function<void()>> m_functions;
}; // Console

#endif // MSG_GAME_CONSOLE_HPP
