#include <hand.hpp>
#include <iostream>

Hand::Hand(unsigned int wager) : bet(wager) {}

Hand::~Hand() {}

void	Hand::add_card(Card c)
{
	cards.push_back(c);
}

unsigned int	Hand::get_bet(void)
{
	return (bet);
}

void	Hand::set_bet(unsigned int wager)
{
	bet = wager;
}

Card	Hand::split(void)
{
	Card	card(cards.back());

	cards.pop_back();
	dump();
	return card;
}

std::pair<unsigned int, unsigned int>	Hand::get_count()
{
	unsigned int	soft = 0;
	unsigned int	hard = 0;

	for (auto i : cards) {
		if (i.get_value() == 0)
			soft += 10;
		if (i.get_value() >= 9)
		{
			soft += 10;
			hard += 10;
		}
		else
		{
			soft += i.get_value() + 1;
			hard += i.get_value() + 1;
		}
		if (soft > 21 && soft != hard)
			soft -= 10;
	}
	return (std::make_pair(soft, hard));
}

unsigned int	Hand::get_soft_count(void)
{
	return (std::get<0>(get_count()));
}

unsigned int	Hand::get_hard_count(void)
{
	return (std::get<1>(get_count()));
}

int		Hand::get_card_count(void)
{
	return (cards.size());
}

bool	Hand::is_blackjack(void)
{
	return (get_soft_count() == 21 && cards.size() == 2);
}

bool	Hand::is_double(void)
{
	return (cards.size() == 2 && ((cards.front().get_value() == cards.back().get_value()) || (std::get<0>(get_count()) == 20 && std::get<1>(get_count()) == 20)));
}

void	Hand::clear(void)
{
	cards.clear();
}

void	Hand::dump(void)
{
	std::cout << "Hand data:" << std::endl;
	std::cout << cards.size() << " cards in the hand" << std::endl;
	for (auto i : cards)
		std::cout << VALUES[(int)i.get_value()] << SUITS[(int)i.get_suit()]	 << ' ';
	std::cout << std::endl;
	std::cout << "Total: ";
	if (get_soft_count() != get_hard_count())
		std::cout << get_soft_count() << "/";
	std::cout << get_hard_count() << std::endl;
}

void	Hand::pretty_print(void)
{
	for (auto i : cards)
		std::cout << VALUES[(int)i.get_value()] << SUITS[(int)i.get_suit()] << ' ';
	std::cout << "(";
	if (std::get<0>(get_count()) != std::get<1>(get_count()))
		std::cout << std::get<0>(get_count()) << "/";
	std::cout << std::get<1>(get_count()) << ")" << std::endl;
}

void	Hand::print_cards(void)
{
	for (auto c : cards)
		std::cout << VALUES[(int)c.get_value()] << SUITS[(int)c.get_suit()] << " ";
}