#ifndef __DECK_H
#define __DECK_H

#include "enum.h"
#include "card.h"

class Deck{
	int cards_size;
	int drawed_cards_size;
	Card* cards;
	char series[10];
public:
	Deck();
	Deck(int size, char* ser = nullptr);
	Deck& operator=(const Deck& other);
	void print_all_card();
	Card draw();
	void swap(int first,int second);
	int suit_count(Color col);
	int rank_count(Value val);
	~Deck();
};

#endif