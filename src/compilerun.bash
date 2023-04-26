# Comandos para compilar e rodar o jogo, considerando a SFML baixada no folder anterior.
g++ -c main.cpp -I ../SFML-2.5.1/include/
g++ main.o -o sfml-app -L ../SFML-2.5.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
