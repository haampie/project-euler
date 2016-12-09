#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class Card
{
  friend std::ostream &operator<<(std::ostream &os, Card const &c);


public:
  static char const nums[13];
  static char const suits[4];
  enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};
  enum Num {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

private:
  Suit d_suit;
  Num d_num;

public:
  Card(Suit suite, Num num)
    : d_suit(suite), d_num(num)
  {}

  inline char num() const
  {
    return d_num;
  }

  inline Suit suit() const
  {
    return d_suit;
  }
};

char const Card::nums[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char const Card::suits[4] = {'C', 'D', 'H', 'S'};

std::ostream &operator<<(std::ostream &os, Card const &c)
{
  os << Card::suits[static_cast<int>(c.suit())] << Card::nums[static_cast<int>(c.num())];
  return os;
}

class Hand
{
  friend std::ostream &operator<<(std::ostream &os, Hand const &c);

  enum Rank {HIGH_CARD, ONE_PAIR, TWO_PAIRS, 
    THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, 
    FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH};

  std::vector<Card> d_by_num;
  std::vector<Card> d_by_suit;
  Rank d_rank = HIGH_CARD;
  bool d_same_suit = false;
  size_t d_rank_value = 0;

public:
  Hand(Card a, Card b, Card c, Card d, Card e)
    : d_by_num{a, b, c, d, e}, d_by_suit{a, b, c, d, e}
  {
    std::sort(d_by_num.begin(), d_by_num.end(), [](Card const & a, Card const & b)
    {
      return a.num() < b.num();
    });

    std::sort(d_by_suit.begin(), d_by_suit.end(), [](Card const & a, Card const & b)
    {
      return a.suit() < b.suit();
    });

    // Same suit?
    if (d_by_suit[0].suit() == d_by_suit[4].suit())
      d_same_suit = true;

    // Royal flush
    if (d_same_suit && d_by_num[0].num() == Card::TEN && d_by_num[4].num() == Card::ACE) {
      d_rank = ROYAL_FLUSH;
      return;
    }

    // Straight flush
    if (d_same_suit && d_by_num[4].num() - d_by_num[0].num() == 4) {
      d_rank = STRAIGHT_FLUSH;
      d_rank_value = d_by_num[4].num();
      return;
    }

    // Four of a kind
    if (d_by_num[0].num() == d_by_num[3].num())
    {
      d_rank = FOUR_OF_A_KIND;
      d_rank_value = d_by_num[0].num();
      return;
    }

    // Four of a kind
    if (d_by_num[1].num() == d_by_num[4].num())
    {
      d_rank = FOUR_OF_A_KIND;
      d_rank_value = d_by_num[1].num();
      return;
    }

    // Full house
    if (d_by_num[0].num() == d_by_num[2].num() && d_by_num[3].num() == d_by_num[4].num())
    {
      d_rank = FULL_HOUSE;
      d_rank_value = d_by_num[0].num();
      return;
    }

    // Full house
    if (d_by_num[0].num() == d_by_num[1].num() && d_by_num[2].num() == d_by_num[4].num())
    {
      d_rank = FULL_HOUSE;
      d_rank_value = d_by_num[2].num();
      return;
    }

    // Flush
    if (d_same_suit)
    {
      d_rank = FLUSH;
      d_rank_value = d_by_num[0].num() + d_by_num[1].num() + d_by_num[2].num() + d_by_num[3].num() + d_by_num[4].num();
      return;
    }

    // Straight
    if (d_by_num[1].num() - d_by_num[0].num() == 1 
      && d_by_num[2].num() - d_by_num[1].num() == 1 
      && d_by_num[3].num() - d_by_num[2].num() == 1 
      && d_by_num[4].num() - d_by_num[3].num() == 1) {
      d_rank = STRAIGHT;
      d_rank_value = d_by_num[4].num();
      return;
    }

    // Three of a kind.
    if (d_by_num[0].num() == d_by_num[2].num())
    {
      d_rank = THREE_OF_A_KIND;
      d_rank_value = d_by_num[0].num();
      return;
    }

    // Three of a kind.
    if (d_by_num[1].num() == d_by_num[3].num())
    {
      d_rank = THREE_OF_A_KIND;
      d_rank_value = d_by_num[1].num();
      return;
    }

    // Three of a kind.
    if (d_by_num[2].num() == d_by_num[4].num())
    {
      d_rank = THREE_OF_A_KIND;
      d_rank_value = d_by_num[2].num();
      return;
    }

    // Two pairs
    if (d_by_num[0].num() == d_by_num[1].num() && d_by_num[2].num() == d_by_num[3].num())
    {
      d_rank = TWO_PAIRS;
      d_rank_value = d_by_num[0].num() + d_by_num[2].num();
      return;
    }

    // Two pairs
    if (d_by_num[0].num() == d_by_num[1].num() && d_by_num[3].num() == d_by_num[4].num())
    {
      d_rank = TWO_PAIRS;
      d_rank_value = d_by_num[0].num() + d_by_num[3].num();
      return;
    }

    // Two pairs
    if (d_by_num[1].num() == d_by_num[2].num() && d_by_num[3].num() == d_by_num[4].num())
    {
      d_rank = TWO_PAIRS;
      d_rank_value = d_by_num[1].num() + d_by_num[3].num();
      return;
    }

    // One pair
    if (d_by_num[0].num() == d_by_num[1].num())
    {
      d_rank = ONE_PAIR;
      d_rank_value = d_by_num[0].num();
      return;
    }

    // One pair
    if (d_by_num[1].num() == d_by_num[2].num())
    {
      d_rank = ONE_PAIR;
      d_rank_value = d_by_num[1].num();
      return;
    }

    // One pair
    if (d_by_num[2].num() == d_by_num[3].num())
    {
      d_rank = ONE_PAIR;
      d_rank_value = d_by_num[2].num();
      return;
    }

    // One pair
    if (d_by_num[3].num() == d_by_num[4].num())
    {
      d_rank = ONE_PAIR;
      d_rank_value = d_by_num[3].num();
      return;
    }

    d_rank = HIGH_CARD;
    d_rank_value = d_by_num[4].num();
  }

  bool operator<(Hand const &rhs)
  {
    if (d_rank < rhs.d_rank)
      return true;

    if (d_rank > rhs.d_rank)
      return false;

    if (d_rank_value < rhs.d_rank_value)
      return true;

    if (d_rank_value > rhs.d_rank_value)
      return false;

    for (size_t idx = 5; idx != 0; --idx)
    {
      if (d_by_num[idx - 1].num() < rhs.d_by_num[idx - 1].num())
        return true;

      if (d_by_num[idx - 1].num() > rhs.d_by_num[idx - 1].num())
        return false;
    }

    return false;
  }

  inline Rank rank()
  {
    return d_rank;
  }

  inline size_t rank_value()
  {
    return d_rank_value;
  }
};

std::ostream &operator<<(std::ostream &os, Hand const &hand)
{
  std::ostream_iterator<Card> out(os, " ");
  std::copy(hand.d_by_num.begin(), hand.d_by_num.end(), out);

  switch(hand.d_rank) {
    case Hand::HIGH_CARD:
      os << "High card";
    break;
    case Hand::ONE_PAIR:
      os << "One pair";
    break;
    case Hand::TWO_PAIRS:
      os << "Two pairs";
    break;
    case Hand::THREE_OF_A_KIND:
      os << "Three of a kind";
    break;
    case Hand::STRAIGHT:
      os << "Straight";
    break;
    case Hand::FLUSH:
      os << "Flush";
    break;
    case Hand::FULL_HOUSE:
      os << "Full house";
    break;
    case Hand::FOUR_OF_A_KIND:
      os << "Four of a kind";
    break;
    case Hand::STRAIGHT_FLUSH:
      os << "Straight flush";
    break;
    case Hand::ROYAL_FLUSH:
      os << "Royal flush";
    break;
  }

  return os << " (" << hand.d_rank_value << ")";
}

Hand read_hand()
{
  std::vector<Card> cards;
  for (size_t idx = 0; idx != 5; ++idx)
  {
    std::string str;
    std::cin >> str;

    int num_idx = 0;
    int suit_idx = 0;

    for (; Card::nums[num_idx] != str[0]; ++num_idx);
    for (; Card::suits[suit_idx] != str[1]; ++suit_idx);

    cards.emplace_back(static_cast<Card::Suit>(suit_idx), static_cast<Card::Num>(num_idx));
  }

  return Hand(cards[0], cards[1], cards[2], cards[3], cards[4]);
}

int main()
{
  size_t wins = 0;
  while (std::cin.good())
  {
    Hand one = read_hand();
    // std::cout << one << '\n';
    Hand two = read_hand();
    // std::cout << two << '\n';

    if (two < one) {
      ++wins;
      // std::cout << "One wins\n";
    } else {
      // std::cout << "Two wins\n";
    }
  }

  std::cout << "Total wins for 1 = " << wins << '\n';
}