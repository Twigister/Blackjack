#include <deck.hpp>
#include <iostream>

Card::Card(char v, char s)
{
	value = v;
	suit = s;
}

Card::~Card() {}

char Card::get_value(void)
{
	return (value);
}

char Card::get_suit(void)
{
	return (suit);
}

void	Card::dump(void)
{
	std::cout << VALUES[(int)value] << SUITS[(int)suit] << std::endl;
}