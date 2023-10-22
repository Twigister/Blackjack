#include <player.hpp>
#include <iostream>

Player::Player(std::string newname, unsigned int newstack) : name(newname), stack(newstack), bet_unit(0) {}

Player::~Player()
{
	std::cout << "See ya " << name << "!" << std::endl;
}

bool	Player::bet(int amount)
{
	if (stack >= amount && amount > 0) {
		bet_unit = amount;
		stack -= amount;
		return (true);
	}
	return (false);
}

void	Player::win(unsigned int wager)
{
	std::cout << "It's a win: " << wager << std::endl;
	stack += wager * 2;
}

void	Player::blackjack(unsigned int wager)
{
	std::cout << "It's a BLACKJACK" << std::endl;
	stack += wager * 5 / 2;
}

void	Player::lose(void)
{
	std::cout << "It's a loss" << std::endl;
}

void	Player::push(unsigned int wager)
{
	std::cout << "It's a push" << std::endl;
	stack += wager;
}

int	Player::get_stack(void)
{
	return (stack);
}

std::string	Player::get_name(void)
{
	return (name);
}

int	Player::get_bet(void)
{
	return (bet_unit);
}

Hand	&Player::get_hand()
{
	hands.push_back(Hand(bet_unit));
	return (hands[0]);
}

std::vector<Hand> &Player::get_hands(void)
{
	return (hands);
}

void	Player::clear_hands(void)
{
	hands.clear();
}