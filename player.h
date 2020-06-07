#ifndef __PLAYER_H
#define __PLAYER_H

#include <fstream>
#include <iostream>

class Player{
	short size;
	char name[100];
	int years;
	int wins;
	double KP;
	int looses;
public:
	Player();
	Player& operator=(const Player& other);
	void set_name(char* name_);
	char* get_name();
	void set_years(int years_);
	int get_years();
	int get_wins();
	double get_KP();
	int get_looses();
	void add_win();
	void add_loose();
	void save(std::ofstream& of);
	void load(std::ifstream& inf);
	~Player();
};

#endif