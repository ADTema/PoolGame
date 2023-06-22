#include "../headers/Context.h"

#include <utility>
void Context::setWindowsData(Context::WindowData win_data) {
    m_mainWidowData = std::move(win_data);
}
void Context::stopGame() { m_running = false; }
bool Context::isKeyPressed(sf::Keyboard::Key keyCode) {
    return m_pressedKeys[static_cast<int>(keyCode)];
}
void Context::setKeyPressed(sf::Keyboard::Key keyCode) {
    m_pressedKeys[static_cast<int>(keyCode)] = true;
}
void Context::setKeyReleased(sf::Keyboard::Key keyCode){
    m_pressedKeys[static_cast<int>(keyCode)] = false;
}