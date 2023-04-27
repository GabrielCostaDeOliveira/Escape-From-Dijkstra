#include <SFML/Graphics.hpp>
#include "../include/Wall.hpp"
#include "../include/Monster.hpp"

int dist(sf::Vector2f a, sf::Vector2f b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}


Monster::Monster(int width, int height, Wall wall){
    this->wall = wall;
    this->monster.setSize(sf::Vector2f(width, height));
    sf::Vector2f monsterPosition(40, 10);
    this->monster.setPosition(monsterPosition); 
    this->monster.setFillColor(sf::Color(255, 0, 0));

    sf::Vector2f monster_velocity;
    this->moviment_speed = width;
}

Monster::~Monster(){}

sf::RectangleShape Monster::get_monster(){
    return this->monster;
}

void Monster::set_position(int x, int y){
    this->monster.setPosition(x, y);
}



void Monster::move(sf::Vector2f player_position){
    sf::Vector2f nextMove(1000000, 1000000);
    sf::Vector2f monsterPosition = this->monster.getPosition();

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            sf::Vector2f tmpNextMove(monsterPosition.x + i, monsterPosition.y + j);
            if (dist(player_position, nextMove) > dist(tmpNextMove, player_position)){
                nextMove = tmpNextMove;
            }

        }
    }

    this->set_position(nextMove.x, nextMove.y);
}

