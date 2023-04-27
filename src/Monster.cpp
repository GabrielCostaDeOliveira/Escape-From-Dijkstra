#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <utility>
#include "../include/Wall.hpp"
#include "../include/Monster.hpp"

int dist(sf::Vector2f a, sf::Vector2f b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}


Monster::Monster(int width, int height, Wall wall){
    this->wall = wall;
    this->list_position_can_move = wall.get_list_position_can_move();

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

void Monster::move_bfs(sf::Vector2f player_position) {

    const std::vector<std::pair<int, int>> moves {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    std::map<std::pair<int, int>, std::pair<int, int>> father;

    std::pair<int, int> current_position_of_moster(static_cast<int>(this->monster.getPosition().x), static_cast<int>(this->monster.getPosition().y));

    std::queue<std::pair<int, int>> q;
    q.push(current_position_of_moster);

    std::set<std::pair<int, int>> visited;
    visited.insert(current_position_of_moster);

    while (not q.empty()) {

        auto v = q.front();
        q.pop();

        for (auto m : moves) {
            std::pair<int, int> u;
            u.first = m.first + v.first;
            u.second = m.second + v.second;

            if (!visited.count(u) && list_position_can_move.count(u)) {
                father[u] = v;
                q.push(u);
                visited.insert(u);
            }
        }
    }

    std::pair<int, int> next_position = std::make_pair(static_cast<int>(player_position.x), static_cast<int>(player_position.y));

    while (father[next_position] != current_position_of_moster) {
        next_position = father[next_position];
    }

    this->set_position(static_cast<float>(next_position.first), static_cast<float>(next_position.second));
}
