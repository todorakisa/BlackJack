#ifndef __ENUM_CPP
#define __ENUM_CPP

#include "enum.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, Color& col){
	switch(col){
		case Heart:	out << "Heart";break;
		case Diamond: out << "Diamond";break;
		case Club: out << "Club";break;
		case Spade: out << "Spade";break;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, Value& val){
	switch(val){
		case two:	out << "2";break;
		case three: out << "3";break;
		case four: out << "4";break;
		case five: out << "5";break;
		case six:	out << "6";break;
		case seven: out << "7";break;
		case eight: out << "8";break;
		case nine: out << "9";break;
		case ten:	out << "10";break;
		case J: out << "J";break;
		case Q: out << "Q";break;
		case K: out << "K";break;
		case A: out << "A";break;
	}
	return out;
}

#endif