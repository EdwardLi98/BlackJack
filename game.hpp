#ifndef game_hpp
#define game_hpp 

#include "player.hpp"
#include "dealer.hpp"
#include <unordered_map>
#include <functional>
#include <any>

namespace blackJack {

class Game {
    public:
        Game(Dealer dealer) : dealer_{dealer} {};
        void initialiseGame(); //Generate deck and add players
        void startGame(); //Plays game
        void processTurn(Player& player); //TODO
        int checkHand(Person person); //Return the total value of a players hand
        int activePlayers();
        void addPlayer(std::string name);
        void removePlayer(); //TDOO
        void showPlayers(); //for debug purposes
        void hit(Player& player);
        void hold(Player& player);
    private:
        std::vector<Player> players_;
        Dealer dealer_;
        std::unordered_map<std::string, void(Game::*)(Player&)> commands_ {
            {"hit", &Game::hit},
            {"hold", &Game::hold}
        };  
};

}

#endif //game_hpp