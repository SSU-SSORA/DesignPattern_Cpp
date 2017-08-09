#pragma once
#include <string>
using namespace std;

class Item {
public:
	Item(string str) : data_(str) {}
	string data_;
};