#ifndef __ENUM_H
#define __ENUM_H

#include <iostream>

enum Color{	Heart,Diamond,Club,Spade};
enum Value{ two = 2, three, four, five, six, seven, eight, nine, ten, J, Q, K, A};

std::ostream& operator<<(std::ostream& out, Color& col);
std::ostream& operator<<(std::ostream& out, Value& val);

#endif