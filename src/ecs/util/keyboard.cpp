#include <ecs/util/keyboard.hpp>
#include <iostream>

bool Keyboard_t::isKeyPressed(KeySym s) noexcept{
    if(auto it = getIterator(s)){
        return (*it)->second;
    }
    return false;
}

Keyboard_t::OptIter Keyboard_t::getIterator(KeySym s) noexcept {
    auto it = m_pressedKeys.find(s);
    if( it != m_pressedKeys.end()){
        return it;
    }
    return {};
}

