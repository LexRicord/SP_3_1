#include "testCase.h"

using namespace std;

namespace testCases
{
	BOOL insertGetTestOutTrue(ht::HtHandle* htHandle)
	{
		ht::Element* insertEl = new ht::Element("insertGetTest", 14, "test1", 6);
		if (ht::insert(htHandle, insertEl))
		{
			ht::removeOne(htHandle, insertEl);
			ht::get(htHandle, insertEl);
			if (strcmp("-- not found element (GET)", ht::getLastError(htHandle))) {
				cout << "Test [insertGetTestOutTrue] is successful" << endl;
				return true;
			}
		}
		cout << "Test [insertGetTestOutTrue] is gone wrong" << endl;
		return false;
	}

	BOOL snapAsyncTestTrue(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("snap", 5, "snapAsync", 12);

		ht::insert(htHandle, element);
		WaitForSingleObject(htHandle->mutex, INFINITE);
		ht::getLastError(htHandle);
		if (ht::snap(htHandle)) {
			if (strcmp("-- snapshot error", ht::getLastError(htHandle))) {
				cout << "Test [snapAsyncTestTrue] is successful" << endl;
				ReleaseMutex(htHandle->mutex);
				return false;
			}
		}
		cout << "Test [snapAsyncTestTrue] is gone wrong" << endl;
		ReleaseMutex(htHandle->mutex);
		return true;
	}

	BOOL insertUpdateTestOutTrue(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("updateTest", 17, "test2", 6);

		ht::insert(htHandle, element);
		ht::removeOne(htHandle, element);
		ht::update(htHandle, element, "updatePayloadData", 20);
		if (strcmp("-- not found element(UPDATE)", ht::getLastError(htHandle))) {
			cout << "Test [insertUpdateTestOutTrue] is successful" << endl;
			return true;
		}
		cout << "Test [insertUpdateTestOutTrue] is gone wrong" << endl;
		return false;
	}

	BOOL doubleInsertTestOutFalse(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("insertTest", 11, "test3", 6);
		ht::insert(htHandle, element);

		if (!ht::insert(htHandle, element)) {
			if (strcmp("-- not found element(UPDATE)", ht::getLastError(htHandle))) {
				cout << "Test [doubleInsertTestOutFalse] is successful" << endl;
				return false;
			}
		}
		cout << "Test [doubleInsertTestOutFalse] is gone wrong" << endl;
		return true;
	}

	BOOL insertRemoveWithRemovalCheckOutTrue(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("test3", 6, "test3", 6);

		ht::insert(htHandle, element);
		ht::removeOne(htHandle, element);
		if (!ht::removeOne(htHandle, element)) {
			if (strcmp("-- not found element (DELETE)", ht::getLastError(htHandle))) {
				cout << "Test [insertRemoveWithRemovalCheckOutTrue] is successful" << endl;
				return true;
			}
		}
		cout << "Test [insertRemoveWithRemovalCheckOutTrue] is gone wrong" << endl;
		return false;
	}

	BOOL InsertTwoHtWithSameNameOutFalse(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("test3", 6, "test3", 6);
		ht::Element* element2 = new ht::Element("test3", 6, "test3", 6);
		
		ht::insert(htHandle, element);

		if (!ht::insert(htHandle, element2)) {
			if (strcmp("-- not found free memory", ht::getLastError(htHandle))) {
				cout << "Test [InsertTwoHtWithSameNameOutFalse] is successful" << endl;
				return false;
			}
		}
		cout << "Test [InsertTwoHtWithSameNameOutFalse] is gone wrong" << endl;
		return true;
	}

	BOOL OutOfFreeSpaceOutTrue(ht::HtHandle* htHandle)
	{
		ht::Element* element = new ht::Element("insertTest", 11, "test3", 6);
		char tmpStr[] = "key";
		int i = 0;
		try {
			for (i; i < htHandle->capacity+3; i++)
			{
				element->key = tmpStr + (char)i;
			}
			ht::getLastError(htHandle);
		}
		catch(const char* msg) {
		}
		if (strcmp("-- not found free memory", ht::getLastError(htHandle))) {
			cout << "Test [OutOfFreeSpaceOutTrue] is successful" << endl;
			return true;
		}
		cout << "Test [OutOfFreeSpaceOutTrue] is gone wrong" << endl;
		return false;
	}
}
