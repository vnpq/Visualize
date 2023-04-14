#pragma once
#include "Style.h"

class Arrow {
public:
    Arrow();

    Arrow(sf::Vector2f pos1, sf::Vector2f pos2) : Arrow() {
        create(pos1, pos2);
    }

    template<class Obj1, class Obj2>
    void create(Obj1 o1, Obj2 o2) {

        float d = o2.getSize().x / 2;
        sf::Vector2f pos1 = o1.getPosition() + sf::Vector2f(d, d);
        sf::Vector2f pos2 = o2.getPosition() + sf::Vector2f(d, d);
      
        create(pos1, pos2, d);
    }
  
    void create(sf::Vector2f pos1, sf::Vector2f pos2, int d = 0);

    void draw(sf::RenderWindow& window); 

    sf::Sprite s;
    int id = 0;
    bool inited = 0;
};
