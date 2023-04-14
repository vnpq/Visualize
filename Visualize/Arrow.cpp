#include "Arrow.h"

Arrow::Arrow() {
    
}
void Arrow::create(sf::Vector2f pos1, sf::Vector2f pos2, int d) {
    s.setTexture(Style::t);

    // Calculate the length and angle of the arrow
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx) * 180 / M_PI;

    // Set the position, origin, rotation, and scale of the arrow sprite
    s.setPosition(pos1);
    s.setOrigin(0, s.getLocalBounds().height / 2.0);
    s.setRotation(angle);
    s.setScale((length - d) / s.getLocalBounds().width, 0.2);
    
    inited = 1;
}

void Arrow::draw(sf::RenderWindow& window) {
    if (!inited) {
        return;
    }
    window.draw(s);
}
