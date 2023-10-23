#include <table.hpp>
#include <iostream>

int	run_game(void)
{
	Player	p("Twigister", 1000);
	Table	table(p, 4);

	while (table.play_shoe());
	return (p.get_stack());
}

int	main(void)
{
	int	money = run_game();

	std::cout << "You ended the night with " << money << std::endl;
	return (0);
}