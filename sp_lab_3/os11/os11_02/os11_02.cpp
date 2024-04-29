#define _CRT_SECURE_NO_WARNINGS

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

typedef int (*AddNumbersFunc)(int, int);
typedef ht::HtHandle* (*OpenFunc)(const wchar_t*, bool);
typedef BOOL(*InsertFunc)(ht::HtHandle*, const ht::Element*);
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

		AddNumbersFunc addNumbers = (AddNumbersFunc)GetProcAddress(hmdll, "AddNumbers");
		OpenFunc open = (OpenFunc)GetProcAddress(hmdll, "open");
		InsertFunc insert = (InsertFunc)GetProcAddress(hmdll, "insert");
		CreateInsertElementFunc createInsertElement = (CreateInsertElementFunc)GetProcAddress(hmdll, "createInsertElement");
		CreateGetElement createGetElement = (CreateGetElement)GetProcAddress(hmdll, "createGetElement");

		if (!open || !insert || !createInsertElement) {
			cerr << "[GetProcAddress failed for one or more functions]" << endl;
			FreeLibrary(hmdll);
			return 1;
		}

		const wchar_t* fileName = getWC(argv[1]);

		if (addNumbers) {
			int result = addNumbers(5, 7);
			std::cout << "[Test DLL FUNC 'AddNumbers' Result]: " << result << std::endl;
		}
		else {
			std::cerr << "[GetProcAddress failed]" << std::endl;
		}

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
			string key = intToString(numberKey);
			cout << key << endl;

			ht::Element* element = ht::createInsertElement(key.c_str(), (key.length()+1), "0", 5);
			if (insert(ht, element))
				cout << "[Insert]: Error" << endl;
			else
				cout << "[Insert]: Success" << endl;
				
			if (createGetElement(ht, numberKey))
			{
				cout << "[createGetElement]: Success" << endl;
				cout << createGetElement(ht, numberKey) << endl;
			}
			else
				cout << "[createGetElement]: Error" << endl;
			delete element;

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

