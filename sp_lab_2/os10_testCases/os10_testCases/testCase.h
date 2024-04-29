#pragma once
#ifdef _WIN64
#pragma comment(lib, "../x64/debug/os10_api.lib")
#else
#pragma comment(lib, "../debug/os10_api.lib")
#endif

#include <iostream>
#include "../../os10_api/os10_api/pch.h"
#include "../../os10_api/os10_api/HT.h"

namespace testCases
{
	BOOL insertGetTestOutTrue(ht::HtHandle* htHandle);
	BOOL insertUpdateTestOutTrue(ht::HtHandle* htHandle);
	BOOL doubleInsertTestOutFalse(ht::HtHandle* htHandle);
	BOOL insertRemoveWithRemovalCheckOutTrue(ht::HtHandle* htHandle);
	BOOL snapAsyncTestTrue(ht::HtHandle* htHandle);
	BOOL InsertTwoHtWithSameNameOutFalse(ht::HtHandle* htHandle);
	BOOL OutOfFreeSpaceOutTrue(ht::HtHandle* htHandle);
}
