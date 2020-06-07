#ifndef __SAVE_FILE_H
#define __SAVE_FILE_H

#include "player.h"

class Save_File{
	char name[15];
	int player_size;
	Player* players;
public:
	Save_File();
	void load_data();
	void save_data();
	void create_file();
	void print_all_players();
	void add_player(Player& plr);
	bool have_such_player(char* name);
	Player& find_player_by_name(char* name);
	~Save_File();
};

#endif