#ifndef player_hpp
#define player_hpp

#include <vector>
#include "person.hpp"
#include "card.hpp"

namespace blackJack {

class Player : public Person {
    public:
        using Person::Person;
        void hit();
        void stay();
        void doubleBet();
        void split();
    private:
        int totalMoney; 
};
}

#endif //player_hpp