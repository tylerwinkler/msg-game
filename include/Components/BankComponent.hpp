#ifndef MSG_GAME_COMPONENTS_BANKCOMPONENT
#define MSG_GAME_COMPONENTS_BANKCOMPONENT

#include <string>
#include <vector>

#include "Components/Component.hpp"

class BankComponent : public Component
{
public:
    std::vector<std::string> items;
}; // BankComponent

#endif // MSG_GAME_COMPONENTS_BANKCOMPONENT
