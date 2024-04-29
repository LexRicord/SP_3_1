#pragma once
#include <string>

using namespace std;

namespace os11_04
{
	wchar_t* getWC(const char* c);
	string incrementPayload(char* str);
	int charToInt(char* str);
	string intToString(int number);
};
