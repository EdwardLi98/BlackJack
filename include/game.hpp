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

namespace blackJack {

class Game {
    public:
        Game() {
            auto dealer = blackJack::Dealer("Dealer"); 
            dealer_ = dealer;
        }
        void initialiseGame(); //Generate deck and add players
        void runGame(); //Plays game
    private:
        enum SystemCommand {
            Add,
            Remove,
            Play,
            End,
            InvalidS
        };
        enum PlayerCommand {
            Hit,
            Hold,
            Split,
            InvalidP
        };
        void setupGame();
        enum SystemCommand processSystemCommand(std::string input);
        void executeSystemCommand(std::string input);
        enum PlayerCommand processPlayerCommand(std::string input); 
        void processTurn(Player& player); //TODO
        void checkHand(Person& person); //Return the total value of a players hand
        int activePlayers(); //Return the total number of players still able to process actions (those who haven't folded or busted)
        int standingPlayers(); //Return the total number of players that are standing
        void addPlayer(std::string name);
        void removePlayer(); //TDOO
        void showPlayers(); //for debug purposes
        void setActiveGame(bool active) { activeGame_ = active; };
        std::vector<Player> players_;
        Dealer dealer_;
        bool activeGame_ = false; // True if a round is in progress and false if it has ended
};

}

#endif //game_hpp