#include <vector>

#ifndef DECK_HPP
# define DECK_HPP

# define VALUES "A23456789TJQK"
# define SUITS "sdhc"

class Card {
    public:
        Card(char v, char s);
        ~Card();

        char    get_value(void);
        char    get_suit(void);

        void    dump(void);
    private:
        char    value;
        char    suit;
};

class Shoe {
    public:
        Shoe(int deck_count);
        ~Shoe();
        void    shuffle(void);
        void    shuffle(int seed);
        void    reset(void);

        Card    draw(void);
        Card    &peek(void);
        void    dump(void);

        bool    eos(); // Fonction a parfaire... Un peu pourri rn
    private:
        std::vector<Card>   cards;
        unsigned int        initial_size;
};

#endif