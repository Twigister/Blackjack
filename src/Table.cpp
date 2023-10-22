#include <table.hpp>
#include <iostream>

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
	while (std::get<0>(dealer.get_count()) < 17)
		dealer.add_card(shoe.draw());
	dealer.pretty_print();
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
	for (Hand &hand : player.get_hands())
	{
		hand.dump();
		std::cout << hand.get_bet() << std::endl;
		if (hand.is_blackjack() && !dealer.is_blackjack()) // Joueur fait blackjack
			player.blackjack(hand.get_bet());
		else if (dealer.is_blackjack())
			player.lose();
		else if (std::get<0>(hand.get_count()) > 21) // Joueur bust
			player.lose();
		else if (std::get<0>(dealer.get_count()) > 21) // Dealer bust : OK
			player.win(hand.get_bet());
		else if (std::get<0>(hand.get_count()) < std::get<0>(dealer.get_count())) // 
			player.lose();
		else if (std::get<0>(hand.get_count()) > std::get<0>(dealer.get_count()))
			player.win(hand.get_bet());
		else
			player.push(hand.get_bet());
	}
}

void	Table::player_bet(void)
{
	std::string		line;
	unsigned int	num;

	while (1) {
		std::cout << "Enter your bet: ";
		std::getline(std::cin, line);
		num = std::stoi(line);
		if (player.bet(num)) {
			std::cout << "Betting " << num << std::endl;
			break;
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
		h->pretty_print();
		end_hand = false;
		while (std::get<0>(h->get_count()) < 21 && !end_hand) {
			if (h->get_card_count() == 1)
				h->add_card(shoe.draw());
			h->dump();
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
					if (player.get_stack() >= player.get_bet() && h->get_card_count() == 2) {
						h->add_card(shoe.draw());
						h->set_bet(h->get_bet() * 2);
						player.bet(player.get_bet());
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
					else { // Il faut gérer la balance
						Card c = h->split();

						h->add_card(shoe.draw());
						hands.push_back(Hand(player.get_bet()));
						player.bet(player.get_bet());
						hands.back().add_card(c);
						h = &hands[i];
						std::cout << "1st ";
						h->dump();
						std::cout << "2nd ";
						hands.back().dump();
												
						/*hands.push_back(Hand(player.get_bet()));
						player.bet(player.get_bet());
						hands.back().add_card(h->split());
						h->add_card(shoe.draw());
						std::cout << "1st hand: ";
						h->dump();
						std::cout << "2nd hand: ";	
						hands.back().dump();*/
						std::cout << "WIP" << std::endl;
					}
					break;
				default:
					std::cout << "Invalid input" << std::endl;
			}
			player.get_hands() = hands;
		}
	}
}

void	Table::clear_hands()
{
	player.clear_hands();
	dealer.clear();
}

void	Table::round()
{
	std::cout << "Starting a new round:" << std::endl;
	player_bet();
	deal();
	player_turn();
	dealer_play();
	payout();
	clear_hands();
	std::cout << player.get_stack() << std::endl << std::endl;
}

void	Table::play_shoe()
{
	while (shoe.eos() == false)
		round();
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