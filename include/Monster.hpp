#include <SFML/Graphics.hpp>
#include "../include/Wall.hpp"
#include <set>

class Monster{
    private: 
    sf::RectangleShape monster;
    int moviment_speed;

    Wall wall;

    public: 


    std::set<std::pair<int, int>> list_position_can_move;


    Monster(int width, int height, Wall wall);
    ~Monster();

    void move(sf::Vector2f player_position);
    sf::RectangleShape get_monster();
    void set_position(int x, int y);

    public:
    
    sf::RectangleShape next_position();

};

