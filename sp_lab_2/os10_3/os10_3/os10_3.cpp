﻿#ifdef _WIN64
#pragma comment(lib, "../x64/debug/os10_api.lib")
#else
#pragma comment(lib, "../debug/os10_api.lib")
#endif

#include "../../os10_api/os10_api/pch.h"
#include "../../os10_api/os10_api/HT.h"

using namespace std;

int main()
{
	ht::HtHandle* ht1 = nullptr;
	ht::HtHandle* ht2 = nullptr;

#pragma region ht1

	try
	{
		cout << "### ht1 ###" << endl;
		ht1 = ht::create(1000, 3, 10, 256, L"./output/HTspace.ht");
		if (ht1)
			cout << "-- create: success" << endl;
		else
			throw "-- create: error";

		cout << "ht1: " << ht1->addr << endl;

		if (ht::insert(ht1, new ht::Element("key", 4, "payload", 8)))
			cout << "-- insert: success" << endl;
		else
			throw "-- insert: error";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << ht::getLastError(ht1) << endl;
	}

#pragma endregion

#pragma region ht2

	try
	{
		cout << "\n### ht2 ###" << endl;
		ht2 = ht::open(L"./output/HTspace.ht", true);
		if (ht2)
			cout << "-- create: success" << endl;
		else
			throw "-- create: error";

		cout << "ht2: " << ht2->addr << endl;

		ht::Element* hte = ht::get(ht1, new ht::Element("key", 4));
		if (hte)
			cout << "-- get: success" << endl;
		else
			throw "-- get: error";

		ht::print(hte);
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << ht::getLastError(ht1) << endl;
	}

#pragma endregion

	try
	{
		if (ht1 != nullptr)
			if (ht::close(ht1))
				cout << "-- close: success (ht1)" << endl;
			else
				throw "-- close: error (ht1)";

		if (ht2 != nullptr)
			if (ht::close(ht2))
				cout << "-- close: success (ht2)" << endl;
			else
				throw "-- close: error (ht2)";
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}