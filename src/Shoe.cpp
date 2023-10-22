#include <deck.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Shoe::Shoe(int deck_count=4) : initial_size(deck_count * 52)
{
	for (int deck_counter = 0; deck_counter < deck_count; deck_counter++)
		for (int value_counter = 0; value_counter < 13; value_counter++)
			for (int suit_counter = 0; suit_counter < 4; suit_counter++)
				cards.push_back(Card(value_counter, suit_counter));
}

Shoe::~Shoe()
{
	std::cout << "Destroying the shoe" << std::endl;
}

Card	Shoe::draw(void)
{
	Card	cp(cards.front());
	
	cards.erase(cards.begin());
	return (cp);
}

Card	&Shoe::peek(void)
{
	return (cards.front());
}

void	Shoe::shuffle(int seed)
{
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

void	Shoe::shuffle(void)
{
	shuffle(std::chrono::system_clock::now().time_since_epoch().count());
}

void	Shoe::reset(void)
{
	cards.clear();
	for (unsigned int deck_counter = 0; deck_counter < initial_size / 52; deck_counter++)
		for (int value_counter = 0; value_counter < 13; value_counter++)
			for (int suit_counter = 0; suit_counter < 4; suit_counter++)
				cards.push_back(Card(value_counter, suit_counter));}

void	Shoe::dump(void)
{
	std::cout << "Shoe data:" << std::endl;
	std::cout << "Card count: " << cards.size() << std::endl;
	for (Card &i : cards)
		std::cout << VALUES[(int)i.get_value()] << SUITS[(int)i.get_suit()] << ' ';
	std::cout << std::endl;
}

bool	Shoe::eos(void)
{
	return (cards.size() < initial_size / 4);
}