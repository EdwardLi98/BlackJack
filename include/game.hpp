#ifndef game_hpp
#define game_hpp 

#define DEAL_LIMIT 16
#define BLACKJACK 21

#include "person.hpp"
#include "player.hpp"
#include "dealer.hpp"
#include <unordered_map>
#include <functional>
#include <range/v3/algorithm/for_each.hpp>
#include <any>

namespace blackJack {

class Game {
    public:
        Game(Dealer dealer) : dealer_{dealer} {};
        void initialiseGame(); //Generate deck and add players
        void runGame(); //Plays game
        void setupGame();
    private:
        enum Command {
            Hit,
            Hold,
            Split,
            Invalid
        };
        void processTurn(Player& player); //TODO
        enum Command processCommand(std::string input); 
        void checkHand(Person& person); //Return the total value of a players hand
        int activePlayers(); //Return the total number of players still able to process actions (those who haven't folded or busted)
        int standingPlayers(); //Return the total number of players that are standing
        void addPlayer(std::string name);
        void removePlayer(); //TDOO
        void showPlayers(); //for debug purposes
        std::vector<Player> players_;
        Dealer dealer_;
};

}

#endif //game_hpp