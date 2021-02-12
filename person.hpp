#ifndef person_hpp
#define person_hpp

#include "card.hpp"
#include <vector>
#include <iostream>
#include <memory>

namespace blackJack {
class Person {
    public:
        Person() : name_{"default"}, hand_ (std::make_unique<std::vector<Card>>()){};
        Person(std::string name) : name_{name}, hand_ (std::make_unique<std::vector<Card>>()) {};
        std::string getName() {return name_;}
        std::vector<Card>* getHand() {return hand_.get();}
        void showHand();
    private:
        std::string name_; 
        std::unique_ptr<std::vector<Card>> hand_;
};
}

#endif //person_hpp