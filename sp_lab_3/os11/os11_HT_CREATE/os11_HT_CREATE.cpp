#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN64
#pragma comment(lib, "../x64/Release/OS11_htAPI.lib")
#else
#pragma comment(lib, "../Release/OS11_htAPI.lib")
#endif

#include "../os11/pch.h"
#include "../os11/ht.h"

using namespace std;

wchar_t* getWC(const char* c);

int main(int argc, char* argv[])
{
	ht::HtHandle* ht = nullptr;
	ht = ht::create(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), getWC(argv[5]));
	if (ht)
	{
		cout << "ht-Storage Created" << endl;
		wcout << "filename: " << ht->fileName << endl;
		cout << "secSnapshotInterval: " << ht->secSnapshotInterval << endl;
		cout << "capacity: " << ht->capacity << endl;
		cout << "maxKeyLength: " << ht->maxKeyLength << endl;
		cout << "maxPayloadLength: " << ht->maxPayloadLength << endl;

		ht::close(ht);
	}
	else
		cout << "[Create]: Error" << endl;
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}
