#include <table.hpp>

int	main(void)
{
	Player	p("Armond", 1000);
	Table table(p, 1);

	table.play_shoe();
	table.new_shoe();
	// table.play_shoe();
	return (0);
}