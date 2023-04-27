#include <SFML/Graphics.hpp>
#include "../include/Wall.hpp"

class Monster{
    private: 
    sf::RectangleShape monster;
    int moviment_speed;

    Wall wall;

    public: 

    Monster(int width, int height, Wall wall);
    ~Monster();

    void move(sf::Vector2f player_position);
    sf::RectangleShape get_monster();
    void set_position(int x, int y);

};

