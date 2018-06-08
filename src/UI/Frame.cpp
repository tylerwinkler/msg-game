#include "UI/Frame.hpp"

Frame::Frame() : m_open(false)
{
}

void Frame::open()
{
    m_open = true;
}

void Frame::close()
{
    m_open = false;
}

bool Frame::isOpen()
{
    return m_open;
}

void Frame::render(sf::RenderTarget& target)
{
    if (m_open)
    {
        onRender(target);
    }
}

void Frame::onRender(sf::RenderTarget& target)
{
}

