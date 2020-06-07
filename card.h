#ifndef __CARD_H
#define __CARD_H

#include "enum.h"

class Card{
	Color color;
	Value value;
	char serial_number[15];
public:
	Card();
	Card(Card& other);
	Card(Color col, Value val, char* series, char* unique);
	Color get_color();
	Value get_value();
	char* get_serial_num();
	void set_serial_num(char* series, char* unique);
	Card& operator=(const Card &other);
	bool operator==(const Card& other) const;
	void print();
	~Card();
};

#endif