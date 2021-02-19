#ifndef person_hpp
#define person_hpp

#include "card.hpp"
#include <vector>
#include <iostream>
#include <memory>

namespace blackJack {
class Person {
    public:
        Person(std::string name) : name_{name}, hand_ (std::make_shared<std::vector<Card>>()) {};
        std::string getName() {return name_;}
        std::shared_ptr<std::vector<Card>> getHand() {return hand_;}
        int sumHand();
        void showHand();
        void stand() { playingStatus_ = false; };
        void bust() { 
            playingStatus_ = false;
            bustedStatus_ = true;
        }
        bool getPlayingStatus() { return playingStatus_; };
        void setPlayingStatus(bool value) { playingStatus_ = value; };
        bool getBustedStatus() { return bustedStatus_; };
        void setBustedStatus(bool value) { bustedStatus_ = value; };
    private:
        std::string name_; 
        std::shared_ptr<std::vector<Card>> hand_;
        bool playingStatus_; //Whether the player is still capable of doing actions (hasn't held)
        bool bustedStatus_; //Whether the player has busted
};
}

#endif //person_hpp