#ifndef HAND_H
# define HAND_H

#include <deck.hpp>

class Hand {
	public:
		Hand(unsigned int wager);
		~Hand();
		
		unsigned int	get_bet(void);
		void			set_bet(unsigned int wager);
		Card			split(void);

		std::pair<unsigned int, unsigned int> get_count(void);
		int		get_card_count(void);
		bool	is_blackjack(void);
		bool	is_double(void);
		
		void	add_card(Card card);
		void	clear(void);

		void 	dump(void);
		void	pretty_print(void);
	private:
		std::vector<Card>	cards;
		unsigned int		bet;
};

#endif