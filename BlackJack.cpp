#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

#include "enum.h"
#include "card.h"
#include "deck.h"
#include "player.h"
#include "savefile.h"

char* substr(const char* str, size_t start_pos = 0, size_t end_pos = 0){
	if(end_pos == 0 || end_pos > strlen(str)){
		end_pos = strlen(str);
	}
	size_t size = end_pos - start_pos;
	char* substr = new char[size + 1];
	size_t index = 0;
	for (size_t i = start_pos; i < end_pos; i++)
	{
		*(substr+index) = str[i];
		index++; 
	}
	substr[size] = '\0';
	return substr;
}

int main(){
	char command[100];
	char* first_comand = nullptr;
	Player current_payer;
	bool have_curr_plr = false;
	Save_File file;
	file.create_file();
	file.load_data();
	cout << endl;
	cout << "----------------Welcome to the famous game named BlackJack----------------" << endl;
	cout << "If you have any questions about the supported commands use the command \"help\"" << endl;
	cout << "In order to play you need to create new user with the command \"createusr\" \nor choose one of the following users with the command \"chooseplr <player>\":" << endl;
	cout << endl;
	file.print_all_players();
	cout << endl;
	Deck deck;
	while(true){
		cout << ">";
		cin.getline(command,100);

		first_comand = substr(command,0,9);
		if(strcmp(first_comand,"createusr")==0){
			char name[100];
			int age;
			cout << "Enter your name:" << endl;
			cin.getline(name,100);
			cout << "In order to play you must be atleast 18 year old!" << endl;
			cout << "Enter your age:" << endl;
			cin >> age;
			cin.ignore();
			while(age < 18 && age > 90){
				cout << "Enter your age again and this time think twice:" << endl;
				cin >> age;
				cin.ignore();
			}
			current_payer.set_name(name);
			current_payer.set_years(age);
			file.add_player(current_payer);
			file.save_data();
			have_curr_plr = true;
		}

		if(strcmp(first_comand,"chooseplr")==0 && strlen(command) > 11){
			char* player_name = substr(command,10);
			if(file.have_such_player(player_name)){
				current_payer = file.find_player_by_name(player_name);
				cout << "You will play as " << current_payer.get_name() << endl;
				have_curr_plr = true;
			}else{
				cout << "There is no such player" << endl;
			}
			delete[] player_name;
		}
		delete[] first_comand;

		first_comand = substr(command,0,5);
		if(strcmp(first_comand,"play") == 0){
			if(!have_curr_plr){
				cout << "Seriously?? Did you read the description?" << endl;
				cout << "Create new player or choose a player!!!" << endl;
			}else{
				bool end_game = false;
				int size_of_deck = 0;
				cout << "Enter the size of the deck, if you want start the game with standart Deck just type 52" << endl;
				cout << "$";
				cin >> size_of_deck;
				if(size_of_deck!=52){
					Deck deck_(size_of_deck);
					deck = deck_;
				}else{
					Deck deck_;
					deck = deck_;
				}
				int points = 0;
				int index_plr = 0;			
				Card drawed_cards[10];
				char player_comand[20];
				cout << "________________________________" << endl;
				cout << "|       The Game Starts!!      |" << endl;
				cout << "L______________________________J" << endl;
				cout << endl;
				drawed_cards[index_plr] = deck.draw();
				if(drawed_cards[index_plr].get_value() == 11 || drawed_cards[index_plr].get_value() == 12 || drawed_cards[index_plr].get_value() == 13){
					points+= 10;
				}else if(drawed_cards[index_plr].get_value() == 14){
					if(points + 11 > 21){
						points+=1;
					}else{
						points+=11;
					}
				}else{
					points+= drawed_cards[index_plr].get_value();
				}
				index_plr++;
				cout << "--------Your Cards and Points----------" << endl;
				for (int i = 0; i < index_plr; ++i)
				{	
					Color col = drawed_cards[i].get_color();
					Value val = drawed_cards[i].get_value();
					cout << val << "(" << col << ")" << " ";
				}
				cout << "(Points "<< points << ")" << endl;
				while(true){
					cout << "Hit/Stand/Probability" << endl;
					cout << "---------------------------------------" << endl;
					cout << "$";
					cin >> player_comand;
					if(strcmp(player_comand,"Stand") == 0){
						break;
					}else if(strcmp(player_comand,"Probability") == 0){
						if(points < 10){
							cout << "0" << endl;
						}else{
							int requared_points = 21 - points;
							int num_of_needed_cards = 0;
							if(requared_points == 1 || requared_points == 11){
								num_of_needed_cards = deck.rank_count(A);
							}else if(requared_points == 10){
								num_of_needed_cards = deck.rank_count(J) + deck.rank_count(Q) + deck.rank_count(K) + deck.rank_count(ten);
							}else{
								Value val;
								switch(requared_points){
									case 2:	val = two;break;
									case 3: val = three;break;
									case 4: val = four;break;
									case 5: val = five;break;
									case 6:	val = six;break;
									case 7: val = seven;break;
									case 8: val = eight;break;
									case 9: val = nine;break;
								}
								num_of_needed_cards = deck.rank_count(val);
							}
							double prob = (double)num_of_needed_cards/(double)(size_of_deck - index_plr);
							cout << prob << endl;
						}
					}else if(strcmp(player_comand,"Hit") == 0){
						drawed_cards[index_plr] = deck.draw();
						if(drawed_cards[index_plr].get_value() == 11 || drawed_cards[index_plr].get_value() == 12 || drawed_cards[index_plr].get_value() == 13){
							points+= 10;
						}else if(drawed_cards[index_plr].get_value() == 14){
							if(points + 11 > 21){
								points+=1;
							}else{
								points+=11;
							}
						}else{
							points+= drawed_cards[index_plr].get_value();
						}
						index_plr++;
						cout << "--------Your Cards and Points----------" << endl;
						for (int i = 0; i < index_plr; ++i)
						{	
							Value val = drawed_cards[i].get_value();
							Color col = drawed_cards[i].get_color();
							cout << val << "(" << col << ")" << " ";
						}
						cout << "(Points "<< points << ")" << endl;
						if(points > 21){
							cout << "You loose!" << endl;
							current_payer.add_loose();
							end_game = true;
							break;
						}
						if(points == 21){
							cout << "You Win!" << endl;
							current_payer.add_win();
							end_game = true;
							break;
						}
					}
				}
				if(!end_game){
					int croupier_points = 0;
					int index_crp = 0;
					Card croupier_cards[10];
					while(croupier_points < 17){
						croupier_cards[index_crp] = deck.draw();
						if(croupier_cards[index_crp].get_value() == 11 || croupier_cards[index_crp].get_value() == 12 || croupier_cards[index_crp].get_value() == 13){
							croupier_points+= 10;
						}else if(croupier_cards[index_crp].get_value() == 14){
							if(croupier_points + 11 > 21){
								croupier_points+=1;
							}else{
								croupier_points+=11;
							}
						}else{
							croupier_points+= croupier_cards[index_crp].get_value();
						}
						index_crp++;
					}
					cout << "--------Dealer Cards and Points--------" << endl;
					cout << "The dealer's draw: ";
					for (int i = 0; i < index_crp; ++i)
					{	Value val = croupier_cards[i].get_value();
						Color col = croupier_cards[i].get_color();
						cout << val << "(" << col << ")" << " ";
					}
					cout << "(Points "<< croupier_points << ")" << endl;
					if(croupier_points > 21){
						cout << "You Win!" << endl;
						current_payer.add_win();
					}else if(croupier_points > points){
						cout << "You loose!" << endl;
						current_payer.add_loose();
					}else if(croupier_points < points){
						cout << "You Win!" << endl;
						current_payer.add_win();
					}else if(croupier_points == points){
						cout << "You Win!" << endl;
						current_payer.add_win();
					}
				}
			 	file.find_player_by_name(current_payer.get_name()) = current_payer;
			 	file.save_data();
			 	cout << "Saved your score in the file" << endl;
			 	cin.ignore();
			}
		}	
		delete[] first_comand;

		first_comand = substr(command,0,4);
		if(strcmp(first_comand,"help") == 0){
			cout << "-------------------------------------------------------" << endl;
			cout << "The following commands are supported:" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "createuser            creates new user" << endl;
			cout << "chooseplr <player>    chooses a player from the existing ones" << endl;
			cout << "play                  starts a new game" << endl;
			cout << "exit                  exits the program(works only if you don't play a game)" << endl;
			cout << "-------------------------------------------------------" << endl;
		}	

		if(strcmp(first_comand,"exit") == 0){
			cout << "Exiting the program..." << endl;
			delete[] first_comand;
			break;
		}	
		delete[] first_comand;
	}
	return 0;
}