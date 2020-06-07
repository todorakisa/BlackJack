#ifndef __PLAYER_CPP
#define __PLAYER_CPP

#include "player.h"
#include <fstream>
#include <iostream>
#include <cstring>

Player::Player(){
	size = 0;
	years = 0;
	wins = 0;
	KP = 0;
	looses = 0;
}

Player& Player::operator=(const Player& other){
	if(this!=&other){
		size = other.size;
		strcpy(name,other.name);
		years = other.years;
		wins = other.wins;
		KP = other.KP;
		looses = other.looses;
	}
	return *this;
}

void Player::set_name(char* name_){
	for (int i = 0; i < strlen(name_); ++i)
	{
		name[i] = name_[i];
	}
	name[strlen(name_)] = '\0';
	size = strlen(name_);
};

char* Player::get_name(){
	return name;
};

void Player::set_years(int years_){
	years = years_;
};

int Player::get_years(){
	return years;
};

int Player::get_wins(){
	return wins;
};

double Player::get_KP(){
	return KP;
};

int Player::get_looses(){
	return looses;
};

void Player::add_win(){
	wins++;
	KP = (double)wins/(double)(wins+looses);
};

void Player::add_loose(){
	looses++;
	KP = (double)wins/(double)(wins+looses);
};

void Player::save(std::ofstream& of){
	of.write((char*)&size, sizeof(size));
	of.write((char*)name, sizeof(char)*size);
	of.write((char*)&years, sizeof(years));
	of.write((char*)&wins, sizeof(wins));
	of.write((char*)&KP, sizeof(KP));
	of.write((char*)&looses, sizeof(looses));
}

void Player::load(std::ifstream& inf){
	inf.read((char*)&size, sizeof(size));
	inf.read((char*)name, sizeof(char)*size);
	inf.read((char*)&years, sizeof(years));
	inf.read((char*)&wins, sizeof(wins));
	inf.read((char*)&KP, sizeof(KP));
	inf.read((char*)&looses, sizeof(looses));
}

Player::~Player(){};

#endif