#include <table.hpp>

int	main(void)
{
	Player	p("Twigister", 1000);
	Table	table(p, 4);

	while (table.play_shoe());
	return (0);
}