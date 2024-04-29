#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN64
#pragma comment(lib, "../x64/Release/OS11_HTAPI.lib")
#else
#pragma comment(lib, "../Release/OS11_HTAPI.lib")
#endif

#include <string>
#include <sstream>
#include "../os11/pch.h"
#include "../os11/ht.h"

using namespace std;

string intToString(int number);

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 10];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

typedef ht::HtHandle* (*OpenFunc)(const wchar_t*, bool);
typedef BOOL(*RemoveFunc)(ht::HtHandle*, const ht::Element*);
typedef ht::Element* (*CreateInsertElementFunc)(const void*, int, const void*, int);
typedef ht::Element* (*CreateGetElement)(const void*, int);

int main(int argc, char* argv[])
{
	try
	{
		HMODULE hmdll = nullptr;

	#ifdef _WIN64
		hmdll = LoadLibrary(L"D:\\repos\\SP_3_1\\sp_lab_3\\os11\\x64\\Debug\\OS11_HTAPI.dll");	
	#else
		hmdll = LoadLibrary(L"D:\\repos\\SP_3_1\\sp_lab_3\\os11\\x64\\Release\\OS11_HTAPI.dll");
	#endif

		if (!hmdll) {
			DWORD error = GetLastError();
			LPVOID errorMessage;
			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				nullptr,
				error,
				0,
				reinterpret_cast<LPWSTR>(&errorMessage),
				0,
				nullptr
			);
			wcout << L"[LoadLibrary] Failed with error code " << error << ": " << errorMessage << endl;
			LocalFree(errorMessage);
			throw "[LoadLibrary]: Failed";
		}
		else {
			cout << "[LoadLibrary]: Success" << endl;
		}

		OpenFunc open = (OpenFunc)GetProcAddress(hmdll, "open");
		RemoveFunc RemoveOne = (RemoveFunc)GetProcAddress(hmdll, "removeOne");
		CreateInsertElementFunc createInsertElement = (CreateInsertElementFunc)GetProcAddress(hmdll, "createInsertElement");
		CreateGetElement createGetElement = (CreateGetElement)GetProcAddress(hmdll, "createGetElement");
		RemoveFunc insert = (RemoveFunc)GetProcAddress(hmdll, "insert");

		if (!open || !RemoveOne || !createInsertElement) {
			cerr << "[GetProcAddress failed for one or more functions]" << endl;
			FreeLibrary(hmdll);
			return 1;
		}

		const wchar_t* fileName = getWC(argv[1]);

		if (fileName) {
			cout << "[Filename]: " << fileName << endl;
		}
		if (fileName) {
			cout << "[&Filename]: " << &fileName << endl;
		}
		ht::HtHandle* ht = nullptr;

		ht = open(fileName, true);
		cout << "[HT]: " << ht << endl;
		cout << ht::getLastError(ht) << endl;

		if (ht)
			cout << "[Open]: Success" << endl;
		else
			throw "[Open]: Error";

		while (true) {
			int numberKey = rand() % 50;
			string key = std::to_string(numberKey);
			cout << "[Log: key]: " << key << endl;

			ht::Element* element = createInsertElement(key.c_str(), (key.length() + 1), "0", 5);

			insert(ht, element);
			cout << "[Log: element]: " << element << endl;

			if (RemoveOne(ht, element))
				cout << "[Remove]: Success" << endl;
			else
				cout << "[Remove]: Error" << endl;

			if (!ht::get(ht, element))
			{
				cout << "[Log: removal check]: Success" << endl;
				cout << "[Log: element]: " << ht::get(ht, element) << endl;
			}	
			else
			{ 
				cout << "[Log: removal check]: Error" << endl;
				cout << "[Log: element check] " << ht::get(ht, element) << endl;
			}

			delete element;
			cout << "------------------------------" << endl;

			Sleep(1000);
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}

string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}

