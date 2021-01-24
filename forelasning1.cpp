#include <iostream>
#include <string>
#include <vector>

//g++17

class Card
{
public:
  Card(std::string const& suitp, int valuep)
    : suit{suitp}, value{valuep}
  {
    if(valuep < 1 || valuep > 13)
    {
//      throw std::logic_error{"bad card value"};
    }
  }
  int get_value() const
  {
    return value;
  }
private:
  std::string suit;
  int value;
};

class Deck
{
public:
  Deck() : deck{}
  {
    for(int i{0}; i<=12; i++)
      deck.push_back(Card{"hearts",i});
  }
private:
  std::vector<Card> deck;
};

  
int main()
{
  Card c{"hearts",2};
  std::cout << c.get_value() << std::endl;
  
   Deck deck1{};
  // deck1.shuffle();
  // while(!deck1.is_empty())
  // {
  //   Card card1{deck1.draw()};
  //   std::cout << card1.to_string() << std::endl;
  // }
  return 0;
}
