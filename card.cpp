#ifndef __CARD_CPP
#define __CARD_CPP

#include "card.h"
#include "enum.h"
#include <iostream>
#include <cstring>

Card::Card(){};

Card::Card(Card& other){
	color = other.color;
	value = other.value;
	strcpy(serial_number,other.serial_number);
}

Card::Card(Color col, Value val, char* series, char* unique){
	color = col;
	value = val;
	strcpy(serial_number,series);
	strcat(serial_number,unique);
}

Color Card::get_color(){
	return color;
}

Value Card::get_value(){
	return value;
}

char* Card::get_serial_num(){
	return serial_number;
}

void Card::set_serial_num(char* series, char* unique){
	strcpy(serial_number,series);
	strcat(serial_number,unique);
}

Card& Card::operator=(const Card &other){
	if(this!=&other){
		color = other.color;
		value = other.value;
		strcpy(serial_number,other.serial_number);
	}
	return *this;
}

bool Card::operator==(const Card& other) const{
	if(color == other.color && value == other.value){
		return true;
	}
	return false;
}

void Card::print(){
	std::cout <<"Card: "<< value << color << " Serial num:" << serial_number << std::endl;
}

Card::~Card(){};

#endif