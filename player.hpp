#ifndef player_hpp
#define player_hpp

#include <vector>
#include "person.hpp"
#include "card.hpp"
#include "dealer.hpp"

namespace blackJack {

class Player : public Person {
    public:
        using Person::Person;
        void hit(Dealer &dealer); //TODO
        void stay(); //TODO
        void doubleBet(); //TODO
        void split(); //TODO
        bool getPlayingStatus() { return playingStatus_; };
    private:
        //int totalMoney; 
        bool playingStatus_ = true;
};
}

#endif //player_hpp