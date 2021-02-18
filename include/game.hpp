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
    private:
        enum Command {
            Hit,
            Hold,
            Split,
            Invalid
        };
        void processTurn(Player& player); //TODO
        enum Command processCommand(std::string input); 
        int checkHand(Person person); //Return the total value of a players hand
        int activePlayers();
        void addPlayer(std::string name);
        void removePlayer(); //TDOO
        void showPlayers(); //for debug purposes
        std::vector<Player> players_;
        Dealer dealer_;
};

}

#endif //game_hpp