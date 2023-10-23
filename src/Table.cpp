#include <table.hpp>
#include <iostream>
#include <utils.hpp>

Table::Table(Player &p, unsigned int deck_count=4) : dealer(0), player(p), shoe(deck_count)
{
	std::cout << "Launching a table!" << std::endl;
	shoe.shuffle();
}

Table::~Table()
{
	std::cout << "Gentlemens, the night has ended!" << std::endl;
}

void	Table::dealer_play()
{
	std::cout << "Dealer's turn!" << std::endl;
	dealer.pretty_print();
	while (std::get<0>(dealer.get_count()) < 17) {
		Card c = shoe.draw();
		
		std::cout << "Dealer hits a: ";
		c.dump();
		dealer.add_card(c);
		dealer.pretty_print();
	}
	if (dealer.get_hard_count() > 21) {
		std::cout << "Dealer busts" << std::endl;
	} else if (dealer.is_blackjack()) {
		std::cout << "Dealer has a Blackjack" << std::endl;
	} else {
		std::cout << "Dealer stands on: ";
		dealer.pretty_print();
	}
}

void	Table::deal()
{
	Hand	&h = player.get_hand();

	for (int i = 0; i < 2; i++)
	{
		h.add_card(shoe.draw());
		if (i == 0)
			dealer.add_card(shoe.draw());
	}
}

void	Table::payout(void)
{
	int	wins = 0;

	for (Hand &hand : player.get_hands()) {
		int	hand_bet = hand.get_bet();

		hand.pretty_print();
		if (hand.is_blackjack() && !dealer.is_blackjack()) {
			player.blackjack(hand.get_bet());
			wins += hand_bet * 3 / 2;
		} else if (dealer.is_blackjack() && !hand.is_blackjack()) {
			player.lose();
			wins -= hand_bet;
		} else if (std::get<0>(hand.get_count()) > 21) {
			player.lose();
			wins -= hand_bet;
		} else if (std::get<0>(dealer.get_count()) > 21){
			player.win(hand.get_bet());
			wins += hand_bet;
		} else if (std::get<0>(hand.get_count()) < std::get<0>(dealer.get_count())) {
			player.lose();
			wins -= hand_bet;
		} else if (std::get<0>(hand.get_count()) > std::get<0>(dealer.get_count())) {
			player.win(hand.get_bet());
			wins += hand_bet;
		} else {
			player.push(hand.get_bet());
		}
	}
	std::cout << "Round result: " << wins << " your new balance is: " << player.get_stack() << std::endl;
}

bool	Table::player_bet(void)
{
	std::string		line;
	unsigned int	num;

	while (1) {
		std::cout << "Enter your bet or STOP: ";
		std::getline(std::cin, line);
		if (line == "STOP")
			return (false);
		if (is_number(line) && (num = std::stoi(line)) && player.bet(num)) {
			std::cout << "Betting " << num << std::endl << std::endl;
			return (true);
		} else {
			std::cout << "Invalid bet" << std::endl;
		}
	}
}

void	Table::player_turn()
{
	std::string line;
	bool		end_hand;
	std::vector<Hand> &hands = player.get_hands();

	std::cout << "Player's turn" << std::endl;
	for (size_t i = 0; i < hands.size(); i++) { // Hand &h : hands
		Hand *h = &hands[i];
		end_hand = false;
		while (std::get<0>(h->get_count()) < 21 && !end_hand) {
			if (h->get_card_count() == 1) {
				h->add_card(shoe.draw());
				continue;
			}
			std::cout << "Your hand:" << std::endl;
			h->pretty_print();
			std::cout << "Dealer upcard: ";
			dealer.print_cards();
			std::cout << std::endl;
			std::cout << "Enter your action: Stand/Hit/Double/sPlit:" << std::endl;
			std::getline(std::cin, line);
			switch (line[0]) {
				case 'S':
					end_hand = true;
					break;
				case 'H':
					h->add_card(shoe.draw());
					break;
				case 'D':
					if (h->get_card_count() == 2 && player.bet(player.get_bet())) {
						h->add_card(shoe.draw());
						h->set_bet(h->get_bet() * 2);
						end_hand = true;
					} else if (h->get_card_count() != 2) {
						std::cout << "Can't double after a Hit !" << std::endl;
					} else {
						std::cout << "Insuficcient funds" << std::endl;
					}
					break;
				case 'P':
					if (!h->is_double())
						std::cout << "Invalid split" << std::endl;
					else {
						if (player.bet(player.get_bet()))
						{
							Card c = h->split();

							h->add_card(shoe.draw());
							hands.push_back(Hand(player.get_bet()));
							hands.back().add_card(c);
							h = &hands[i];
							std::cout << "1st ";
							h->pretty_print();
							std::cout << "2nd ";
							hands.back().pretty_print();
						} else {
							std::cout << "Insuficcient funds" << std::endl;
						}
					}
					break;
				default:
					std::cout << "Invalid input" << std::endl;
			}
			player.get_hands() = hands;
			std::cout << std::endl;
		}
		if (h->get_hard_count() > 21) {
			std::cout << "You bust!" << std::endl;
		} else {
			std::cout << "Standing on: " << h->get_soft_count() << std::endl;
		}
	}
}

void	Table::clear_hands()
{
	player.clear_hands();
	dealer.clear();
}

bool	Table::round()
{
	std::cout << "Starting a new round:" << std::endl;
	if (!player_bet())
		return (false);
	deal();
	player_turn();
	dealer_play();
	payout();
	clear_hands();
	return (true);
}

bool	Table::play_shoe()
{
	while (shoe.eos() == false) {
		if (!round())
			return (false);
		if (player.get_stack() == 0) {
			std::cout << "You're broke buddy!" << std::endl;
			return (false);
		}
	}
	return (true);
}

void	Table::new_shoe(void)
{
	shoe.reset();
	shoe.shuffle();
}

void	Table::new_shoe(int seed)
{
	shoe.reset();
	shoe.shuffle(seed);
}