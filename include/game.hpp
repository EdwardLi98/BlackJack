#ifndef game_hpp
#define game_hpp

#define DEAL_LIMIT 16
#define BLACKJACK 21
#define PAIR 2
#define PLAYER_LIMIT 7

#include "person.hpp"
#include "player.hpp"
#include "dealer.hpp"
#include <cstring>
#include <functional>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/algorithm/adjacent_find.hpp>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <stdlib.h>
#include <unordered_map>

namespace blackJack {

class Game {
    public:
        Game() {
            auto dealer = blackJack::Dealer("Dealer");
            dealer_ = dealer;
        }
        void initialiseGame(); //Generate deck and add players
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
        void runGame(); //Plays game
        void setupGame(); //Resets the game state 
        enum SystemCommand processSystemCommand(const std::string input) const; //Reads in input from user relating to the game
        void executeSystemCommand(const std::string input); //Process the input from user relating to the game
        enum PlayerCommand processPlayerCommand(const std::string input) const; //Reads in input from user relating to a specific turn
        void processTurn(Player &player); //Proccess the input from user relating to a specific turn
        void processSplitTurn(Player &player); //Process the input from a user relating to a specific turn for their split hand
        int sumHand(std::shared_ptr<std::vector<Card>> hand); //Returns the total value of a players hand
        void checkHand(std::shared_ptr<std::vector<Card>> hand, Person& person);   //Return the total value of a players hand
        bool checkSplit(Person &person); //Check if the players hand is able to be split
        void checkWin(Player player, Dealer dealer); //Compare player main hand and dealer to see who won
        void checkSplitWin(Player player, Dealer dealer); //Compare player split hand and dealer to see who won
        int standingPlayers() const;  //Return the total number of players that are standing
        void addPlayer(const std::string name); //Adds a player to the game
        void removePlayer(const std::string name); //Removes a player from the game
        void showPlayers() const;  //for debug purposes
        std::vector<Player> players_;
        Dealer dealer_;
};
}

#endif //game_hpp