// Incluir os arquivos da sfml, considerando baixado no mesmo folder, e usando o compilerun.bash.
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../include/Player.hpp"
#include <SFML/Audio.hpp>
#include "../include/Wall.hpp"
#include "../include/Monster.hpp"
#include "../include/Header.hpp"
#include <string>

const float RATE_MONSTER_MOVE = 10000.0;
const float MAX_DISTANCE_TO_PLAYER = 70;

int distance(sf::Vector2f a, sf::Vector2f b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int main(){
    
    // Configurações iniciais da window.
    const unsigned short int WINDOW_HEIGHT = 360;
    const unsigned short int WINDOW_WIDTH = 840;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Escape From Dijsktra !");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    // Visão da câmera.
    sf::View view;
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    view.setCenter(window.getSize().x/2.f, window.getSize().y/2.f);
    view.zoom(10000);

    // Grid, 'menor unidade'
    const float GRID_SIZE = 10.f;

    sf::Vector2f player_velocity;

    // Clock.
    sf::Clock dt_clock;

    // Walls colision.
    sf::FloatRect nextpos;

    // Parede desenhada
    Wall wall(WINDOW_HEIGHT, WINDOW_WIDTH);
    wall.draw();

    // Jagador
    sf::Vector2f initial_position(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    sf::Vector2f final_position(300, 240);
    Player player(initial_position, GRID_SIZE,  WINDOW_WIDTH,  WINDOW_HEIGHT, wall);

    // Musica.
    sf::Music main_theme;
    main_theme.openFromFile("./media/main_theme.wav"); // deve ser comparado com a localização do make
    main_theme.setVolume(50);
    main_theme.play();

    // Monstro
    Monster monster(GRID_SIZE, GRID_SIZE, wall);
    sf::Clock dt_monster;

    Header header;
    
    while (window.isOpen()){
        sf::Event event;
        
        // colisão do player monstro
        if(distance(player.body.getPosition(), monster.get_monster().getPosition()) <= player.body.getSize().x){ 
            player.body.setPosition(initial_position);
            header.text.setString(std::to_string(++player.deaths) + " mortes");
        }


        // colisão com a saída.
        if(distance(player.body.getPosition(), final_position) <= player.body.getSize().x){ break; }

        while(window.pollEvent(event)){
            
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                break;

                case (sf::Event::KeyPressed):// | sf::Event::KeyReleased ):
                    player.move(event);
                break;

                default:
                break;
            }
        }

        if (dt_monster.getElapsedTime().asMilliseconds() > RATE_MONSTER_MOVE) {
            monster.move_bfs(player.body.getPosition());
            dt_monster.restart();
        }

        // Renderizar tudo. 
        window.clear();
        window.draw(header.text);
        window.draw(player.body);
        if(distance(player.body.getPosition(), monster.get_monster().getPosition()) <= MAX_DISTANCE_TO_PLAYER)
            window.draw(monster.get_monster());

        for (auto &w : wall.get_block_list())
            if(distance(player.body.getPosition(), w.getPosition()) <= MAX_DISTANCE_TO_PLAYER)
                window.draw(w);
        
        window.display();
    }


    return 0;
}


