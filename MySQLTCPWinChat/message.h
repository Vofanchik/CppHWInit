#include <string.h>
#include <iostream>
#include <algorithm>
#pragma once

using namespace std;

class Message
{
public:
	Message(const string& from, const string& text)
		:_from(from), _text(text) {}
	string& GetFrom() { return _from; }
	string& GetText() { return _text; }
	string serialize() {
		string copy = _text;
		replace(copy.begin(), copy.end(), ' ', '_');
		string ser = copy + " " + _from;
		return ser;
	};

private:
	string _from;
	string _text;
};