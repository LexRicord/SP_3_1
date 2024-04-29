#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN64
#pragma comment(lib, "../x64/Release/OS11_htAPI.lib")
#else
#pragma comment(lib, "../Release/OS11_htAPI.lib")
#endif

#include <conio.h>
#include "../OS11/pch.h"
#include "../OS11/HT.h"

using namespace std;

wchar_t* getWC(const char* c);

int main(int argc, char* argv[])
{
	ht::HtHandle* ht = nullptr;

	wchar_t* fileName = getWC(argv[1]);
	ht = ht::open(fileName);
	if (ht)
	{
		cout << "==============  ht-Storage Start  ==============" << endl;
		wcout << "filename:\t\t" << ht->fileName << endl;
		cout << "secSnapshotInterval:\t" << ht->secSnapshotInterval << endl;
		cout << "capacity:\t\t" << ht->capacity << endl;
		cout << "maxKeyLength:\t\t" << ht->maxKeyLength << endl;
		cout << "maxPayloadLength:\t" << ht->maxPayloadLength << endl << endl;

		while (!_kbhit())
			SleepEx(0, TRUE);

		ht::close(ht);
	}
	else
		cout << "[Open]: Error" << endl;
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}

