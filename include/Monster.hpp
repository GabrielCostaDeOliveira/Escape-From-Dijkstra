#include <SFML/Graphics.hpp>

class Monster{
    private: 
    sf::RectangleShape monster;
    int moviment_speed;

    public: 

    Monster(int width, int height);
    ~Monster();

    void move(sf::Vector2f player_position);
    sf::RectangleShape get_monster();
    void set_position(int x, int y);

};

