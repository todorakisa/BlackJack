#ifndef __SAVE_FILE_CPP
#define __SAVE_FILE_CPP

#include "player.h"
#include "savefile.h"

#include <iostream>
#include <fstream>
#include <cstring>

Save_File::Save_File():players(nullptr),player_size(0){
	char name_[15] = {"playerdata.bin"};
	for (int i = 0; i < strlen(name_); ++i)
	{
		name[i] = name_[i];
	}
}

void Save_File::load_data(){
	std::streampos size;
	std::ifstream original_file(this->name,std::ios::in|std::ios::binary|std::ios::ate);
	if(original_file.is_open()){
		size = original_file.tellg();
		original_file.seekg(0, std::ios::beg);
		original_file.read((char*)&player_size, sizeof(player_size));
		players = new Player[player_size];
		for (int i = 0; i < player_size; ++i)
		{
			players[i].load(original_file);
		}
	}else{
		std::cout << "The file cannot be opened" << std::endl;
		original_file.close();
		return;
	}
	original_file.close();
}

void Save_File::save_data(){
	remove(name);
	std::ofstream new_file(name, std::ios::binary|std::ios::out);
	new_file.write((char*)&player_size, sizeof(player_size));
	for (int i = 0; i < player_size; ++i)
	{
		players[i].save(new_file);
	}
	new_file.close();
}

void Save_File::create_file(){
	std::ifstream original_file(this->name, std::ios::binary);
	if(!original_file){
		std::ofstream new_file(this->name, std::ios::binary);
		new_file.close();
	}
	original_file.close();
}

void Save_File::print_all_players(){
	if(player_size == 0){
		std::cout << "No registered players!" << std::endl;
	}
	std::cout << "---------------Player List-----------------" << std::endl;
	for (int i = 0; i < player_size; ++i)
	{
		char name[100];
		strcpy(name,players[i].get_name());
		for (int i = 0; i < strlen(name); ++i)
		{
			if(name[i] == ' ' && name[i+1] == ' '){
				name[i] = '\0';
			};
		}
		std::cout << "Name: " << name << " Age: " << players[i].get_years() << " Wins: " << players[i].get_wins() << " Winate: " << players[i].get_KP() << std::endl;
	}
	std::cout << "-------------------------------------------" << std::endl;
};	

void Save_File::add_player(Player& plr){
	Player* new_players = new Player[player_size+1];
	for (int i = 0; i < player_size; ++i)
	{
		new_players[i] = players[i];
	}
	new_players[player_size] = plr;
	player_size++;
	delete[] players;
	players = new_players;
}

bool Save_File::have_such_player(char* name){
	for (int i = 0; i < player_size; ++i)
	{
		if(strcmp(players[i].get_name(),name)==0){
			return true;
		}
	}
	return false;
}

Player& Save_File::find_player_by_name(char* name){
	for (int i = 0; i < player_size; ++i)
	{
		if(strcmp(players[i].get_name(),name)==0){
			return players[i];
		}
	}
}

Save_File::~Save_File(){
	delete[] players;
}

#endif