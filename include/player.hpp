#ifndef PLAYER_H
# define PLAYER_H

# include <hand.hpp>
# include <string>

class Player {
	public:
		Player(std::string name, unsigned int stack);
		~Player();

		bool					bet(int amount);

		void					win(unsigned int wager);
		void					lose(void);
		void					push(unsigned int wager);
		void					blackjack(unsigned int wager);

		int						get_stack(void);
		std::string				get_name(void);
		int						get_bet(void);
		Hand					&get_hand(void);
		std::vector<Hand>		&get_hands(void);
		void					clear_hands(void);
	private:
		std::vector<Hand>		hands;
		std::string				name;
		int						stack;
		int						bet_unit;
};

#endif