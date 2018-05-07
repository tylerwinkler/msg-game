#ifndef MSG_GAME_TEST_TEST_HPP
#define MSG_GAME_TEST_TEST_HPP

#include <iostream>
#include <string>

namespace Test
{
    void fail();
    void fail(const std::string& message);

    void pass();
    void pass(const std::string& message);
}

#endif // MSG_GAME_TEST_TEST_HPP
