#include "HT.h"

using namespace std;

int main()
{
	ht::HtHandle* ht1 = nullptr;
	try
	{
		ht1 = ht::create(
			1500,	// предельное кол-во хранимых эл-тов
			2,		// кд между snapshots
			24,		// максимальная длина ключа
			256,	// максимальная длина данных
			L"./output/HTspace.ht"
		);
		if (ht1)
			cout << "log: function {ht::create} - Success" << endl;
		else
			throw "log: error occurred while {ht::create}";
		const ht::Element ht1Elem = ht::Element("key1", 10, "payloadData", 15);
		if (ht::insert(ht1, &ht1Elem))
			cout << "log: function {ht::insert} - Successful. Key:"<< ht1Elem.key<<" , PayloadData:"<< ht1Elem.payload << endl;
		else
			throw "log: error occurred while {ht::insert}";

		ht::Element* ht1Elem2 = ht::get(ht1, new ht::Element("key1", 10));
		if (ht1Elem2)
			cout << "log: function {ht::get} - Success" << endl;
		else
			throw "log: error occurred while {ht::get}";

		ht::print(ht1Elem2);

		if (ht::update(ht1, ht1Elem2, "newPayloadData", 20))
			cout << "log: function {ht::update} - Success" << endl;
		else
			throw "log: error occurred while {ht::update}";

		if (ht::snap(ht1))
			cout << "log: function {ht::snap} - snapshot is gotten successful" << endl;
		else
			throw "log: error occurred while {ht::snap}";

		ht1Elem2 = ht::get(ht1, new ht::Element("key1", 5));
		if (ht1Elem2)
			cout << "log: function {ht::get} - Success" << endl;
		else
			throw "log: error occurred while {ht::get}";

		ht::print(ht1Elem2);

		SleepEx(2000, TRUE);

		if (ht::remove(ht1, ht1Elem2))
			cout << "log: function {ht::remove} - removal is succesful" << endl;
		else
			throw "log: error occurred while {ht::remove}";

		ht1Elem2 = ht::get(ht1, new ht::Element("falseKey", 5));
		if (ht1Elem2)
			cout << "log: function {ht::get} - Success" << endl;
		else
			throw "log: error occurred while {ht::get}";
	}
	catch (const char* msg)
	{
		cout << msg << endl;

		if (ht1 != nullptr)
			cout << ht::getLastError(ht1) << endl;
	}

	try
	{
		if (ht1 != nullptr)
			if (ht::close(ht1))
				cout << "log: function {ht::close} - closing is succesful" << endl;
			else
				throw "log: error occurred while {ht::close}";
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}