#ifndef TABLE_HPP
# define TABLE_HPP

#include <player.hpp>
#include <deck.hpp>

class Table {
	public:
		Table(Player &p, unsigned int deck_count);
		~Table();

		bool	round();
		bool	player_bet(void);
		void	deal();
		void	player_turn();
		void	dealer_play();
		void	payout();
		void	clear_hands();

		bool	play_shoe();
		void	new_shoe();
		void	new_shoe(int seed);
	private:
		Hand	dealer;
		Shoe	shoe;
		Player	&player;
};

#endif