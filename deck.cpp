#ifndef __DECK_CPP
#define __DECK_CPP

#include "enum.h"
#include "card.h"
#include "deck.h"

#include<iostream>
#include<cmath>
#include<cstring>

Deck::Deck(){
	drawed_cards_size = 0;
	strcpy(series,"Default");
	cards_size = 52;
	cards = new Card[cards_size];
	for (int i = 0; i < cards_size; ++i)
	{
		char unique[5];
		int unq = rand()%10000;
		for (int h = 0; h < 4; ++h)
		{
			unique[h] = '0' + unq%10;
			unq/=10;
		}
		unique[4] = '\0';
		int color = rand()%10;
		while(color > 3){
			color = rand()%10;
		}
		int power = rand()%100;
		while(power > 14 || power < 2){
			power = rand()%100;
		}
		enum Color col;
		enum Value val;
		switch(color){
			case 0:	col = Heart;break;
			case 1: col = Diamond;break;
			case 2: col = Club;break;
			case 3: col = Spade;break;
		}
		switch(power){
			case 2:	val = two;break;
			case 3: val = three;break;
			case 4: val = four;break;
			case 5: val = five;break;
			case 6:	val = six;break;
			case 7: val = seven;break;
			case 8: val = eight;break;
			case 9: val = nine;break;
			case 10: val = ten;break;
			case 11: val = J;break;
			case 12: val = Q;break;
			case 13: val = K;break;
			case 14: val = A;break;
		}
		Card card(col, val, series, unique);
		bool true_unique_card = true;
		for (int j = 0; j < i; ++j)
		{
			if(cards[j] == card){
				true_unique_card = false;
			}
			if(strcmp(cards[j].get_serial_num(),card.get_serial_num()) == 0){
				while(strcmp(cards[j].get_serial_num(),card.get_serial_num()) == 0){
					unq = rand()%10000;
					for (int h = 0; h < 4; ++h)
					{
						unique[h] = '0' + unq%10;
						unq/=10;
					}
					unique[4] = '\0';
					card.set_serial_num(series, unique);
				}	
			}
		}
		if(true_unique_card){
			cards[i] = card;
		}else{
			i--;
		}
	}
}

Deck::Deck(int size, char* ser){
	if(ser == nullptr){
		strcpy(series,"Custom");
	}else if(strlen(ser)>10){
		std::cout << "invalid series, series is set to Custom" << std::endl;
		strcpy(series,"Custom");
	}else{
		strcpy(series,ser);
	}
	drawed_cards_size = 0;
	cards_size = size;
	cards = new Card[cards_size];
	int possible_repeat = ceil(((cards_size-1)/52) + 1);
	for (int i = 0; i < cards_size; ++i)
	{
		char unique[5];
		int unq = rand()%10000;
		for (int h = 0; h < 4; ++h)
		{
			unique[h] = '0' + unq%10;
			unq/=10;
		}
		unique[4] = '\0';
		int color = rand()%10;
		while(color > 3){
			color = rand()%10;
		}
		int power = rand()%100;
		while(power > 14 || power < 2){
			power = rand()%100;
		}
		enum Color col;
		enum Value val;
		switch(color){
			case 0:	col = Heart;break;
			case 1: col = Diamond;break;
			case 2: col = Club;break;
			case 3: col = Spade;break;
		}
		switch(power){
			case 2:	val = two;break;
			case 3: val = three;break;
			case 4: val = four;break;
			case 5: val = five;break;
			case 6:	val = six;break;
			case 7: val = seven;break;
			case 8: val = eight;break;
			case 9: val = nine;break;
			case 10: val = ten;break;
			case 11: val = J;break;
			case 12: val = Q;break;
			case 13: val = K;break;
			case 14: val = A;break;
		}
		Card card(col, val, series, unique);
		bool true_unique_card = true;
		int repeated = 0;
		for (int j = 0; j < i; ++j)
		{
			if(cards[j] == card){
				repeated++;
				if(repeated >= possible_repeat){
					true_unique_card = false;
				}
			}
			if(strcmp(cards[j].get_serial_num(),card.get_serial_num()) == 0){
				while(strcmp(cards[j].get_serial_num(),card.get_serial_num()) == 0){
					unq = rand()%10000;
					for (int h = 0; h < 4; ++h)
					{
						unique[h] = '0' + unq%10;
						unq/=10;
					}
					unique[4] = '\0';
					card.set_serial_num(series, unique);
				}	
			}
		}
		if(true_unique_card){
			cards[i] = card;
		}else{
			i--;
		}
	}
}

Deck& Deck::operator=(const Deck& other){
	if(this!=&other){
		drawed_cards_size = other.drawed_cards_size;
		strcpy(series,other.series);
		cards_size = other.cards_size;
		delete[] cards;
		cards = new Card[cards_size];
		for (int i = 0; i < cards_size; ++i)
		{
			cards[i] = other.cards[i];	
		}
	}
	return *this;
}

void Deck::print_all_card(){
	std::cout << "Seriq:" << series << ";" << std::endl;
	for (int i = 0; i < cards_size; ++i)
	{
		cards[i].print();
	}
}

Card Deck::draw(){
	Card result;
	drawed_cards_size++;
	if(drawed_cards_size == cards_size){
		drawed_cards_size = 0;
	}
	result = cards[0];
	for (int i = 0; i < cards_size-1; ++i)
	{
		cards[i] = cards[i+1];
	}
	cards[cards_size-1] = result;
	return result;
};
void Deck::swap(int first,int second){
	if(first < 0 || first >= cards_size || second < 0 || second >= cards_size){
		std::cout << "Can't swap invalide index" << std::endl;
	}
	Card help;
	help = cards[first];
	cards[first] = cards[second];
	cards[second] = help;
};
int Deck::suit_count(Color col){
	int result = 0;
	for (int i = 0; i < cards_size; ++i)
	{
		if(cards[i].get_color() == col){
			result++;
		}
	}
	return result;
};
int Deck::rank_count(Value val){
	int result = 0;
	for (int i = 0; i < cards_size - drawed_cards_size; ++i)
	{
		if(cards[i].get_value() == val){
			result++;
		}
	}
	return result;
};

Deck::~Deck(){
	delete[] cards;
}

#endif