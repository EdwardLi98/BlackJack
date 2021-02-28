#ifndef player_hpp
#define player_hpp

#include <vector>
#include "person.hpp"
#include "card.hpp"
#include "dealer.hpp"

namespace blackJack {

class Player : public Person {
    public:
        Player(std::string name) : Person(name) {
            splitHand_ = std::make_shared<std::vector<Card>>();
        };
        void doubleBet(); //TODO
        std::shared_ptr<std::vector<Card>> getSplitHand() { return splitHand_; };
        void split(); //TODO
        void showSplitHand() const;
        HandStatus getSplitStatus() { return splitStatus_; };
        void setSplitStatus(HandStatus splitStatus) { splitStatus_ = splitStatus; };
    private:
        //int totalMoney; 
        std::shared_ptr<std::vector<Card>> splitHand_;
        HandStatus splitStatus_ = Person::HandStatus::Inactive;
};
}

#endif //player_hpp