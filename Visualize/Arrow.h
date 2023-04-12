#pragma once
#include "Style.h"

class Arrow {
public:
    Arrow();

    Arrow(sf::Vector2f pos1, sf::Vector2f pos2, int k) : Arrow() {
        create(pos1, pos2, k);
    }

    template<class Obj1, class Obj2>
    void create(Obj1 o1, Obj2 o2, int k) {
        sf::Vector2f pos1 = o1.getPosition() + sf::Vector2f(o1.getSize().x - 6.f, o1.getSize().y / 2);
        sf::Vector2f pos2 = o2.getPosition() + sf::Vector2f(10.f, o2.getSize().y / 2);
        create(pos1, pos2, k);
    }
  
    void create(sf::Vector2f pos1, sf::Vector2f pos2, int k);

    void draw(sf::RenderWindow& window); 

    sf::Sprite s[3];
    int id = 0;
    bool inited = 0;
};
