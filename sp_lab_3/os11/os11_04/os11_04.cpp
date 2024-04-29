#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN64
#pragma comment(lib, "../x64/debug/OS11_HTAPI.lib")
#else
#pragma comment(lib, "../debug/OS11_HTAPI.lib")
#endif

#include <string>
#include <sstream>
#include "../os11/pch.h"
#include "../os11/ht.h"

using namespace std;

string intToString(int number);

int charToInt(char* str)
{
	stringstream convert;
	convert << str;
	int num;
	convert >> num;

	return num;
}

string incrementPayload(char* str)
{
	int oldNumberPayload = charToInt(str);
	int newNumberPayload = oldNumberPayload + 1;
	string newPayload = intToString(newNumberPayload);

	return newPayload;
}
wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 5];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

typedef BOOL(*RemoveFunc)(ht::HtHandle*, const ht::Element*);
typedef int (*AddNumbersFunc)(int, int);
typedef ht::HtHandle* (*OpenFunc)(const wchar_t*, bool);
typedef BOOL(*UpdateFunc)(ht::HtHandle*, const ht::Element*, const void*, int);
typedef ht::Element* (*CreateInsertElementFunc)(const void*, int, const void*, int);
typedef ht::Element* (*CreateGetElement)(const void*, int);
typedef void (*Print)(const ht::Element*);

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

		AddNumbersFunc addNumbers = (AddNumbersFunc)GetProcAddress(hmdll, "AddNumbers");
		OpenFunc open = (OpenFunc)GetProcAddress(hmdll, "open");
		UpdateFunc update = (UpdateFunc)GetProcAddress(hmdll, "update");
		CreateInsertElementFunc createInsertElement = (CreateInsertElementFunc)GetProcAddress(hmdll, "createInsertElement");
		CreateGetElement createGetElement = (CreateGetElement)GetProcAddress(hmdll, "createGetElement");
		Print print = (Print)GetProcAddress(hmdll, "print");
		RemoveFunc insert = (RemoveFunc)GetProcAddress(hmdll, "insert");

		if (!open || !update || !createInsertElement) {
			cerr << "[GetProcAddress failed for one or more functions]" << endl;
			FreeLibrary(hmdll);
			return 1;
		}

		const wchar_t* fileName = getWC(argv[1]);

		ht::HtHandle* ht = ht::open(fileName, true);

		if (ht)
			cout << "[Open]: Success" << endl;
		else
			throw "[Open]: Error";

		while (true) {
			int numberKey = rand() % 50;
			string key = intToString(numberKey);
			cout << key << endl;

			ht::Element* element = createInsertElement(key.c_str(), (key.length() + 1), "0", 5);
			insert(ht, element);
			cout << "[Log: element]: " << ht::get(ht, element) << endl;
			cout << "[Log: element data]: ";
			print(element);
			cout << endl;

			if (element)
			{
				cout << "[Get]: Success" << endl;
				string newPayload = incrementPayload((char*)element->payload);
				ht::Element* ht1Elem2 = ht::get(ht, new ht::Element(key.c_str(), (int)(newPayload.length() + 6)));
				if (update(ht, element, newPayload.c_str(), (newPayload.length() + 6)))
				{
					cout << "[Update]: Success" << endl;
					cout << "[Log: element data]: ";
					print(ht1Elem2);
					cout <<"----------------------" << endl;
				}
				else
				{
					cout << "[Update]: Error" << endl;
					print(element);
				}
			}
			else
				cout << "[Get]: Error" << endl;

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

