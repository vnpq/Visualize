#include "Arrow.h"

Arrow::Arrow() {
    
}
void Arrow::create(sf::Vector2f pos1, sf::Vector2f pos2, int d) {   
    if (abs(pos1.x - pos2.x) <= 0.001 && abs(pos1.y - pos2.y) <= 0.001) {
        s = sf::Sprite();
        if (Style::dark) s.setTexture(Style::a2);
        else s.setTexture(Style::t2);
        
        s.setPosition(pos1 - sf::Vector2f{10, 10});
        s.setRotation(0);
        s.setScale(2 * 37 / s.getLocalBounds().width, 2 * 37 / s.getLocalBounds().height);

        inited = 1;
        return;
    }
    
    s = sf::Sprite();
    if (Style::dark) s.setTexture(Style::a);
    else s.setTexture(Style::t);    

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
