#include "Console.hpp"

#include <string>

#include "imgui.h"
#include "imgui-SFML.h"

void Console::draw()
{
    ImGui::Begin("Console");
    char str0[128] = "";
    if (ImGui::InputText("Command", str0, IM_ARRAYSIZE(str0), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        std::string command(str0);
        if (m_functions.count(command) != 0)
        {
            m_functions.at(command)();
        }
    }
    ImGui::End();
}

bool Console::isOpen()
{
    return m_open;
}

void Console::open()
{
    m_open = true;
}

void Console::close()
{
    m_open = false;
}

void Console::toggle()
{
    m_open = !m_open;
}

void Console::setFunction(std::string str, std::function<void()> func)
{
    m_functions.insert(std::make_pair(str, func));
}
