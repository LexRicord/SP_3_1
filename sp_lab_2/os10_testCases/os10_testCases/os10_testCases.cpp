#include "testCase.h"


using namespace std;

int main()
{
	ht::HtHandle* ht = ht::create(15, 5, 17, 100, L"./output/HTspace.ht");
	if (ht)
		cout << "[Create]: Success" << endl;
	else
		throw "[log]: error occurred while {ht::create}";

	testCases::insertGetTestOutTrue(ht);

	testCases::insertUpdateTestOutTrue(ht);

	testCases::doubleInsertTestOutFalse(ht);

	testCases::snapAsyncTestTrue(ht);

	testCases::insertRemoveWithRemovalCheckOutTrue(ht);

	testCases::InsertTwoHtWithSameNameOutFalse(ht);

	testCases::OutOfFreeSpaceOutTrue(ht);

	if (ht != nullptr)
		if (ht::close(ht))
			cout << "[Сlose]: Success" << endl;
		else
			throw ht::getLastError(ht);
}